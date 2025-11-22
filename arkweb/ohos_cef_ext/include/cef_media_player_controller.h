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

#ifndef CEF_INCLUDE_CEF_MEDIA_PLAYER_CONTROLLER_H_
#define CEF_INCLUDE_CEF_MEDIA_PLAYER_CONTROLLER_H_

#include <cstdint>

class CefMediaPlayerController {
 public:
  virtual ~CefMediaPlayerController() = default;
  virtual void Play() {}
  virtual void Pause() {}
  virtual void Seek(double time) {}
  virtual void SetMuted(bool muted) {}
  virtual void SetPlaybackRate(double playback_rate) {}
  virtual void ExitFullscreen() {}
  virtual bool SetVideoSurface(void* native_window) { return false; }
  virtual void Download() {}
  virtual void SetVolume(double volume) {}
  virtual double GetVolume() { return 1.0; }
};

#endif // CEF_INCLUDE_CEF_MEDIA_PLAYER_CONTROLLER_H_