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

#include "libcef/browser/alloy/media_player_listener_proxy.h"

#include "include/cef_media_player_listener_for_vast.h"

MediaPlayerListenerProxy::MediaPlayerListenerProxy(
    std::unique_ptr<CefMediaPlayerListenerForVAST> cef_listener)
    : cef_listener_(std::move(cef_listener)) {}
MediaPlayerListenerProxy::~MediaPlayerListenerProxy() = default;

void MediaPlayerListenerProxy::OnStatusChanged(uint32_t status) {
  if (cef_listener_) {
    cef_listener_->OnStatusChanged(status);
  }
}

void MediaPlayerListenerProxy::OnMutedChanged(bool muted) {
  if (cef_listener_) {
    cef_listener_->OnMutedChanged(muted);
  }
}
void MediaPlayerListenerProxy::OnPlaybackRateChanged(double playback_rate) {
  if (cef_listener_) {
    cef_listener_->OnPlaybackRateChanged(playback_rate);
  }
}
void MediaPlayerListenerProxy::OnDurationChanged(double duration) {
  if (cef_listener_) {
    cef_listener_->OnDurationChanged(duration);
  }
}
void MediaPlayerListenerProxy::OnTimeUpdate(double current_time) {
  if (cef_listener_) {
    cef_listener_->OnTimeUpdate(current_time);
  }
}
void MediaPlayerListenerProxy::OnBufferedEndTimeChanged(double buffered_end_time) {
  if (cef_listener_) {
    cef_listener_->OnBufferedEndTimeChanged(buffered_end_time);
  }
}
void MediaPlayerListenerProxy::OnEnded() {
  if (cef_listener_) {
    cef_listener_->OnEnded();
  }
}
void MediaPlayerListenerProxy::OnFullscreenChanged(bool fullscreen) {
  if (cef_listener_) {
    cef_listener_->OnFullscreenChanged(fullscreen);
  }
}
void MediaPlayerListenerProxy::OnSeeking() {
  if (cef_listener_) {
    cef_listener_->OnSeeking();
  }
}
void MediaPlayerListenerProxy::OnSeekFinished() {
  if (cef_listener_) {
    cef_listener_->OnSeekFinished();
  }
}
void MediaPlayerListenerProxy::OnError(uint32_t error_code, const std::string& error_msg) {
  if (cef_listener_) {
    cef_listener_->OnError(error_code, error_msg);
  }
}
void MediaPlayerListenerProxy::OnVideoSizeChanged(int width, int height) {
  if (cef_listener_) {
    cef_listener_->OnVideoSizeChanged(width, height);
  }
}
void MediaPlayerListenerProxy::OnFullscreenOverlayChanged(bool fullscreen_overlay) {
  if (cef_listener_) {
    cef_listener_->OnFullscreenOverlayChanged(fullscreen_overlay);
  }
}

void MediaPlayerListenerProxy::OnVolumeChanged(double volume)
{
  if (cef_listener_) {
    cef_listener_->OnVolumeChanged(volume);
  }
}