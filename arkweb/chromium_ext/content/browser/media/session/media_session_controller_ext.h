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

#ifndef CONTENT_BROWSER_MEDIA_SESSION_MEDIA_SESSION_CONTROLLER_H_EXT_
#define CONTENT_BROWSER_MEDIA_SESSION_MEDIA_SESSION_CONTROLLER_H_EXT_

#include "content/browser/media/session/media_session_controller.h"

namespace content {

class MediaSessionController;

class MediaSessionControllerExt : public MediaSessionController {
public:
  MediaSessionControllerExt(const MediaPlayerId& id,
                            WebContentsImpl* web_contents);

#if BUILDFLAG(ARKWEB_MEDIA_POLICY)
  void OnSetHtmlPlayEnabled(int player_id, bool enabled) override;

  // Set whether to the HTML play can be used to control media
  void SetHtmlPlayEnabled(bool enabled);

  // Set whether to the HTML play can be used to  control media
  void SetSessionStateIfNeed(bool isNeedMediaSession);

  void HasOneShotPlayersWhenSetMetadata(media::MediaContentType media_content_type);
#endif  // BUILDFLAG(ARKWEB_MEDIA_POLICY)

#if BUILDFLAG(ARKWEB_MEDIA_AVSESSION)
  void OnEndAVSession(const MediaPlayerId& id, bool is_hidden);
#endif // ARKWEB_MEDIA_AVSESSION

  MediaSessionControllerExt* AsMediaSessionControllerExt() override {
    return this;
  }

#if BUILDFLAG(ARKWEB_PIP)
  void OnPictureInPictureStateChanged(
      const MediaPlayerId& id, uint32_t state, int32_t width, int32_t height);
#endif

#if BUILDFLAG(ARKWEB_MEDIA_MEMORY_PRESSURE)
  void OnNotifyMemoryLevel(int player_id, int32_t level) override;
#endif
};

}

#endif  // CONTENT_BROWSER_MEDIA_SESSION_MEDIA_SESSION_CONTROLLER_H_EXT_