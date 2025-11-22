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

#ifndef GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_OZONE_IMAGE_BACKING_FACTORY_EXT_H_
#define GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_OZONE_IMAGE_BACKING_FACTORY_EXT_H_

#include "arkweb/build/features/features.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_refptr.h"
#include "gpu/command_buffer/common/shared_image_usage.h"
#include "gpu/command_buffer/service/shared_image/ozone_image_backing.h"
#include "gpu/command_buffer/service/shared_image/shared_image_backing_factory.h"
#include "gpu/config/gpu_driver_bug_workarounds.h"
#include "gpu/config/gpu_preferences.h"
#include "gpu/gpu_gles2_export.h"
#include "gpu/command_buffer/service/shared_image/ozone_image_backing_factory.h"

namespace gpu {
class OzoneImageBackingFactory;

class OzoneImageBackingFactoryExt : public OzoneImageBackingFactory {
public:
  gpu::OzoneImageBackingFactoryExt* AsOzoneImageBackingFactoryExt() override {
      return this;
  }

  OzoneImageBackingFactoryExt(
    scoped_refptr<SharedContextState> shared_context_state,
    const GpuDriverBugWorkarounds& workarounds,
    const GpuPreferences& gpu_preferences);

  using OzoneImageBackingFactory::CreateSharedImage;
#if BUILDFLAG(ARKWEB_HEIF_SUPPORT)
  std::unique_ptr<SharedImageBacking> CreateSharedImage(
      const Mailbox& mailbox,
      gfx::GpuMemoryBufferHandle handle,
      gfx::BufferFormat format,
      gfx::BufferPlane plane,
      const gfx::Size& size,
      const gfx::ColorSpace& color_space,
      GrSurfaceOrigin surface_origin,
      SkAlphaType alpha_type,
      uint32_t usage,
      void* window_buffer) override;
#endif  // BUILDFLAG(ARKWEB_HEIF_SUPPORT)

  scoped_refptr<base::RefCountedData<DawnProcTable>> dawn_procs_;
  bool use_passthrough_;
};

}

#endif  // GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_OZONE_IMAGE_BACKING_FACTORY_EXT_H_
