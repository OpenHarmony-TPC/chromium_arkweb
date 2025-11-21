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

#include "video_capture_surface_buffer_listener_ohos.h"

#include "base/logging.h"
#include "ohos_adapter_helper.h"
namespace media {

VideoCaptureSufaceBufferListenerOHOS::VideoCaptureSufaceBufferListenerOHOS(
    const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
    base::WeakPtr<OHOSCaptureDelegate> capture_delegate)
    : task_runner_(task_runner), capture_delegate_(capture_delegate) {
  DCHECK(task_runner_.get());
  DCHECK(capture_delegate_);
}

VideoCaptureSufaceBufferListenerOHOS::~VideoCaptureSufaceBufferListenerOHOS() {}

void VideoCaptureSufaceBufferListenerOHOS::OnBufferAvailable(
    std::shared_ptr<CameraSurfaceAdapter> surface,
    std::shared_ptr<OHOS::NWeb::CameraSurfaceBufferAdapter> buffer,
    std::shared_ptr<OHOS::NWeb::CameraRotationInfoAdapter> roration_info) {
  task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(&OHOSCaptureDelegate::OnBufferAvailable, capture_delegate_,
                     surface, std::move(buffer), roration_info));
}

}  // namespace media
