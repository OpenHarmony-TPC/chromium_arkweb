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

#ifndef COMPONENTS_CDM_COMMON_WIDEVINE_DRM_DELEGATE_OHOS_H_
#define COMPONENTS_CDM_COMMON_WIDEVINE_DRM_DELEGATE_OHOS_H_

#include <stdint.h>

#include "media/base/ohos/ohos_media_drm_bridge_delegate.h"

namespace cdm {

class WidevineDrmDelegateOHOS : public media::OHOSMediaDrmBridgeDelegate {
 public:
  WidevineDrmDelegateOHOS();

  WidevineDrmDelegateOHOS(const WidevineDrmDelegateOHOS&) = delete;
  WidevineDrmDelegateOHOS& operator=(const WidevineDrmDelegateOHOS&) = delete;

  ~WidevineDrmDelegateOHOS() override;

  const std::vector<uint8_t> GetUUID() const override;
  bool OnCreateSession(
      const media::EmeInitDataType init_data_type,
      const std::vector<uint8_t>& init_data,
      std::vector<uint8_t>* init_data_out,
      std::vector<std::string>* optional_parameters_out) override;
};

}  // namespace cdm

#endif  // COMPONENTS_CDM_COMMON_WIDEVINE_DRM_DELEGATE_OHOS_H_
