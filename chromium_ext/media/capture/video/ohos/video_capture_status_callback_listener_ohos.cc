// Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "media/capture/video/ohos/video_capture_device_factory_ohos.h"
#include "video_capture_status_callback_listener_ohos.h"
#include "base/logging.h"
#include "ohos_adapter_helper.h"
namespace media {

VideoCaptureCameraStatusCallbackListenerOHOS::
    VideoCaptureCameraStatusCallbackListenerOHOS(
        const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
        base::WeakPtr<VideoCaptureDeviceFactoryOHOS> capture_device_factory)
    : task_runner_(task_runner),
      capture_device_factory_(capture_device_factory) {
  DCHECK(task_runner_.get());
  DCHECK(capture_device_factory_);
}

VideoCaptureCameraStatusCallbackListenerOHOS::
    ~VideoCaptureCameraStatusCallbackListenerOHOS() {}

void VideoCaptureCameraStatusCallbackListenerOHOS::OnCameraStatusChanged(
    CameraStatusAdapter camera_status,
    std::string callback_device_id) {
  task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(&VideoCaptureDeviceFactoryOHOS::OnCameraStatusChanged,
                     capture_device_factory_, camera_status,
                     callback_device_id));
}

}  // namespace media
