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

#ifndef GPU_COMMAND_BUFFER_COMMON_GPU_MEMORY_BUFFER_SUPPORT_UTILS_H_
#define GPU_COMMAND_BUFFER_COMMON_GPU_MEMORY_BUFFER_SUPPORT_UTILS_H_

#include "base/containers/enum_set.h"
#include "build/build_config.h"
#include "gpu/gpu_export.h"
#include "ui/gfx/buffer_types.h"
#include "ui/gfx/geometry/size.h"

namespace gpu {

// Return the size for |plane| with image |size|. E.g, for the Y plane of
// YUV_420_BIPLANAR, return size subsampled by a factor of 2. Assumes
// IsPlaneValidForGpuMemoryBufferFormat returns true for the provided arguments.
GPU_EXPORT gfx::Size GetPlaneSize(gfx::BufferPlane plane,
                                  const gfx::Size& size);

// Return the buffer format for |plane| of |format|. E.g, for the Y plane of
// YUV_420_BIPLANAR, return R_8. Assumes IsPlaneValidForGpuMemoryBufferFormat
// returns true for the provided arguments.
GPU_EXPORT gfx::BufferFormat GetPlaneBufferFormat(gfx::BufferPlane plane,
                                                  gfx::BufferFormat format);

}

#endif // GPU_COMMAND_BUFFER_COMMON_GPU_MEMORY_BUFFER_SUPPORT_UTILS_H_