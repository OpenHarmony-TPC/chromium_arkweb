// Copyright 2022 Huawei Device Co., Ltd.
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

#include "content/browser/media/session/audio_focus_delegate_ohos.h"

#include "audio_renderer_adapter.h"
#include "content/browser/media/session/audio_interrupt_adapter_impl.h"
#include "content/browser/media/session/media_session_impl.h"
#include "content/public/common/content_switches.h"
#include "media/base/media_switches.h"
#include "ohos_adapter_helper.h"

namespace content {
static std::shared_ptr<AudioInterruptAdapterImpl> kAudioInterrupt =
    std::make_shared<AudioInterruptAdapterImpl>();

AudioManagerCallback::AudioManagerCallback(MediaSessionImpl* media_session) {}

AudioManagerCallback::~AudioManagerCallback() {}

void AudioManagerCallback::OnSuspend() {}

void AudioManagerCallback::OnResume() {}

AudioFocusDelegateOHOS::AudioFocusDelegateOHOS(MediaSessionImpl* media_session)
    : media_session_(media_session) {}

AudioFocusDelegateOHOS::~AudioFocusDelegateOHOS() {}

AudioFocusDelegate::AudioFocusResult AudioFocusDelegateOHOS::RequestAudioFocus(
    media_session::mojom::AudioFocusType audio_focus_type) {
  int32_t ret = OhosAdapterHelper::GetInstance()
                    .GetAudioSystemManager()
                    .RequestAudioFocus(kAudioInterrupt);
  if (ret != AudioAdapterCode::AUDIO_OK) {
    LOG(ERROR) << "request audio focus failed";
    return AudioFocusDelegate::AudioFocusResult::kFailed;
  }

  if (!cb_) {
    cb_ = std::make_shared<AudioManagerCallback>(media_session_);
    ret = OhosAdapterHelper::GetInstance()
              .GetAudioSystemManager()
              .SetAudioManagerInterruptCallback(cb_);
    if (ret != AudioAdapterCode::AUDIO_OK) {
      LOG(ERROR) << "set audio interrupt callback failed";
      cb_.reset();
      return AudioFocusDelegate::AudioFocusResult::kFailed;
    }
  }

  return AudioFocusDelegate::AudioFocusResult::kSuccess;
}

void AudioFocusDelegateOHOS::AbandonAudioFocus() {
  (void)OhosAdapterHelper::GetInstance()
      .GetAudioSystemManager()
      .AbandonAudioFocus(kAudioInterrupt);
}

std::optional<media_session::mojom::AudioFocusType>
AudioFocusDelegateOHOS::GetCurrentFocusType() const {
  return media_session::mojom::AudioFocusType::kGain;
}

const base::UnguessableToken& AudioFocusDelegateOHOS::request_id() const {
  return base::UnguessableToken::Null();
}

// static
std::unique_ptr<AudioFocusDelegate> AudioFocusDelegate::Create(
    MediaSessionImpl* media_session) {
  AudioFocusDelegateOHOS* delegate = new AudioFocusDelegateOHOS(media_session);
  return std::unique_ptr<AudioFocusDelegate>(delegate);
}
}  // namespace content
                       