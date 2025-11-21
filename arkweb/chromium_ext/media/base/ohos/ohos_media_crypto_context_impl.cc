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

#include "media/base/ohos/ohos_media_crypto_context_impl.h"

#include "media/base/ohos/ohos_media_drm_bridge.h"
#if BUILDFLAG(ARKWEB_ENABLE_WISEPLAY)
#include "media/cdm/wiseplay_cdm_common.h"
#endif

namespace media {

OHOSMediaCryptoContextImpl::OHOSMediaCryptoContextImpl(
    OHOSMediaDrmBridge* media_drm_bridge)
    : media_drm_bridge_(media_drm_bridge) {
  DCHECK(media_drm_bridge_);
}

OHOSMediaCryptoContextImpl::~OHOSMediaCryptoContextImpl() = default;

void OHOSMediaCryptoContextImpl::SetOHOSMediaCryptoReadyCB(
    OHOSMediaCryptoReadyCB media_crypto_ready_cb) {
  LOG(INFO) << "[DRM]" << __func__;
  if (!media_drm_bridge_) {
    LOG(ERROR) << "[DRM]media_drm_bridge_ is nullptr.";
    return;
  }
#if BUILDFLAG(ARKWEB_ENABLE_WISEPLAY)
  std::vector<uint8_t> scheme_uuid = media_drm_bridge_->GetSchemeUUID();
  if (base::ranges::equal(scheme_uuid, kWiseplayUuid)) {
    LOG(INFO) << "[DRM]" << __func__ << ", Wiseplay.";
    media_drm_bridge_->SetOHOSMediaCryptoAndLicenseReadyCB(
        std::move(media_crypto_ready_cb));
    return;
  }
#endif
  media_drm_bridge_->SetOHOSMediaCryptoReadyCB(
      std::move(media_crypto_ready_cb));
}

#if BUILDFLAG(ARKWEB_ENABLE_WISEPLAY)
void OHOSMediaCryptoContextImpl::ReleaseInnerResource() {
  if (!media_drm_bridge_) {
    LOG(ERROR) << "[DRM]media_drm_bridge_ is nullptr.";
    return;
  }
  media_drm_bridge_->ReleaseInnerResource();
}
#endif

std::vector<uint8_t> OHOSMediaCryptoContextImpl::GetUUID() {
  return media_drm_bridge_ ? media_drm_bridge_->GetSchemeUUID() : std::vector<uint8_t>{};
}
}  // namespace media
