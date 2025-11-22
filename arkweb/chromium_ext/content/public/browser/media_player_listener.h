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

#ifndef CONTENT_PUBLIC_BROWSER_MEDIA_PLAYER_LISTENER_H_
#define CONTENT_PUBLIC_BROWSER_MEDIA_PLAYER_LISTENER_H_

#include <cstdint>
#include <string>

namespace content {

class MediaPlayerListener {
 public:
  virtual ~MediaPlayerListener() = default;
  virtual void OnStatusChanged(uint32_t status) {}
  virtual void OnMutedChanged(bool muted) {}
  virtual void OnPlaybackRateChanged(double playback_rate) {}
  virtual void OnDurationChanged(double duration) {}
  virtual void OnTimeUpdate(double current_time) {}
  virtual void OnBufferedEndTimeChanged(double buffered_end_time) {}
  virtual void OnEnded() {}
  virtual void OnFullscreenChanged(bool fullscreen) {}
  virtual void OnSeeking() {}
  virtual void OnSeekFinished() {}
  virtual void OnError(uint32_t error_code, const std::string& error_msg) {}
  virtual void OnVideoSizeChanged(int width, int height) {}
  virtual void OnFullscreenOverlayChanged(bool fullscreen_overlay) {}
  virtual void OnVolumeChanged(double volume) {}
};

} // namepsace content

#endif // CONTENT_PUBLIC_BROWSER_MEDIA_PLAYER_LISTENER_H_
