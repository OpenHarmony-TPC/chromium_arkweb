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

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_MEDIA_CONTROLS_ELEMENTS_MEDIA_CONTROL_PLAYBACK_SPEED_LIST_ELEMENT_EXT_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_MEDIA_CONTROLS_ELEMENTS_MEDIA_CONTROL_PLAYBACK_SPEED_LIST_ELEMENT_EXT_H_

#include "third_party/blink/renderer/modules/media_controls/elements/media_control_playback_speed_list_element.h"

namespace blink {
class MediaControlPlaybackSpeedListElement;

class MediaControlPlaybackSpeedListElementExt : public MediaControlPlaybackSpeedListElement {
public:
  MediaControlPlaybackSpeedListElementExt(MediaControlsImpl& media_controls);

  blink::MediaControlPlaybackSpeedListElementExt* AsMediaControlPlaybackSpeedListElementExt() override {
      return this;
  }

#if BUILDFLAG(ARKWEB_VIDEO_ASSISTANT)
  void SetHrHidden(Event& event);
  void RemoveHrHidden(Event& event);
#endif

#if BUILDFLAG(ARKWEB_VIDEO_ASSISTANT)
  String CreatePlaybackSpeedLabelContentHM(const double playback_rate);
#endif

void DefaultEventHandlerExt(Event& event) override;

};

}

#endif // THIRD_PARTY_BLINK_RENDERER_MODULES_MEDIA_CONTROLS_ELEMENTS_MEDIA_CONTROL_PLAYBACK_SPEED_LIST_ELEMENT_EXT_H_