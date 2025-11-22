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

#include "components/cdm/common/widevine_drm_delegate_ohos.h"

#include "base/logging.h"
#include "media/cdm/cenc_utils.h"

namespace cdm {

namespace {

const uint8_t kWidevineUuid[16] = {
    0xED, 0xEF, 0x8B, 0xA9, 0x79, 0xD6, 0x4A, 0xCE,  //
    0xA3, 0xC8, 0x27, 0xDC, 0xD5, 0x1D, 0x21, 0xED};
}  // namespace

WidevineDrmDelegateOHOS::WidevineDrmDelegateOHOS() {}

WidevineDrmDelegateOHOS::~WidevineDrmDelegateOHOS() {}

const std::vector<uint8_t> WidevineDrmDelegateOHOS::GetUUID() const {
  return std::vector<uint8_t>(kWidevineUuid,
                              kWidevineUuid + std::size(kWidevineUuid));
}

bool WidevineDrmDelegateOHOS::OnCreateSession(
    const media::EmeInitDataType init_data_type,
    const std::vector<uint8_t>& init_data,
    std::vector<uint8_t>* init_data_out,
    std::vector<std::string>* /* optional_parameters_out */) {
  LOG(INFO) << "[DRM]" << __func__;
  if (init_data_type != media::EmeInitDataType::CENC) {
    return true;
  }
  return media::GetPsshData(init_data, GetUUID(), init_data_out);
}

}  // namespace cdm
