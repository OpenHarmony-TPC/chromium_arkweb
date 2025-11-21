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

// Based on audio_focus_delegate_android.h originally written by
// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. 

#ifndef CONTENT_BROWSER_MEDIA_SESSION_AUDIO_FOCUS_DELEGATE_OHOS_H_
#define CONTENT_BROWSER_MEDIA_SESSION_AUDIO_FOCUS_DELEGATE_OHOS_H_

#include "audio_system_manager_adapter.h"
#include "content/browser/media/session/audio_focus_delegate.h"

namespace media_session {
namespace mojom {
enum class AudioFocusType;
}  // namespace mojom
}  // namespace media_session

namespace content {
using namespace OHOS::NWeb;
class AudioFocusDelegateOHOS;

class AudioManagerCallback : public AudioManagerCallbackAdapter {
 public:
  AudioManagerCallback(MediaSessionImpl* media_session);
  ~AudioManagerCallback();
  void OnSuspend() override;
  void OnResume() override;
};

class AudioFocusDelegateOHOS : public AudioFocusDelegate {
 public:
  explicit AudioFocusDelegateOHOS(MediaSessionImpl* media_session);
  ~AudioFocusDelegateOHOS() override;

  AudioFocusResult RequestAudioFocus(
      media_session::mojom::AudioFocusType audio_focus_type) override;
  void AbandonAudioFocus() override;
  std::optional<media_session::mojom::AudioFocusType> GetCurrentFocusType()
      const override;
  const base::UnguessableToken& request_id() const override;
  // This is not used by this delegate.
  void MediaSessionInfoChanged(
      const media_session::mojom::MediaSessionInfoPtr&) override {}
  void ReleaseRequestId() override {}

 private:
  raw_ptr<MediaSessionImpl> media_session_ = nullptr;
  std::shared_ptr<AudioManagerCallback> cb_ = nullptr;
};

}  // namespace content

#endif  // CONTENT_BROWSER_MEDIA_SESSION_AUDIO_FOCUS_DELEGATE_OHOS_H_
