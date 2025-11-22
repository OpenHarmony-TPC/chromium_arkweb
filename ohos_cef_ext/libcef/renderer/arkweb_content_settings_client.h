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

#ifndef CEF_OHOS_CEF_EXT_LIBCEF_RENDERER_ARKWEB_CONTENT_SETTINGS_CLIENT_H_
#define CEF_OHOS_CEF_EXT_LIBCEF_RENDERER_ARKWEB_CONTENT_SETTINGS_CLIENT_H_

#include "content/public/renderer/render_frame_observer.h"
#include "third_party/blink/public/platform/web_content_settings_client.h"

// NWeb implementation of blink::WebContentSettingsClient.
class ArkWebContentSettingsClient : public content::RenderFrameObserver,
                                    public blink::WebContentSettingsClient {
 public:
  ArkWebContentSettingsClient(const ArkWebContentSettingsClient&) = delete;
  ArkWebContentSettingsClient& operator=(const ArkWebContentSettingsClient&) =
      delete;

  explicit ArkWebContentSettingsClient(content::RenderFrame* render_view);

 private:
  ~ArkWebContentSettingsClient() override;

  // content::RenderFrameObserver implementation.
  void OnDestruct() override;

  bool ShouldAutoupgradeMixedContent() override;
#ifdef BUILDFLAG(ARKWEB_ARKWEB_EXTENSIONS)
  bool AllowWriteToClipboard() override;
#endif
};

#endif  // CEF_OHOS_CEF_EXT_LIBCEF_RENDERER_ARKWEB_CONTENT_SETTINGS_CLIENT_H_
