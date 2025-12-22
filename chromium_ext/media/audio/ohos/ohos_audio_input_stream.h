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

#ifndef MEDIA_AUDIO_OHOS_AUDIO_INPUT_STREAM_H_
#define MEDIA_AUDIO_OHOS_AUDIO_INPUT_STREAM_H_

#include "base/feature_list.h"
#include "base/logging.h"
#include "base/timer/timer.h"
#include "media/audio/audio_io.h"
#include "media/audio/ohos/ohos_audio_capturer_source.h"
#include "media/audio/ohos/ohos_audio_manager.h"
#include "media/base/audio_parameters.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/audio_capturer_adapter.h"
#include "third_party/webrtc/modules/desktop_capture/ohos/base_audio_capturer_source.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/audio_renderer_adapter.h"

namespace content {
  class WebContents;
  class MediaSessionImpl;
}

namespace media {
using namespace OHOS::NWeb;
using namespace webrtc;

class OHOSAudioManager;

class OHOSAudioInputStream : public AudioInputStream {
 public:
  // Caller must ensure that manager outlives the stream.
  OHOSAudioInputStream(OHOSAudioManager* manager,
                       const AudioParameters& parameters);

  OpenOutcome Open() override;
  void Start(AudioInputCallback* callback) override;
  void Stop() override;
  void Close() override;
  double GetMaxVolume() override;
  void SetVolume(double volume) override;
  double GetVolume() override;
  bool SetAutomaticGainControl(bool enabled) override;
  bool GetAutomaticGainControl() override;
  bool IsMuted() override;
  void SetOutputDeviceForAec(const std::string& output_device_id) override;
  static int GetNWebId(const AudioParameters& params);
  static int GetNWebIdOnUIThread(const AudioParameters& params);

 private:
  class CaptureCallbackAdapter;

  ~OHOSAudioInputStream() override;

  raw_ptr<OHOSAudioManager> const manager_;
  AudioParameters parameters_;
  std::unique_ptr<CaptureCallbackAdapter> callback_adapter_;
  scoped_refptr<OHOSAudioCapturerSource> capturer_source_;
  double volume_ = 1.0;
  bool automatic_gain_control_ = false;

  std::unique_ptr<CaptureCallbackAdapter> base_callback_adapter_;
  scoped_refptr<BaseAudioCapturerSource> base_capturer_source_;
};

}  // namespace media

#endif  // MEDIA_AUDIO_OHOS_AUDIO_INPUT_STREAM_H_
