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

#ifndef MEDIA_BASE_OHOS_OHOS_MEDIA_CRYPTO_CONTEXT_IMPL_H_
#define MEDIA_BASE_OHOS_OHOS_MEDIA_CRYPTO_CONTEXT_IMPL_H_

#include "base/memory/raw_ptr.h"
#include "media/base/media_export.h"
#include "media/base/ohos/ohos_media_crypto_context.h"

namespace media {

class OHOSMediaDrmBridge;

class MEDIA_EXPORT OHOSMediaCryptoContextImpl final
    : public OHOSMediaCryptoContext {
 public:
  explicit OHOSMediaCryptoContextImpl(OHOSMediaDrmBridge* media_drm_bridge);

  OHOSMediaCryptoContextImpl(const OHOSMediaCryptoContextImpl&) = delete;
  OHOSMediaCryptoContextImpl& operator=(const OHOSMediaCryptoContextImpl&) =
      delete;

  ~OHOSMediaCryptoContextImpl() override;

  void SetOHOSMediaCryptoReadyCB(
      OHOSMediaCryptoReadyCB media_crypto_ready_cb) override;

#if BUILDFLAG(ARKWEB_ENABLE_WISEPLAY)
  void ReleaseInnerResource() override;
#endif
  
  std::vector<uint8_t> GetUUID() override;
 private:
  const raw_ptr<OHOSMediaDrmBridge> media_drm_bridge_;
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_OHOS_MEDIA_CRYPTO_CONTEXT_IMPL_H_
