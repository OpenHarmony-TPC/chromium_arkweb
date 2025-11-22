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

#ifndef MEDIA_CAPTURE_COMMON_OHOS_H_
#define MEDIA_CAPTURE_COMMON_OHOS_H_

#include <memory>
#include <string>
#include <vector>

#include "base/task/single_thread_task_runner.h"
#include "camera_manager_adapter.h"
#include "media/capture/video/video_capture_device_factory.h"
#include "media/capture/video_capture_types.h"

namespace media {
using namespace OHOS::NWeb;
const std::unordered_map<VideoTransportType, VideoCaptureTransportType>
    TRANS_TYPE_MAP = {
        {VideoTransportType::VIDEO_TRANS_TYPE_BUILD_IN,
         VideoCaptureTransportType::APPLE_USB_OR_BUILT_IN},
        {VideoTransportType::VIDEO_TRANS_TYPE_USB,
         VideoCaptureTransportType::APPLE_USB_OR_BUILT_IN},
        {VideoTransportType::VIDEO_TRANS_TYPE_REMOTE,
         VideoCaptureTransportType::OTHER_TRANSPORT},
};

const std::unordered_map<VideoFacingModeAdapter, VideoFacingMode>
    FACING_MODE_MAP = {
        {VideoFacingModeAdapter::FACING_NONE, MEDIA_VIDEO_FACING_NONE},
        {VideoFacingModeAdapter::FACING_USER, MEDIA_VIDEO_FACING_USER},
        {VideoFacingModeAdapter::FACING_ENVIRONMENT,
         MEDIA_VIDEO_FACING_ENVIRONMENT},
};

const std::unordered_map<VideoPixelFormatAdapter, VideoPixelFormat>
    PIXEL_FORMAT_MAP = {
        {VideoPixelFormatAdapter::FORMAT_RGBA_8888, PIXEL_FORMAT_ABGR},
        {VideoPixelFormatAdapter::FORMAT_YCBCR_420_888, PIXEL_FORMAT_YUV420P12},
        {VideoPixelFormatAdapter::FORMAT_YUV_420_SP, PIXEL_FORMAT_NV21},
        {VideoPixelFormatAdapter::FORMAT_JPEG, PIXEL_FORMAT_MJPEG},
        {VideoPixelFormatAdapter::FORMAT_UNKNOWN, PIXEL_FORMAT_UNKNOWN},
};

const std::unordered_map<VideoPixelFormat, VideoPixelFormatAdapter>
    ADPATER_PIXEL_FORMAT_MAP = {
        {PIXEL_FORMAT_ABGR, VideoPixelFormatAdapter::FORMAT_RGBA_8888},
        {PIXEL_FORMAT_YUV420P12, VideoPixelFormatAdapter::FORMAT_YCBCR_420_888},
        {PIXEL_FORMAT_NV21, VideoPixelFormatAdapter::FORMAT_YUV_420_SP},
        {PIXEL_FORMAT_MJPEG, VideoPixelFormatAdapter::FORMAT_JPEG},
        {PIXEL_FORMAT_UNKNOWN, VideoPixelFormatAdapter::FORMAT_UNKNOWN},
};

class VideoCaptureCommonOHOS {
 public:
  VideoCaptureCommonOHOS();
  ~VideoCaptureCommonOHOS();

  static VideoCaptureTransportType GetCameraTransportType(
      VideoTransportType trans_type);
  static VideoFacingMode GetCameraFacingMode(
      VideoFacingModeAdapter facing_mode);
  static VideoPixelFormat GetCameraPixelFormatType(
      VideoPixelFormatAdapter pixel_format);
  static VideoCaptureFormats GetSupportedFormats(
      const std::vector<std::shared_ptr<FormatAdapter>>&
          capture_formats_adapter);
  static VideoPixelFormatAdapter GetAdapterCameraPixelFormatType(
      VideoPixelFormat pixel_format);
};

}  // namespace media
#endif  // MEDIA_CAPTURE_COMMON_OHOS_H_
