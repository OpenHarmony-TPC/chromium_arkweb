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

#ifndef CEF_LIBCEF_BROWSER_ALLOY_MEDIA_PLAYER_LISTENER_PROXY_H_
#define CEF_LIBCEF_BROWSER_ALLOY_MEDIA_PLAYER_LISTENER_PROXY_H_

#include <memory>
#include <utility>
#include "content/public/browser/media_player_listener.h"

class CefMediaPlayerListenerForVAST;

class MediaPlayerListenerProxy : public content::MediaPlayerListener {
 public:
  MediaPlayerListenerProxy(
      std::unique_ptr<CefMediaPlayerListenerForVAST> cef_listener);
  ~MediaPlayerListenerProxy() override;

  void OnStatusChanged(uint32_t status) override;
  void OnMutedChanged(bool muted) override;
  void OnPlaybackRateChanged(double playback_rate) override;
  void OnDurationChanged(double duration) override;
  void OnTimeUpdate(double current_time) override;
  void OnBufferedEndTimeChanged(double buffered_end_time) override;
  void OnEnded() override;
  void OnFullscreenChanged(bool fullscreen) override;
  void OnSeeking() override;
  void OnSeekFinished() override;
  void OnError(uint32_t error_code, const std::string& error_msg) override;
  void OnVideoSizeChanged(int width, int height) override;
  void OnFullscreenOverlayChanged(bool fullscreen_overlay) override;
  void OnVolumeChanged(double volume) override;

 private:
  std::unique_ptr<CefMediaPlayerListenerForVAST> cef_listener_;
};

#endif // CEF_LIBCEF_BROWSER_ALLOY_MEDIA_PLAYER_LISTENER_PROXY_H_
