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

#ifndef MEDIA_AUDIO_OHOS_AUDIO_FOCUS_CONTROLLER_H_
#define MEDIA_AUDIO_OHOS_AUDIO_FOCUS_CONTROLLER_H_

#include "media/base/audio_parameters.h"
#include "content/browser/media/session/media_session_impl.h"
#include "content/public/browser/web_contents.h"

namespace media {
class OHOSAudioFocusController {
public:
  // OHOSAudioOutputStream mediaSession State
  static void OnSuspend(const AudioParameters& parameters);
  
  static MediaContentType GetMediaContentType(const AudioParameters& parameters);

  static bool IsActive(const AudioParameters& parameters);

  static bool HasOnlyOneShotPlayersPublic(const AudioParameters& parameters);

  static bool HasOneShotPlayersWhenSetMetadataPublic(const AudioParameters& parameters);

  static content::MediaSessionImpl::NWebMediaSessionState GetSessionState(const AudioParameters& parameters);

  static bool GetPlayingState(const AudioParameters& parameters);

  static bool GetMuteState(const AudioParameters& parameters);

  static void OneShotMediaPlayerStopped(const AudioParameters& parameters);

  static bool GetAudioExclusive(const AudioParameters& parameters);

  // AudioRendererCallback mediaSession State
  static int GetAudioResumeInterval(const AudioParameters& parameters);

  static int GetAudioSessionType(const AudioParameters& parameters);

  static void OnResume(const AudioParameters& parameters);

  static bool IsSuspended(const AudioParameters& parameters);

  static bool GetMediaPlayerMuteState(const AudioParameters& parameters);

private:
  // OHOSAudioOutputStream mediaSession State
  static bool CheckActiveOnUIThread(const AudioParameters& params);

  static MediaContentType GetContentTypeOnUIThread(const AudioParameters& params);

  static bool CheckOneShotPlayersOnUIThread(const AudioParameters& params);

  static bool CheckOneShotPlayersWhenSetMetadataOnUIThread(const AudioParameters& params);

  static content::MediaSessionImpl::NWebMediaSessionState
      CheckGetSessionStateOnUIThread(const AudioParameters& params);

  static bool CheckGetPlayingStateOnUIThread(const AudioParameters& params);

  static bool CheckGetMuteStateOnUIThread(const AudioParameters& params);

  static bool CheckGetAudioExclusiveUIThread(const AudioParameters& params);

  // AudioRendererCallback mediaSession State
  static int CheckGetAudioResumeIntervalUIThread(const AudioParameters& params);

  static int CheckGetAudioSessionTypeUIThread(const AudioParameters& params);

  static bool CheckIsSuspendedUIThread(const AudioParameters& params);

  static bool CheckGetMediaPlayerMuteStateOnUIThread(const AudioParameters& params);
};

} // media

#endif // MEDIA_AUDIO_OHOS_AUDIO_FOCUS_CONTROLLER_H_
