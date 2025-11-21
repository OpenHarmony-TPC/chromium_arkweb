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

#ifndef MEDIA_BASE_OHOS_OHOS_MEDIA_DRM_BRIDGE_DELEGATE_H_
#define MEDIA_BASE_OHOS_OHOS_MEDIA_DRM_BRIDGE_DELEGATE_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "media/base/eme_constants.h"
#include "media/base/media_export.h"
#include "media/base/ohos/ohos_media_drm_bridge_client.h"

namespace media {

class MEDIA_EXPORT OHOSMediaDrmBridgeDelegate {
 public:
  OHOSMediaDrmBridgeDelegate();

  OHOSMediaDrmBridgeDelegate(const OHOSMediaDrmBridgeDelegate&) = delete;
  OHOSMediaDrmBridgeDelegate& operator=(const OHOSMediaDrmBridgeDelegate&) =
      delete;

  virtual ~OHOSMediaDrmBridgeDelegate();

  virtual const UUID GetUUID() const = 0;

  virtual bool OnCreateSession(
      const EmeInitDataType init_data_type,
      const std::vector<uint8_t>& init_data,
      std::vector<uint8_t>* init_data_out,
      std::vector<std::string>* optional_parameters_out);
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_OHOS_MEDIA_DRM_BRIDGE_DELEGATE_H_
