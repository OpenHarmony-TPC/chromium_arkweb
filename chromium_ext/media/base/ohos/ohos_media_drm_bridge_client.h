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

#ifndef MEDIA_BASE_OHOS_OHOS_MEDIA_DRM_BRIDGE_CLIENT_H_
#define MEDIA_BASE_OHOS_OHOS_MEDIA_DRM_BRIDGE_CLIENT_H_

#include <stdint.h>

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "media/base/media_export.h"

namespace media {

class OHOSMediaDrmBridgeClient;
class OHOSMediaDrmBridgeDelegate;

MEDIA_EXPORT void SetMediaDrmBridgeClient(
    OHOSMediaDrmBridgeClient* media_client);

#if defined(IS_MEDIA_IMPL)
OHOSMediaDrmBridgeClient* GetMediaDrmBridgeClient();
#endif

using UUID = std::vector<uint8_t>;

class MEDIA_EXPORT OHOSMediaDrmBridgeClient {
 public:
  typedef std::unordered_map<std::string, UUID> KeySystemUuidMap;

  OHOSMediaDrmBridgeClient();

  OHOSMediaDrmBridgeClient(const OHOSMediaDrmBridgeClient&) = delete;
  OHOSMediaDrmBridgeClient& operator=(const OHOSMediaDrmBridgeClient&) = delete;

  virtual ~OHOSMediaDrmBridgeClient();

  virtual void AddKeySystemUUIDMappings(KeySystemUuidMap* map);

  virtual media::OHOSMediaDrmBridgeDelegate* GetMediaDrmBridgeDelegate(
      const UUID& scheme_uuid);

 private:
  friend class KeySystemManager;
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_OHOS_MEDIA_DRM_BRIDGE_CLIENT_H_
