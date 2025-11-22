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

#ifndef DEVICE_FIDO_OHOS_OHOS_WEBAUTHN_API_H_
#define DEVICE_FIDO_OHOS_OHOS_WEBAUTHN_API_H_

#include "device/fido/authenticator_get_assertion_response.h"
#include "device/fido/authenticator_make_credential_response.h"
#include "device/fido/ctap_get_assertion_request.h"
#include "device/fido/ctap_make_credential_request.h"
#include "device/fido/discoverable_credential_metadata.h"
#include "device/fido/fido_authenticator.h"
#include "device/fido/fido_constants.h"
#include "device/fido/ohos/fido2_api.h"

namespace device {

class OhosWebAuthnApi {
 public:
  static OhosWebAuthnApi* Instance();
  virtual ~OhosWebAuthnApi();

  virtual bool IsAvailable();

  using GetClientCapabilitiesResult = std::vector<std::pair<std::string, bool>>;
  virtual GetClientCapabilitiesResult GetClientCapabilities();

  virtual bool IsUserVerifyingPlatformAuthenticatorAvailable();

  using RegisterResult = std::pair<MakeCredentialStatus,
      std::optional<AuthenticatorMakeCredentialResponse>>;
  virtual RegisterResult Register(
      CtapMakeCredentialRequest request,
      MakeCredentialOptions request_options);

  using GetAssertionResult = std::pair<GetAssertionStatus,
      std::optional<AuthenticatorGetAssertionResponse>>;
  virtual GetAssertionResult GetAssertion(CtapGetAssertionRequest request,
               CtapGetAssertionOptions options);
};

} // namespace device

#endif  // DEVICE_FIDO_OHOS_OHOS_WEBAUTHN_API_H_
