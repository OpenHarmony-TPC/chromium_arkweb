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

#ifndef MEDIA_GPU_OHOS_VIDEO_FRAME_FACTORY_H_
#define MEDIA_GPU_OHOS_VIDEO_FRAME_FACTORY_H_

#include <memory>

#include "base/memory/ref_counted.h"
#include "base/task/single_thread_task_runner.h"
#include "base/time/time.h"
#include "media/base/video_decoder.h"
#include "media/gpu/media_gpu_export.h"
#include "ui/gfx/geometry/size.h"

namespace media {

class CodecOutputBuffer;
class CodecSurfaceBundle;
class VideoFrame;

class MEDIA_GPU_EXPORT VideoFrameFactory {
 public:
  using InitCB = base::RepeatingCallback<void(
      scoped_refptr<gpu::NativeImageTextureOwner>)>;
  using OnceOutputCB = base::OnceCallback<void(scoped_refptr<VideoFrame>)>;

  VideoFrameFactory() = default;
  virtual ~VideoFrameFactory() = default;

  virtual void Initialize(InitCB init_cb) = 0;

  virtual void SetSurfaceBundle(
      scoped_refptr<CodecSurfaceBundle> surface_bundle) = 0;

  virtual void CreateVideoFrame(
      std::unique_ptr<CodecOutputBuffer> output_buffer,
      base::TimeDelta timestamp,
      gfx::Size natural_size,
      OnceOutputCB output_cb) = 0;

  virtual void RunAfterPendingVideoFrames(base::OnceClosure closure) = 0;
#if BUILDFLAG(ARKWEB_PIP)
  virtual void PipEnable(bool enable) = 0;
#endif
};

}  // namespace media

#endif  // MEDIA_GPU_OHOS_VIDEO_FRAME_FACTORY_H_
