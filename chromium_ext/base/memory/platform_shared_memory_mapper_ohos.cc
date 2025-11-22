// Copyright (c) 2024 Huawei Device Co., Ltd.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "base/memory/platform_shared_memory_mapper.h"

#include "base/logging.h"
#include "base/numerics/safe_conversions.h"

#include <sys/mman.h>

namespace base {

std::optional<span<uint8_t>> PlatformSharedMemoryMapper::Map(
    subtle::PlatformSharedMemoryHandle handle,
    bool write_allowed,
    uint64_t offset,
    size_t size) {
  void* address =
      mmap(nullptr, size, PROT_READ | (write_allowed ? PROT_WRITE : 0),
           MAP_SHARED, handle, checked_cast<off_t>(offset));

  if (address == MAP_FAILED) {
    DPLOG(ERROR) << "mmap " << handle << " failed";
    return std::nullopt;
  }

  return make_span(reinterpret_cast<uint8_t*>(address), size);
}

void PlatformSharedMemoryMapper::Unmap(span<uint8_t> mapping) {
  if (munmap(mapping.data(), mapping.size()) < 0)
    DPLOG(ERROR) << "munmap";
}

}  // namespace base
