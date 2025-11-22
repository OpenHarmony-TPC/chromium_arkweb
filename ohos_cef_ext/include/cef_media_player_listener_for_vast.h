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

#ifndef CEF_INCLUDE_CEF_MEDIA_PLAYER_LISTENER_FOR_VAST_H_
#define CEF_INCLUDE_CEF_MEDIA_PLAYER_LISTENER_FOR_VAST_H_

#include "build/build_config.h"
#include "cef/include/cef_base.h"

#if BUILDFLAG(IS_OHOS)

///
/// Class used to monitor custom media player status.
///
/*--cef(source=library)--*/
class CefMediaPlayerListenerForVAST {
 public:
  ///
  /// triggered on CefMediaPlayerListenerForVAST released
  ///
  /*--cef()--*/
  virtual ~CefMediaPlayerListenerForVAST() = default;

  ///
  /// triggered on video playing state changed
  ///
  /*--cef()--*/
  virtual void OnStatusChanged(uint32_t status) = 0;

  ///
  /// triggered on video mute state changed
  ///
  /*--cef()--*/
  virtual void OnMutedChanged(bool muted) = 0;

  ///
  /// triggered on video playback sppeed changed
  ///
  /*--cef()--*/
  virtual void OnPlaybackRateChanged(double playback_rate) = 0;

  ///
  /// triggered on vidoe duration changed
  ///
  /*--cef()--*/
  virtual void OnDurationChanged(double duration) = 0;

  ///
  /// triggered on video current playing time changed
  ///
  /*--cef()--*/
  virtual void OnTimeUpdate(double current_time) = 0;

  ///
  /// triggered on video buffered last length changed
  ///
  /*--cef()--*/
  virtual void OnBufferedEndTimeChanged(double buffered_time) = 0;

  ///
  /// triggered on video play at the end.
  ///
  /*--cef()--*/
  virtual void OnEnded() = 0;
  ///
  /// triggered on video fullscreen state changed.
  ///
  /*--cef()--*/
  virtual void OnFullscreenChanged(bool fullscreen) = 0;

  ///
  /// triggered on video is seeking
  ///
  /*--cef()--*/
  virtual void OnSeeking() = 0;

  ///
  /// triggered on video seek finished
  ///
  /*--cef()--*/
  virtual void OnSeekFinished() = 0;

  ///
  /// triggered on video playback error
  ///
  /*--cef()--*/
  virtual void OnError(uint32_t error_code, const std::string& error_msg) = 0;

  ///
  /// triggered on video size changed.
  ///
  /*--cef()--*/
  virtual void OnVideoSizeChanged(int width, int height) = 0;

  ///
  /// triggered on overlay changed.
  ///
  /*--cef()--*/
  virtual void OnFullscreenOverlayChanged(bool fullscreen_overlay) = 0;

  // triggered on volume changed.
  /*--cef()--*/
  virtual void OnVolumeChanged(double volume) {}
};

#endif // BUILDFLAG(IS_OHOS)

#endif // CEF_INCLUDE_CEF_MEDIA_PLAYER_LISTENER_FOR_VAST_H_
