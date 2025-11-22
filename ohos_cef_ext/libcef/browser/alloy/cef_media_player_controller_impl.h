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

#ifndef CEF_LIBCEF_BROWSER_ALLOY_CEF_MEDIA_PLAYER_CONTROLLER_IMPL_H_
#define CEF_LIBCEF_BROWSER_ALLOY_CEF_MEDIA_PLAYER_CONTROLLER_IMPL_H_

#include <memory>
#include <utility>
#include "include/cef_media_player_controller.h"

namespace content {
class MediaPlayerController;
} // namepsace content

class CefMediaPlayerControllerImpl : public CefMediaPlayerController {
 public:
  CefMediaPlayerControllerImpl(
      std::unique_ptr<content::MediaPlayerController> media_player_controller);
  ~CefMediaPlayerControllerImpl() override;
  void Play() override;
  void Pause() override;
  void Seek(double time) override;
  void SetMuted(bool muted) override;
  void SetPlaybackRate(double playback_rate) override;
  void ExitFullscreen() override;
  bool SetVideoSurface(void* native_window) override;
  void Download() override;
  void SetVolume(double volume) override;
  double GetVolume() override;
 private:
  std::unique_ptr<content::MediaPlayerController> media_player_controller_;
};

#endif // CEF_LIBCEF_BROWSER_ALLOY_CEF_MEDIA_PLAYER_CONTROLLER_IMPL_H_
