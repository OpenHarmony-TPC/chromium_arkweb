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
#ifndef OHOS_MEDIA_CODEC_BRIAGE_H_
#define OHOS_MEDIA_CODEC_BRIAGE_H_

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "media/base/video_frame.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/media_codec_adapter.h"

namespace OHOS::NWeb {
struct DecoderFormat {
  int32_t width;
  int32_t height;
  double frameRate;
};

struct BufferInfo {
  int64_t presentationTimeUs = 0;
  int32_t size = 0;
  int32_t offset = 0;
};

struct OhosBuffer {
  uint8_t* addr;
  uint32_t bufferSize;
};

struct CodecConfigPara {
  int32_t width;
  int32_t height;
  int64_t bitRate;
  double frameRate;
};
}  // namespace OHOS::NWeb

namespace media {
using namespace OHOS::NWeb;
enum class CodecType {
  kAny,
  kSecure,    // Note that all secure codecs are HW codecs.
  kSoftware,  // In some cases hardware codecs could hang the GPU process.
};

enum MediaCodecStatus {
  MEDIA_CODEC_OK,
  MEDIA_CODEC_TRY_AGAIN_LATER,
  MEDIA_CODEC_OUTPUT_BUFFERS_CHANGED,
  MEDIA_CODEC_OUTPUT_FORMAT_CHANGED,
  MEDIA_CODEC_NO_KEY,
  MEDIA_CODEC_ERROR
};

class OHOSMediaCodecBridge {
 public:
  OHOSMediaCodecBridge() = default;

  OHOSMediaCodecBridge(const OHOSMediaCodecBridge&) = delete;
  OHOSMediaCodecBridge& operator=(const OHOSMediaCodecBridge&) = delete;

  virtual ~OHOSMediaCodecBridge() = default;

  virtual CodecCodeAdapter CreateVideoCodecByMime(
      const std::string mimetype) = 0;

  virtual CodecCodeAdapter CreateVideoCodecByName(const std::string name) = 0;

  virtual CodecCodeAdapter Configure(
      const CodecConfigPara& config,
      scoped_refptr<base::SequencedTaskRunner> codec_task_runner) = 0;

  virtual CodecCodeAdapter Prepare() = 0;

  virtual CodecCodeAdapter Start() = 0;

  virtual CodecCodeAdapter Stop() = 0;

  virtual CodecCodeAdapter Reset() = 0;

  virtual CodecCodeAdapter Release() = 0;

  virtual CodecCodeAdapter CreateInputSurface() = 0;

  virtual CodecCodeAdapter DequeueOutputBuffer(uint32_t& index,
                                               BufferInfo& info,
                                               BufferFlag& flag,
                                               OhosBuffer& buffer) = 0;
  virtual CodecCodeAdapter ReleaseOutputBuffer(uint32_t index, bool render) = 0;

  virtual void ClearKeyFrameCache() = 0;

  virtual CodecCodeAdapter RequestKeyFrameSoon() = 0;

  virtual CodecCodeAdapter FillSurfaceBuffer(scoped_refptr<VideoFrame> frame,
                                             const int64_t timestamp_ms) = 0;
};

}  // namespace media

#endif  // OHOS_MEDIA_CODEC_BRIAGE_H_
