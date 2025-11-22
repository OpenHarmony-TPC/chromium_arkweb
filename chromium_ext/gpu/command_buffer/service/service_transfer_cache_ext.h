// Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef GPU_COMMAND_BUFFER_SERVICE_SERVICE_TRANSFER_CACHE_EXT_H_
#define GPU_COMMAND_BUFFER_SERVICE_SERVICE_TRANSFER_CACHE_EXT_H_

#include "gpu/config/gpu_preferences.h"
#include "gpu/command_buffer/service/service_transfer_cache.h"

namespace gpu {
class ServiceTransferCache;

class ServiceTransferCacheExt : public ServiceTransferCache {
public:
  ServiceTransferCacheExt(const GpuPreferences& preferences,
                          base::RepeatingClosure flush_callback);

  raw_ptr<ServiceTransferCacheExt> AsServiceTransferCacheExt() override {
    return this;
  }

#if BUILDFLAG(ARKWEB_HEIF_SUPPORT)
  bool CreateLockedRGBAHardwareDecodedImageEntry(
      int decoder_id,
      uint32_t entry_id,
      ServiceDiscardableHandle handle,
      GrDirectContext* context,
      std::vector<sk_sp<SkImage>> plane_images,
      size_t buffer_byte_size);
#endif
};

}

#endif // GPU_COMMAND_BUFFER_SERVICE_SERVICE_TRANSFER_CACHE_EXT_H_