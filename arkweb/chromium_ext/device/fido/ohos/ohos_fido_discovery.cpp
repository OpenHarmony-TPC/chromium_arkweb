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

#include "device/fido/ohos/ohos_fido_discovery.h"

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/logging.h"
#include "base/task/sequenced_task_runner.h"
#include "device/fido/ohos/ohos_webauthn_api.h"

namespace device {

OhosFidoDiscovery::OhosFidoDiscovery()
    : FidoDiscoveryBase(FidoTransportProtocol::kInternal) {}

OhosFidoDiscovery::~OhosFidoDiscovery() = default;

void OhosFidoDiscovery::Start()
{
  DCHECK(!authenticator_);
  if (!observer()) {
    return;
  }

  // Start() is currently invoked synchronously in the
  // FidoRequestHandler ctor. Invoke AddAuthenticator() asynchronously
  // to avoid hairpinning FidoRequestHandler::AuthenticatorAdded()
  // before the request handler has an observer.
  base::SequencedTaskRunner::GetCurrentDefault()->PostTask(
      FROM_HERE,
      base::BindOnce(&OhosFidoDiscovery::AddAuthenticator,
                     weak_factory_.GetWeakPtr()));
}

void OhosFidoDiscovery::AddAuthenticator()
{
  bool success = false;
  if (!OhosWebAuthnApi::Instance()->IsAvailable()) {
    observer()->DiscoveryStarted(this, success);
    return;
  }
  success = true;
  authenticator_ = std::make_unique<OhosAuthenticator>();
  observer()->DiscoveryStarted(this, success, {authenticator_.get()});
}

}  // namespace device
