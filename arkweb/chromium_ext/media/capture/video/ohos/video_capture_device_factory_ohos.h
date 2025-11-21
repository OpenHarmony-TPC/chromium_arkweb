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

// Implementation of a VideoCaptureDeviceFactoryOHOS class.

#ifndef MEDIA_CAPTURE_VIDEO_OHOS_VIDEO_CAPTURE_DEVICE_FACTORY_OHOS_H_
#define MEDIA_CAPTURE_VIDEO_OHOS_VIDEO_CAPTURE_DEVICE_FACTORY_OHOS_H_

#include <memory>
#include <string>
#include <vector>

#include "base/task/single_thread_task_runner.h"
#include "camera_manager_adapter.h"
#include "media/capture/video/video_capture_device_factory.h"
#include "media/capture/video_capture_types.h"

namespace media {
using namespace OHOS::NWeb;

// Extension of VideoCaptureDeviceFactory to create and manipulate OHOS
// devices.
class CAPTURE_EXPORT VideoCaptureDeviceFactoryOHOS
    : public VideoCaptureDeviceFactory {
 public:
  explicit VideoCaptureDeviceFactoryOHOS(
      scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner);

  VideoCaptureDeviceFactoryOHOS(const VideoCaptureDeviceFactoryOHOS&) = delete;
  VideoCaptureDeviceFactoryOHOS& operator=(
      const VideoCaptureDeviceFactoryOHOS&) = delete;

  ~VideoCaptureDeviceFactoryOHOS() override;

  VideoCaptureErrorOrDevice CreateDevice(
      const VideoCaptureDeviceDescriptor& device_descriptor) override;
  void GetDevicesInfo(GetDevicesInfoCallback callback) override;
  void OnCameraStatusChanged(CameraStatusAdapter camera_status,
                             std::string callback_device_id);

 private:
  int CheckDeviceId(const std::string device_id);
  bool CheckAndInitCameraManager();
  scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner_;
  std::shared_ptr<CameraManagerAdapter> camera_manager_adapter_;
  bool is_camera_manager_created_{false};
#if BUILDFLAG(ARKWEB_UNITTESTS)
  friend class VideoCaptureDeviceFactoryOHOSTest;
#endif
  base::WeakPtrFactory<VideoCaptureDeviceFactoryOHOS> weak_factory_{this};
};

}  // namespace media
#endif  // MEDIA_CAPTURE_VIDEO_OHOS_VIDEO_CAPTURE_DEVICE_FACTORY_OHOS_H_
