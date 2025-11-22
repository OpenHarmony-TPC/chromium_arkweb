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

// Based on frame_info_helper.h originally written by
// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. 

#ifndef MEDIA_GPU_OHOS_FRAME_INFO_HELPER_H_
#define MEDIA_GPU_OHOS_FRAME_INFO_HELPER_H_

#include "gpu/command_buffer/service/ref_counted_lock.h"
#include "media/gpu/media_gpu_export.h"
#include "media/gpu/ohos/shared_image_video_provider.h"
#include "third_party/abseil-cpp/absl/types/optional.h"
#include "ui/gfx/geometry/rect.h"

namespace media {
class CodecOutputBufferRenderer;

class MEDIA_GPU_EXPORT FrameInfoHelper {
 public:
  struct FrameInfo {
    FrameInfo();
    ~FrameInfo();

    FrameInfo(FrameInfo&&);
    FrameInfo(const FrameInfo&);
    FrameInfo& operator=(const FrameInfo&);

    gfx::Size coded_size;
    gfx::Rect visible_rect;
    absl::optional<gpu::VulkanYCbCrInfo> ycbcr_info;
  };

  using FrameInfoReadyCB =
      base::OnceCallback<void(std::unique_ptr<CodecOutputBufferRenderer>,
                              FrameInfo)>;

  static std::unique_ptr<FrameInfoHelper> Create(
      scoped_refptr<base::SequencedTaskRunner> gpu_task_runner,
      SharedImageVideoProvider::GetStubCB get_stub_cb,
      scoped_refptr<gpu::RefCountedLock> drdc_lock);

  virtual ~FrameInfoHelper() = default;

  virtual void GetFrameInfo(
      std::unique_ptr<CodecOutputBufferRenderer> buffer_renderer,
      FrameInfoReadyCB callback) = 0;

 protected:
  FrameInfoHelper() = default;
};

}  // namespace media

#endif  // MEDIA_GPU_OHOS_FRAME_INFO_HELPER_H_
