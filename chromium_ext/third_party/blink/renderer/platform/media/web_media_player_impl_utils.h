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

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_MEDIA_WEB_MEDIA_PLAYER_IMPL_UTILS_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_MEDIA_WEB_MEDIA_PLAYER_IMPL_UTILS_H_

namespace blink {
class WebMediaPlayerImpl;

class WebMediaPlayerImplUtils {
public:
  raw_ptr<WebMediaPlayerImpl> impl = nullptr;
  WebMediaPlayerImplUtils(WebMediaPlayerImpl* WebMediaPlayerImpl);
  void ExitedFullscreenExt();
  bool DoLoadExt(WebMediaPlayer::CorsMode cors_mode, bool is_cache_disabled);
  void PlayExt();
  void PlayCapabilitiesExt();
  void PauseCapabilitiesExt();
  void OnMetadataExt();
  void OnPageHiddenExt(bool storing_in_bfcache);
  void CreateRendererExtSetRendererType();
  std::unique_ptr<media::Renderer> CreateRendererExtConfigRenderer(media::RequestOverlayInfoCB request_overlay_info_cb);
  void SetSuspendStateExt();
  void OnIdleTimeoutExt();
  void PauseExt();
  void DoSeekExt(base::TimeDelta time);
  void SetVolumeExt(double volume);
  void OnFrameShownExt();
  void OnFrameHiddenExt();
  void SetPosterExt(const WebURL& poster);
  bool UpdatePlayStateExt(bool can_auto_suspend);
  void SetDelegateStateExt();
  void UpdatePlayState_ComputePlayStateExt(bool& idle_suspended, bool& can_stay_suspended);
  void OnVideoNaturalSizeChangeExt();
  void DidEndAVSessionExt();
  void SuspendCdmSessionExt();
  void ResumeCdmSessionExt();
};

}

#endif //THIRD_PARTY_BLINK_RENDERER_PLATFORM_MEDIA_WEB_MEDIA_PLAYER_IMPL_UTILS_H_
