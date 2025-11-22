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


#include "cef/ohos_cef_ext/libcef/browser/alloy/custom_media_player_proxy.h"

CustomMediaPlayerProxy::CustomMediaPlayerProxy(
    CefOwnPtr<CefCustomMediaPlayerDelegate> delegate)
    : delegate_(std::move(delegate)) {}
CustomMediaPlayerProxy::~CustomMediaPlayerProxy() = default;

void CustomMediaPlayerProxy::UpdateLayerRect(int x,
                                             int y,
                                             int width,
                                             int height) {
  if (delegate_) {
    delegate_->UpdateLayerRect(x, y, width, height);
  }
}
void CustomMediaPlayerProxy::Play() {
  if (delegate_) {
    delegate_->Play();
  }
}
void CustomMediaPlayerProxy::Pause() {
  if (delegate_) {
    delegate_->Pause();
  }
}
void CustomMediaPlayerProxy::Seek(double target_time) {
  if (delegate_) {
    delegate_->Seek(target_time);
  }
}
void CustomMediaPlayerProxy::SetVolume(double volume) {
  if (delegate_) {
    delegate_->SetVolume(volume);
  }
}
void CustomMediaPlayerProxy::SetMuted(bool muted) {
  if (delegate_) {
    delegate_->SetMuted(muted);
  }
}
void CustomMediaPlayerProxy::SetPlaybackRate(double rate) {
  if (delegate_) {
    delegate_->SetPlaybackRate(rate);
  }
}
void CustomMediaPlayerProxy::Release() {
  if (delegate_) {
    delegate_->Release();
  }
}
void CustomMediaPlayerProxy::EnterFullscreen() {
  if (delegate_) {
    delegate_->EnterFullscreen();
  }
}
void CustomMediaPlayerProxy::ExitFullscreen() {
  if (delegate_) {
    delegate_->ExitFullscreen();
  }
}
void CustomMediaPlayerProxy::ResumeMediaPlayer() {
  if (delegate_) {
    delegate_->ResumeMediaPlayer();
  }
}
void CustomMediaPlayerProxy::SuspendMediaPlayer(int suspend_type) {
  if (delegate_) {
    delegate_->SuspendMediaPlayer(suspend_type);
  }
}
