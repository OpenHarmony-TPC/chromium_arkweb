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


#include "content/public/browser/custom_media_player.h"

namespace content {

int32_t CustomMediaPlayer::Initialize(const std::string& surface_id) {
  return 0;
}

void CustomMediaPlayer::UpdateLayerRect(int x, int y, int width, int height) {}
void CustomMediaPlayer::Play() {}
void CustomMediaPlayer::Pause() {}
void CustomMediaPlayer::Seek(double target_time) {}
void CustomMediaPlayer::SetVolume(double volume) {}
void CustomMediaPlayer::SetMuted(bool muted) {}
void CustomMediaPlayer::SetPlaybackRate(double rate) {}
void CustomMediaPlayer::Release() {}
void CustomMediaPlayer::EnterFullscreen() {}
void CustomMediaPlayer::ExitFullscreen() {}
void CustomMediaPlayer::ResumeMediaPlayer() {}
void CustomMediaPlayer::SuspendMediaPlayer(int suspend_type) {}

}  // namespace content
