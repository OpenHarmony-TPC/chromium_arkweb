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

#include "third_party/blink/renderer/modules/media_controls/elements/media_control_entered_fullscreen_title_display_element_ext.h"

#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/dom_token_list.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/html/media/html_media_element.h"
#include "third_party/blink/renderer/core/page/page.h"
#include "third_party/blink/renderer/modules/media_controls/media_controls_impl.h"
#include "third_party/blink/renderer/platform/wtf/text/unicode.h"
#include "arkweb/chromium_ext/third_party/blink/renderer/core/html/media/html_media_element_utils.h"

namespace blink {

MediaControlEnteredFullscreenTitleDisplayElement::
    MediaControlEnteredFullscreenTitleDisplayElement(
        MediaControlsImpl& media_controls)
    : MediaControlDivElement(media_controls) {
  SetShadowPseudoId(AtomicString(
      "-internal-media-controls-entered-fullscreen-title-display"));
  title_span_ = MakeGarbageCollected<HTMLDivElement>(GetDocument());
  title_span_->SetShadowPseudoId(
      AtomicString("-internal-media-controls-entered-fullscreen-title-item"));
  this->ParserAppendChild(title_span_);
  UpdateTitle();
}

void MediaControlEnteredFullscreenTitleDisplayElement::UpdateTitle() {
  SetTitle(MediaElement().html_media_element_utils_.GetTitle());
}

void MediaControlEnteredFullscreenTitleDisplayElement::SetTitle(
    const String& title) {
  if (title_ == title) {
    return;
  }
  title_ = title;

  bool isRTL = false;
  for (unsigned i = 0; i < title_.length(); ++i) {
    auto direction = WTF::unicode::Direction(title_[i]);
    if (direction == WTF::unicode::kRightToLeft ||
        direction == WTF::unicode::kRightToLeftArabic ||
        direction == WTF::unicode::kRightToLeftEmbedding ||
        direction == WTF::unicode::kRightToLeftOverride) {
      isRTL = true;
      break;
    } else if (direction == WTF::unicode::kLeftToRight ||
               direction == WTF::unicode::kLeftToRightEmbedding ||
               direction == WTF::unicode::kLeftToRightOverride) {
      isRTL = false;
      break;
    }
  }
  SetClass(AtomicString("rtl_lang"), isRTL);
  title_span_->setInnerText(title_);
}

void MediaControlEnteredFullscreenTitleDisplayElement::Trace(
    blink::Visitor* visitor) const {
  MediaControlDivElement::Trace(visitor);
  visitor->Trace(title_span_);
}

}  // namespace blink
                     