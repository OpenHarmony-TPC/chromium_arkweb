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

#ifndef MEDIA_BASE_VIDEO_UTIL_EXT_H_
#define MEDIA_BASE_VIDEO_UTIL_EXT_H_

#include <stdint.h>
#include <vector>
#include "base/memory/scoped_refptr.h"
#include "media/base/encoder_status.h"
#include "media/base/media_export.h"
#include "media/base/video_types.h"
#include "third_party/skia/include/core/SkImage.h"
#include "third_party/skia/include/core/SkYUVAInfo.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/size.h"

namespace media {

class VideoFramePool;
class VideoFrame;

// Copy pixel data from |src_frame| to |dst_frame| applying scaling and pixel
// format conversion as needed. Both frames need to be mappabale and have either
// I420 or NV12 pixel format.
[[nodiscard]] MEDIA_EXPORT EncoderStatus
ConvertAndScaleFrame(const VideoFrame& src_frame,
                     VideoFrame& dst_frame,
                     std::vector<uint8_t>& tmp_buf);
}

#endif // MEDIA_BASE_VIDEO_UTIL_EXT_H_