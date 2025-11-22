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

#include "ohos_nweb/src/video_assistant/nweb_media_player_controller_impl.h"

#include <utility>
#include <cstdint>
#include "base/logging.h"
#include "cef/ohos_cef_ext/include/cef_media_player_controller.h"
#include "gpu/ipc/common/nweb_native_window_tracker.h"
#include "arkweb/ohos_adapter_ndk/ohos_adapter_helper_ext.h"

namespace OHOS::NWeb {

NWebMediaPlayerControllerImpl::NWebMediaPlayerControllerImpl(
    std::unique_ptr<CefMediaPlayerController> controller)
    : cef_controller_(std::move(controller)) {}

NWebMediaPlayerControllerImpl::~NWebMediaPlayerControllerImpl() = default;

void NWebMediaPlayerControllerImpl::Play() {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::Play()";
  if (cef_controller_) {
    cef_controller_->Play();
  }
}

void NWebMediaPlayerControllerImpl::Pause() {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::Pause()";
  if (cef_controller_) {
    cef_controller_->Pause();
  }
}

void NWebMediaPlayerControllerImpl::Seek(double time) {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::Seek(" << time << ")";
  if (cef_controller_) {
    cef_controller_->Seek(time);
  }
}

void NWebMediaPlayerControllerImpl::SetMuted(bool muted) {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::SetMuted(" << muted << ")";
  if (cef_controller_) {
    cef_controller_->SetMuted(muted);
  }
}

void NWebMediaPlayerControllerImpl::SetPlaybackRate(double playback_rate) {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::SetPlaybackRate(" << playback_rate << ")";
  if (cef_controller_) {
    cef_controller_->SetPlaybackRate(playback_rate);
  }
}

void NWebMediaPlayerControllerImpl::ExitFullscreen() {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::ExitFullscreen()";
  if (cef_controller_) {
    cef_controller_->ExitFullscreen();
  }
}

void NWebMediaPlayerControllerImpl::SetVideoSurface(void* native_window) {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::SetVideoSurface";
  bool success = false;
  if (cef_controller_) {
    success = cef_controller_->SetVideoSurface(native_window);
  }
  if (!success) {
    OHOS::NWeb::OhosAdapterHelperExt::GetWindowAdapterNdkInstance()
        .DestroyNativeWindow(native_window);
  }
}

void NWebMediaPlayerControllerImpl::Download() {
  LOG(INFO) << "NWebMediaPlayerControllerImpl::Download()";
  if (cef_controller_) {
    cef_controller_->Download();
  }
}

void NWebMediaPlayerControllerImpl::SetVolume(double volume)
{
  LOG(INFO) << "NWebMediaPlayerControllerImpl::SetVolume volume=" << volume;
  if (cef_controller_) {
    cef_controller_->SetVolume(volume);
  }
}

double NWebMediaPlayerControllerImpl::GetVolume()
{
  LOG(INFO) << "NWebMediaPlayerControllerImpl::GetVolume()";
  if (cef_controller_) {
    return cef_controller_->GetVolume();
  }
  return -1.0;
}

} // namespace OHOS::NWeb