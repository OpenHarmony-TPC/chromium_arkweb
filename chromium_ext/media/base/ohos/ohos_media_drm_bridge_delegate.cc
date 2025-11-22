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

#include "media/base/ohos/ohos_media_drm_bridge_delegate.h"

#include "base/check.h"
#include "base/logging.h"

namespace media {

OHOSMediaDrmBridgeDelegate::OHOSMediaDrmBridgeDelegate() {}

OHOSMediaDrmBridgeDelegate::~OHOSMediaDrmBridgeDelegate() {}

bool OHOSMediaDrmBridgeDelegate::OnCreateSession(
    const EmeInitDataType init_data_type,
    const std::vector<uint8_t>& init_data,
    std::vector<uint8_t>* init_data_out,
    std::vector<std::string>* optional_parameters_out) {
  LOG(INFO) << "[DRM]" << __func__;
  DCHECK(init_data_out->empty());
  DCHECK(optional_parameters_out->empty());
  LOG(INFO) << "[DRM]" << __func__;
  return true;
}

}  // namespace media
