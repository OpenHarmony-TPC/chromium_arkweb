// Copyright 2023 Huawei Device Co., Ltd.
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

#ifndef VIDEO_CAPTURE_SURFACE_BUFFER_LISTENER_OHOS_H_
#define VIDEO_CAPTURE_SURFACE_BUFFER_LISTENER_OHOS_H_

#include "base/logging.h"
#include "ohos_capture_delegate.h"
#include "video_capture_device_ohos.h"
namespace media {

class VideoCaptureSufaceBufferListenerOHOS
    : public OHOS::NWeb::CameraBufferListenerAdapter {
 public:
  VideoCaptureSufaceBufferListenerOHOS(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      base::WeakPtr<OHOSCaptureDelegate> media_player);

  VideoCaptureSufaceBufferListenerOHOS(
      const VideoCaptureSufaceBufferListenerOHOS&) = delete;
  VideoCaptureSufaceBufferListenerOHOS& operator=(
      const VideoCaptureSufaceBufferListenerOHOS&) = delete;

  virtual ~VideoCaptureSufaceBufferListenerOHOS();
  void OnBufferAvailable(
      std::shared_ptr<CameraSurfaceAdapter> surface,
      std::shared_ptr<OHOS::NWeb::CameraSurfaceBufferAdapter> buffer,
      std::shared_ptr<OHOS::NWeb::CameraRotationInfoAdapter> roration_info)
      override;

 private:
  std::unique_ptr<VideoCaptureDevice::Client> client_;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::WeakPtr<OHOSCaptureDelegate> capture_delegate_;
};

}  // namespace media

#endif  // VIDEO_CAPTURE_SURFACE_BUFFER_LISTENER_OHOS_H_
