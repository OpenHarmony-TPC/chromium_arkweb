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

#ifndef DEVICE_FIDO_OHOS_OHOS_FIDO_DISCOVER_H_
#define DEVICE_FIDO_OHOS_OHOS_FIDO_DISCOVER_H_

#include <memory>

#include "base/component_export.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "device/fido/fido_discovery_base.h"
#include "device/fido/ohos/ohos_authenticator.h"

namespace device {

class COMPONENT_EXPORT(DEVICE_FIDO) OhosFidoDiscovery
    : public FidoDiscoveryBase {
 public:
  OhosFidoDiscovery();
  ~OhosFidoDiscovery() override;

  // FidoDiscoveryBase:
  void Start() override;

 private:
  void AddAuthenticator();

  std::unique_ptr<OhosAuthenticator> authenticator_;

  base::WeakPtrFactory<OhosFidoDiscovery> weak_factory_{this};
};

} // namespace device

#endif  // DEVICE_FIDO_OHOS_OHOS_FIDO_DISCOVER_H_
