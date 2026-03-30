/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "parse-jitcode.h"

#include <sys/mman.h>
#include <sys/uio.h>
#include <unistd.h>

#include <fstream>
#include <string>

#include "hilog.h"
#include "perf-jit-common.h"

namespace v8 {
namespace jitparse {
static bool IsPidMatch(uint32_t storedPid, uint32_t dfxPid) {
  if (storedPid != dfxPid) {
#ifdef USING_OHOS
    return false;
#endif
#ifdef USING_OHOS_WEB
    // arkweb render pid stored is always 1
    if (storedPid != 1) {
        return false;
    }
#endif
  }
  return true;
}

static bool ReadProcessMemory(uint32_t pid, const uint64_t addr,
                                                  void* data,
                                                  size_t size) {
  uint64_t currentAddr = addr;
  if (__builtin_add_overflow(currentAddr, size, &currentAddr)) {
    return false;
  }
  struct iovec remoteIov = {
      .iov_base = reinterpret_cast<void*>(addr),
      .iov_len = size,
  };
  struct iovec dataIov = {
      .iov_base = static_cast<uint8_t*>(data),
      .iov_len = size,
  };
  ssize_t readCount =
      process_vm_readv(pid, &dataIov, 1, &remoteIov, 1, 0);
  return static_cast<size_t>(readCount) == size;
}

static std::pair<uintptr_t, uintptr_t> FindVMAInProcMaps(uint32_t pid,
                                                        const std::string &vmaName) {
  std::string maps_path = "/proc/" + std::to_string(pid) + "/maps";
  std::ifstream maps_file(maps_path);
  std::pair<uintptr_t, uintptr_t> res(0, 0);
  if (!maps_file.is_open()) {
    HilogPrint(ERROR, "can not open map file!");
    return res;
  }
  std::string line;
  while (std::getline(maps_file, line)) {
    if (line.find(vmaName) != std::string::npos) {
      // parse start address
      size_t dash_pos = line.find('-');
      if (dash_pos == std::string::npos) {
        continue;
      }
      size_t end_pos = line.find(' ');
      std::string start_addr_str = line.substr(0, dash_pos);
      std::string end_addr_str = line.substr(dash_pos + 1, end_pos);
      // convert address string to uint64_t
      constexpr int kNumberBase = 16;
      res.first = static_cast<uintptr_t>(
          std::stoull(start_addr_str, nullptr, kNumberBase));
      res.second = static_cast<uintptr_t>(
          std::stoull(end_addr_str, nullptr, kNumberBase));
      return res;
    }
  }
  HilogPrint(ERROR, "cant find JSVM JIT symbol");
  return res;
}

JitSymbolVMA::JitSymbolVMA(uint32_t pid) : isCurrentProcess(
                                        static_cast<uint32_t>(getpid()) == pid) {
  std::pair<uintptr_t, uintptr_t> addressRange = FindVMAInProcMaps(pid,
                                                            internal::kJitSymbolMapName);
  uintptr_t startMapAddress = addressRange.first;
  uintptr_t endMapAddress = addressRange.second;
  if (startMapAddress == 0 || endMapAddress == 0) {
    return;
  }
  memorySize = endMapAddress - startMapAddress;
  if (memorySize < 0) {
    return;
  }
  void* address = nullptr;
  if (isCurrentProcess) {
    startAddress = startMapAddress;
    endAddress = endMapAddress;
  } else {
    address = mmap(nullptr, memorySize, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (address == MAP_FAILED) {
      HilogPrint(ERROR, "failed mmap symbol memory!");
      return;
    }

    if (!ReadProcessMemory(pid, static_cast<uint64_t>(startMapAddress), address,
                                                                              memorySize)) {
      HilogPrint(ERROR, "failed read dfxAddress to local address.");
      return;
    }
    startAddress = reinterpret_cast<uintptr_t>(address);
    endAddress = reinterpret_cast<uintptr_t>(address) + memorySize;
  }
  hasPrepared = true;
}

JitSymbolVMA::~JitSymbolVMA() {
  if (!isCurrentProcess) {
    munmap(reinterpret_cast<void*>(startAddress), memorySize);
  }
}

uintptr_t JitSymbolVMA::GetStartAddress() const {
  return startAddress;
}

bool JitSymbolVMA::Contains(uintptr_t address) const {
  if (address >= startAddress && address < endAddress) {
    return true;
  }
  return false;
}

bool JitSymbolVMA::HasPrepared() const {
  return hasPrepared;
}

bool JsSymbolExtractor::GetHeader(uintptr_t& memoryPointer) const {
  internal::PerfJitHeader* header =
      reinterpret_cast<internal::PerfJitHeader*>(memoryPointer);
  if (!IsPidMatch(header->process_id_, targetPid)) {
    return false;
  }
  memoryPointer += header->size_;
  return true;
}

bool JsSymbolExtractor::GetJitSymbols(uint32_t& codeID, uintptr_t& memoryPointer,
                                      std::vector<JitSymbol>& jitSymbols) const {
  // Get load-header
  while (true) {
    if (!jitSymbolVMA->Contains(memoryPointer + sizeof(internal::PerfJitCodeLoad))) {
      // Some cases do not have an end tag.
      return true;
    }
    internal::PerfJitCodeLoad* codeLoad =
        reinterpret_cast<internal::PerfJitCodeLoad*>(memoryPointer);
    if (!jitSymbolVMA->Contains(memoryPointer + codeLoad->size_)) {
      // Some cases do not have an end tag.
      return true;
    }
    if (!IsPidMatch(codeLoad->process_id_, targetPid) || codeLoad->code_id_ != codeID) {
      HilogPrint(ERROR, "codeLoad check failed!");
      return false;
    }

    codeID++;
    char* code_name =
        reinterpret_cast<char*>(memoryPointer + sizeof(internal::PerfJitCodeLoad));
    uint8_t* code_pointer = reinterpret_cast<uint8_t*>(
        memoryPointer + sizeof(internal::PerfJitCodeLoad) + strlen(code_name) +
        sizeof(internal::kStringTerminator));

    jitSymbols.emplace_back(codeLoad->code_address_, codeLoad->code_size_,
                                code_name);
    memoryPointer += codeLoad->size_;

    char* maybeKJitCodeTerminator = reinterpret_cast<char*>(memoryPointer);
    if (strcmp(maybeKJitCodeTerminator, internal::kJitCodeTerminator) == 0) {
      HilogPrint(INFO, "last jit code block");
      return true;
    }
    if (!jitSymbolVMA->Contains(memoryPointer)) {
      HilogPrint(ERROR, "Reach max shared memory size!");
      return false;
    }
  }
}

JsSymbolExtractor::JsSymbolExtractor(uint32_t pid) : targetPid(pid) {
  jitSymbolVMA = new JitSymbolVMA(pid);
  if (!jitSymbolVMA->HasPrepared()) {
    return;
  }
  uintptr_t memoryPointer = jitSymbolVMA->GetStartAddress();
  uint32_t codeID = 0;
  std::vector<JitSymbol> jitSymbols;
  if (!GetHeader(memoryPointer)) {
    return;
  }
  parser = new ELFParser();
  if (!GetJitSymbols(codeID, memoryPointer, parser->jitSymbols)) {
    HilogPrint(ERROR, "GetJitSymbols error!");
    delete parser;
    return;
  }
}

JsSymbolExtractor::~JsSymbolExtractor() {
  if (parser != nullptr) {
    delete parser;
  }
  if (jitSymbolVMA != nullptr) {
    delete jitSymbolVMA;
  }
}

ELFParser* JsSymbolExtractor::GetParser() const {
  return parser;
}

bool JsSymbolExtractor::GetInstruction(uintptr_t pc, std::string& codeName) const {
  return parser->getInstruction(pc, codeName);
}

bool JsSymbolExtractor::GetInstruction(uintptr_t pc, std::string& codeName, uint32_t& offset) const {
  return parser->getInstruction(pc, codeName, offset);
}

bool ELFParser::getInstruction(uint64_t pc, std::string& codeName) const {
  for (const auto& jitSymbol : jitSymbols) {
    if (pc >= jitSymbol.vaddr && pc < jitSymbol.vaddr + jitSymbol.codeSize) {
      codeName = jitSymbol.name;
      return true;
    }
  }
  return false;
}

bool ELFParser::getInstruction(uint64_t pc, std::string& codeName, uint32_t& offset) const {
  for (const auto& jitSymbol : jitSymbols) {
    if (pc >= jitSymbol.vaddr && pc < jitSymbol.vaddr + jitSymbol.codeSize) {
      codeName = jitSymbol.name;
      offset = pc - jitSymbol.vaddr;
      return true;
    }
  }
  return false;
}

}  // namespace jitparse
}  // namespace v8
