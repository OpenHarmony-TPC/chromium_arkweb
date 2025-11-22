// Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "ohos_cef_ext/libcef/renderer/arkweb_content_settings_client.h"

#include "content/public/renderer/render_frame.h"
#include "third_party/blink/public/common/web_preferences/web_preferences.h"
#include "third_party/blink/public/web/web_local_frame.h"
#ifdef BUILDFLAG(ARKWEB_ARKWEB_EXTENSIONS)
#include "content/renderer/render_frame_impl.h"
#endif

ArkWebContentSettingsClient::ArkWebContentSettingsClient(
    content::RenderFrame* render_frame)
    : content::RenderFrameObserver(render_frame) {
  render_frame->GetWebFrame()->SetContentSettingsClient(this);
}

ArkWebContentSettingsClient::~ArkWebContentSettingsClient() {}

bool ArkWebContentSettingsClient::ShouldAutoupgradeMixedContent() {
  return render_frame()->GetBlinkPreferences().allow_mixed_content_upgrades;
}

#ifdef BUILDFLAG(ARKWEB_ARKWEB_EXTENSIONS)
bool ArkWebContentSettingsClient::AllowWriteToClipboard() {
  content::RenderFrameImpl* impl =
     static_cast<content::RenderFrameImpl*>(render_frame());
  return impl ? impl->IsOffscreen() : false;
}
#endif

void ArkWebContentSettingsClient::OnDestruct() {
  delete this;
}
