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

#ifndef MEDIA_BASE_OHOS_OHOS_CDM_FACTORY_H_
#define MEDIA_BASE_OHOS_OHOS_CDM_FACTORY_H_

#include <stdint.h>

#include <utility>

#include "base/containers/flat_map.h"
#include "base/memory/weak_ptr.h"
#include "media/base/cdm_factory.h"
#include "media/base/media_export.h"
#include "media/base/ohos/ohos_media_drm_bridge_factory.h"
#include "media/base/provision_fetcher.h"

namespace media {

struct CdmConfig;

class MEDIA_EXPORT OHOSCdmFactory final : public CdmFactory {
 public:
  OHOSCdmFactory(CreateFetcherCB create_fetcher_cb,
                 CreateStorageCB create_storage_cb);

  OHOSCdmFactory(const OHOSCdmFactory&) = delete;
  OHOSCdmFactory& operator=(const OHOSCdmFactory&) = delete;

  ~OHOSCdmFactory() override;

  // CdmFactory implementation.
  void Create(const CdmConfig& cdm_config,
              const SessionMessageCB& session_message_cb,
              const SessionClosedCB& session_closed_cb,
              const SessionKeysChangeCB& session_keys_change_cb,
              const SessionExpirationUpdateCB& session_expiration_update_cb,
              CdmCreatedCB cdm_created_cb) override;

 private:
  // Callback for MediaDrmBridgeFactory::Create().
  void OnCdmCreated(uint32_t creation_id,
                    const scoped_refptr<ContentDecryptionModule>& cdm,
                    CreateCdmStatus status);

  CreateFetcherCB create_fetcher_cb_;
  CreateStorageCB create_storage_cb_;

  uint32_t creation_id_ = 0;

  // Map between creation ID and PendingCreations.
  using PendingCreation =
      std::pair<std::unique_ptr<OHOSMediaDrmBridgeFactory>, CdmCreatedCB>;
  base::flat_map<uint32_t, PendingCreation> pending_creations_;

  base::WeakPtrFactory<OHOSCdmFactory> weak_factory_{this};
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_OHOS_CDM_FACTORY_H_
