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

#ifndef CHROME_COMMON_MEDIA_CHROME_MEDIA_DRM_BRIDGE_CLIENT_OHOS_H_
#define CHROME_COMMON_MEDIA_CHROME_MEDIA_DRM_BRIDGE_CLIENT_OHOS_H_

#include "components/cdm/common/widevine_drm_delegate_ohos.h"
#include "media/base/ohos/ohos_media_drm_bridge_client.h"

class ChromeMediaDrmBridgeClientOHOS : public media::OHOSMediaDrmBridgeClient {
 public:
  explicit ChromeMediaDrmBridgeClientOHOS();

  ChromeMediaDrmBridgeClientOHOS(const ChromeMediaDrmBridgeClientOHOS&) = delete;
  ChromeMediaDrmBridgeClientOHOS& operator=(
      const ChromeMediaDrmBridgeClientOHOS&) = delete;

  ~ChromeMediaDrmBridgeClientOHOS() override;

 private:
  void AddKeySystemUUIDMappings(KeySystemUuidMap* map) override;
  media::OHOSMediaDrmBridgeDelegate* GetMediaDrmBridgeDelegate(
      const media::UUID& scheme_uuid) override;

  std::vector<std::string> key_system_uuid_mappings_;
  cdm::WidevineDrmDelegateOHOS widevine_delegate_;
};

#endif  // CHROME_COMMON_MEDIA_CHROME_MEDIA_DRM_BRIDGE_CLIENT_OHOS_H_
