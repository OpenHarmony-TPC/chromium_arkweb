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

#ifndef GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_SHARED_IMAGE_BACKING_FACTORY_EXT_H_
#define GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_SHARED_IMAGE_BACKING_FACTORY_EXT_H_

#include <climits>
#include <cstdint>
#include <memory>

#include "base/memory/weak_ptr.h"
#include "components/viz/common/resources/shared_image_format.h"
#include "gpu/command_buffer/common/shared_image_usage.h"
#include "gpu/command_buffer/service/shared_image/shared_image_backing.h"
#include "gpu/config/gpu_preferences.h"
#include "gpu/gpu_gles2_export.h"
#include "gpu/ipc/common/surface_handle.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/gpu/ganesh/GrTypes.h"
#include "ui/gfx/buffer_types.h"
#include "ui/gfx/gpu_memory_buffer.h"

namespace gpu {

class SharedImageBackingFactoryExt {
 public:
#if BUILDFLAG(ARKWEB_HEIF_SUPPORT)
  virtual std::unique_ptr<SharedImageBacking> CreateSharedImage(
      const Mailbox& mailbox,
      gfx::GpuMemoryBufferHandle handle,
      gfx::BufferFormat format,
      gfx::BufferPlane plane,
      const gfx::Size& size,
      const gfx::ColorSpace& color_space,
      GrSurfaceOrigin surface_origin,
      SkAlphaType alpha_type,
      uint32_t usage,
      void* window_buffer) { return nullptr; }
#endif // BUILDFLAG(ARKWEB_HEIF_SUPPORT)
};

}
#endif //GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_SHARED_IMAGE_BACKING_FACTORY_EXT_H_