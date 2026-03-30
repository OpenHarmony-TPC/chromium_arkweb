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

#ifndef COMPONENTS_VIZ_SERVICE_DISPLAY_EMBEDDER_SKIA_OUTPUT_SURFACE_IMPL_ON_GPU_H_
#error "must be in include form COMPONENTS_VIZ_SERVICE_DISPLAY_EMBEDDER_SKIA_OUTPUT_SURFACE_IMPL_ON_GPU_H_"
#endif

#include "components/viz/service/display_embedder/skia_output_surface_impl_on_gpu.h"

namespace viz {

#if BUILDFLAG(ARKWEB_VSYNC_SCHEDULE)
void SkiaOutputSurfaceImplOnGpu::SetBypassVsyncCondition(int32_t condition) {
  if (output_device_) {
    output_device_->SetBypassVsyncCondition(condition);
  }
}
#endif

#if BUILDFLAG(ARKWEB_PARTIAL_DRAW)
gfx::Rect SkiaOutputSurfaceImplOnGpu::GetLastBufferDamageRect() {
  if (output_device_) {
    return output_device_->GetLastBufferDamageRect();
  }
  return gfx::Rect();
}

int SkiaOutputSurfaceImplOnGpu::GetLastBufferAge() {
  if (output_device_) {
    return output_device_->GetLastBufferAge();
  }
  return 0;
}

int SkiaOutputSurfaceImplOnGpu::GetLastBufferSameCnt() {
  if (output_device_) {
    return output_device_->GetLastBufferSameCnt();
  }
  return 0;
}

void SkiaOutputSurfaceImplOnGpu::SetPresentBufferDamageRect(gfx::Rect damage_rect, gfx::Rect curr_rect) {
  if (output_device_) {
    (void)output_device_->SetPresentBufferDamageRect(damage_rect, curr_rect);
  }
}

void SkiaOutputSurfaceImplOnGpu::ClosePostSubBuffer() {
  if (output_device_) {
    output_device_->ClosePostSubBuffer();
  }
}
#endif

} // namespace viz