
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

#ifndef CONTENT_PUBLIC_BROWSER_CUSTOM_MEDIA_PLAYER_H_
#define CONTENT_PUBLIC_BROWSER_CUSTOM_MEDIA_PLAYER_H_

#include <cstdint>
#include <string>

namespace content {

class CustomMediaPlayer {
 public:
  virtual ~CustomMediaPlayer() = default;

  virtual int32_t Initialize(const std::string& surface_id);
  virtual void UpdateLayerRect(int x, int y, int width, int height);
  virtual void Play();
  virtual void Pause();
  virtual void Seek(double target_time);
  virtual void SetVolume(double volume);
  virtual void SetMuted(bool muted);
  virtual void SetPlaybackRate(double rate);
  virtual void Release();
  virtual void EnterFullscreen();
  virtual void ExitFullscreen();
  virtual void ResumeMediaPlayer();
  virtual void SuspendMediaPlayer(int suspend_type);
};

}  // namespace content

#endif  // CONTENT_PUBLIC_BROWSER_CUSTOM_MEDIA_PLAYER_H_
