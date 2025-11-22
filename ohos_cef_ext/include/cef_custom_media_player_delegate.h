
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CEF_INCLUDE_CEF_CUSTOM_MEDIA_PLAYER_DELEGATE_H_
#define CEF_INCLUDE_CEF_CUSTOM_MEDIA_PLAYER_DELEGATE_H_

#include <cstdint>
#include <string>

class CefCustomMediaPlayerDelegate {
 public:
  virtual ~CefCustomMediaPlayerDelegate() = default;

  virtual void UpdateLayerRect(int x, int y, int width, int height) = 0;
  virtual void Play() = 0;
  virtual void Pause() = 0;
  virtual void Seek(double target_time) = 0;
  virtual void SetVolume(double volume) = 0;
  virtual void SetMuted(bool muted) = 0;
  virtual void SetPlaybackRate(double rate) = 0;
  virtual void Release() = 0;
  virtual void EnterFullscreen() = 0;
  virtual void ExitFullscreen() = 0;
  virtual void ResumeMediaPlayer() = 0;
  virtual void SuspendMediaPlayer(int suspend_type) = 0;
};

#endif  // CEF_INCLUDE_CEF_CUSTOM_MEDIA_PLAYER_DELEGATE_H_
