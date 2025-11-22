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

#ifndef MEDIA_BASE_OHOS_OHOS_MEDIA_CRYPTO_CONTEXT_H_
#define MEDIA_BASE_OHOS_OHOS_MEDIA_CRYPTO_CONTEXT_H_

#include <memory>

#include "base/functional/callback.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT OHOSMediaCryptoContext {
 public:
  OHOSMediaCryptoContext() = default;

  OHOSMediaCryptoContext(const OHOSMediaCryptoContext&) = delete;
  OHOSMediaCryptoContext& operator=(const OHOSMediaCryptoContext&) = delete;

  using OHOSMediaCryptoReadyCB =
      base::OnceCallback<void(void* session, bool requires_secure_video_codec)>;

  virtual ~OHOSMediaCryptoContext() = default;

  virtual void SetOHOSMediaCryptoReadyCB(
      OHOSMediaCryptoReadyCB media_crypto_ready_cb) = 0;

#if BUILDFLAG(ARKWEB_ENABLE_WISEPLAY)
  virtual void ReleaseInnerResource() = 0;
#endif

  virtual std::vector<uint8_t> GetUUID() = 0;
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_OHOS_MEDIA_CRYPTO_CONTEXT_H_
