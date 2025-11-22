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

#ifndef GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_SHARED_IMAGE_FACTORY_EXT_H_
#define GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_SHARED_IMAGE_FACTORY_EXT_H_

#include "arkweb/build/features/features.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/scoped_refptr.h"
#include "build/build_config.h"
#include "components/viz/common/resources/shared_image_format.h"
#include "gpu/command_buffer/common/mailbox.h"
#include "gpu/command_buffer/common/shared_image_capabilities.h"
#include "gpu/command_buffer/common/shared_image_usage.h"
#include "gpu/command_buffer/service/shared_image/shared_image_manager.h"
#include "gpu/config/gpu_driver_bug_workarounds.h"
#include "gpu/config/gpu_preferences.h"
#include "gpu/gpu_gles2_export.h"
#include "gpu/ipc/common/gpu_memory_buffer_support.h"
#include "gpu/ipc/common/surface_handle.h"
#include "ui/gfx/buffer_types.h"
#include "ui/gfx/gpu_extra_info.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/gl/gl_bindings.h"

#include "gpu/command_buffer/service/shared_image/shared_image_factory.h"

namespace gpu {
class MemoryTracker;
class SharedContextState;
class SharedImageBackingFactory;
class D3DImageBackingFactory;
struct GpuFeatureInfo;
struct GpuPreferences;
class SharedImageFactory;

class SharedImageFactoryExt : public SharedImageFactory {
public:
  SharedImageFactoryExt(const GpuPreferences& gpu_preferences,
                        const GpuDriverBugWorkarounds& workarounds,
                        const GpuFeatureInfo& gpu_feature_info,
                        SharedContextState* context_state,
                        SharedImageManager* manager,
                        MemoryTracker* tracker,
                        bool is_for_display_compositor);
  ~SharedImageFactoryExt() override {}
  gpu::SharedImageFactoryExt* AsSharedImageFactoryExt() override {
      return this;
  }

#if BUILDFLAG(ARKWEB_HEIF_SUPPORT)
  bool CreateSharedImage(const Mailbox& mailbox,
                         gfx::GpuMemoryBufferHandle handle,
                         gfx::BufferFormat format,
                         gfx::BufferPlane plane,
                         const gfx::Size& size,
                         const gfx::ColorSpace& color_space,
                         GrSurfaceOrigin surface_origin,
                         SkAlphaType alpha_type,
                         uint32_t usage,
                         void* window_buffer);
#endif  // BUILDFLAG(ARKWEB_HEIF_SUPPORT)
};

}
#endif