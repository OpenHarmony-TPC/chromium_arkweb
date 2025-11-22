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

#include "arkweb/build/features/features.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "build/build_config.h"
#include "gpu/command_buffer/common/shared_image_usage.h"
#include "gpu/command_buffer/service/memory_tracking.h"
#include "gpu/command_buffer/service/sequence_id.h"
#include "gpu/command_buffer/service/sync_point_manager.h"
#include "gpu/ipc/common/command_buffer_id.h"
#include "gpu/ipc/common/gpu_channel.mojom.h"
#include "gpu/ipc/service/gpu_ipc_service_export.h"
#include "ui/gfx/gpu_extra_info.h"
#include "gpu/ipc/service/shared_image_stub.h"

namespace gpu {
class SharedImageStub;

class SharedImageStubExt : public SharedImageStub {
public:
  SharedImageStubExt(GpuChannel* channel, int32_t route_id);
  gpu::SharedImageStubExt* AsSharedImageStubExt() {
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