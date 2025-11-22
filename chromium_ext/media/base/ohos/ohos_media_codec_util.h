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

#ifndef MEDIA_BASE_OHOS_MEDIA_CODEC_UTIL_H_
#define MEDIA_BASE_OHOS_MEDIA_CODEC_UTIL_H_

#include "third_party/ohos_ndk/includes/ohos_adapter/media_codec_adapter.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/ohos_adapter_helper.h"
#include "base/compiler_specific.h"
#include "media/base/audio_codecs.h"
#include "media/base/sample_format.h"
#include "media/base/video_codecs.h"

namespace media {
using namespace OHOS::NWeb;
using namespace std;

struct CapabilityData {
  int32_t maxWidth = 0;
  int32_t maxHeight = 0;
  int32_t maxframeRate = 0;
};

class OHOSMediaCodecUtil {
 public:
  static CapabilityData GetCodecCapability(const std::string& mime,
                                           bool isCodec);
  static std::string CodecToOHOSMimeType(AudioCodec codec);
  static std::string CodecToOHOSMimeType(AudioCodec codec,
                                            SampleFormat sample_format);
  static std::string CodecToOHOSMimeType(VideoCodec codec);
  static bool IsPassthroughAudioFormat(AudioCodec codec);
  static bool CanDecode(VideoCodec codec, bool is_secure);
  static bool CanDecode(AudioCodec codec);
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_MEDIA_CODEC_UTIL_H_
