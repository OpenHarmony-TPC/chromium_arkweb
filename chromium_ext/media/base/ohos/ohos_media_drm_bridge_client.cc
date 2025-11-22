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

#include "media/base/ohos/ohos_media_drm_bridge_client.h"

#include "base/check.h"
#include "base/logging.h"

namespace media {

static OHOSMediaDrmBridgeClient* g_media_drm_bridge_client = nullptr;

void SetMediaDrmBridgeClient(OHOSMediaDrmBridgeClient* media_client) {
  DCHECK(!g_media_drm_bridge_client);
  g_media_drm_bridge_client = media_client;
}

OHOSMediaDrmBridgeClient* GetMediaDrmBridgeClient() {
  return g_media_drm_bridge_client;
}

OHOSMediaDrmBridgeClient::OHOSMediaDrmBridgeClient() {}

OHOSMediaDrmBridgeClient::~OHOSMediaDrmBridgeClient() {}

void OHOSMediaDrmBridgeClient::AddKeySystemUUIDMappings(KeySystemUuidMap* map) {
}

media::OHOSMediaDrmBridgeDelegate* OHOSMediaDrmBridgeClient::GetMediaDrmBridgeDelegate(
    const std::vector<uint8_t>& scheme_uuid) {
  return nullptr;
}

}  // namespace media
