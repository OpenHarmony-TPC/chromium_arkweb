// Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "content/browser/speech/tts_platform_impl.h"

#include "base/functional/callback.h"
#include "base/no_destructor.h"

namespace content {

// Dummy implementation to prevent a browser crash
class TtsPlatformImplOHOS : public TtsPlatformImpl {
 public:
  TtsPlatformImplOHOS() = default;
  TtsPlatformImplOHOS(const TtsPlatformImplOHOS&) = delete;
  TtsPlatformImplOHOS& operator=(const TtsPlatformImplOHOS&) = delete;

  // TtsPlatform implementation.
  bool PlatformImplSupported() override { return false; }
  bool PlatformImplInitialized() override { return false; }
  void Speak(int utterance_id,
             const std::string& utterance,
             const std::string& lang,
             const VoiceData& voice,
             const UtteranceContinuousParameters& params,
             base::OnceCallback<void(bool)> on_speak_finished) override {
    std::move(on_speak_finished).Run(false);
  }
  bool StopSpeaking() override { return false; }
  bool IsSpeaking() override { return false; }
  void GetVoices(std::vector<VoiceData>* out_voices) override {}
  void Pause() override {}
  void Resume() override {}

  // Get the single instance of this class.
  static TtsPlatformImplOHOS* GetInstance() {
    static base::NoDestructor<TtsPlatformImplOHOS> tts_platform;
    return tts_platform.get();
  }
};

// static
TtsPlatformImpl* TtsPlatformImpl::GetInstance() {
  return TtsPlatformImplOHOS::GetInstance();
}

}  // namespace content
