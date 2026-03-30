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

#ifndef V8_OHOS_PERF_PARSE_JITCODE_H_
#define V8_OHOS_PERF_PARSE_JITCODE_H_

#include <elf.h>
#include <fcntl.h>

#include <cstring>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace v8 {
namespace jitparse {

struct JitSymbol {
  uint64_t vaddr;
  uint32_t codeSize;
  std::string name;

  JitSymbol(uint64_t vaddr, uint32_t codeSize, const std::string& name)
      : vaddr(vaddr), codeSize(codeSize), name(name) {}
};

class ELFParser {
 public:
  bool getInstruction(uint64_t pc, std::string& codeName) const;
  bool getInstruction(uint64_t pc, std::string& codeName, uint32_t& offset) const;
  std::vector<JitSymbol> jitSymbols;
};

class JitSymbolVMA {
 public:
  explicit JitSymbolVMA(uint32_t pid);
  uintptr_t GetStartAddress() const;
  bool Contains(uintptr_t address) const;
  bool HasPrepared() const;
  ~JitSymbolVMA();
 private:
  uintptr_t startAddress = 0;
  uintptr_t endAddress = 0;
  uint64_t memorySize = 0;
  bool hasPrepared = false;
  const bool isCurrentProcess;
};

class JsSymbolExtractor {
 public:
  explicit JsSymbolExtractor(uint32_t pid);

  ~JsSymbolExtractor();

  bool GetHeader(uintptr_t& memoryPointer) const;
  bool GetJitSymbols(uint32_t& codeID,
                uintptr_t& memoryPointer,
                std::vector<JitSymbol>& jitSymbols) const;

  ELFParser* GetParser() const;

  bool GetInstruction(uintptr_t pc, std::string& codeName) const;
  bool GetInstruction(uintptr_t pc, std::string& codeName, uint32_t& offset) const;

 private:
  ELFParser* parser = nullptr;
  JitSymbolVMA* jitSymbolVMA = nullptr;
  const uint32_t targetPid;
};

}  // namespace jitparse
}  // namespace v8

#endif  // V8_OHOS_PERF_PARSE_JITCODE_H_