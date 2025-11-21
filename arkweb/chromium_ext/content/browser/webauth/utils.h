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

#ifndef CONTENT_BROWSER_WEBAUTH_UTILS_H_
#define CONTENT_BROWSER_WEBAUTH_UTILS_H_

#include "device/fido/authenticator_get_assertion_response.h"
#include "device/fido/authenticator_make_credential_response.h"
#include "device/fido/ctap_get_assertion_request_extra.h"
#include "device/fido/ctap_make_credential_request_extra.h"
#include "third_party/blink/public/mojom/webauthn/authenticator.mojom.h"

namespace content {

device::CredentialMediationRequirement Convert(
    const blink::mojom::PublicKeyCredentialMediationRequirement& mediation);

device::CredentialHint Convert(const blink::mojom::Hint&);

device::CtapRequestExtraCommon CreateCtapRequestExtraCommon(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialCreationOptionsPtr& options);

device::CtapRequestExtraCommon CreateCtapRequestExtraCommon(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialRequestOptionsPtr& options);

device::CtapMakeCredentialRequestExtra CreateCtapMakeCredentialRequestExtra(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialCreationOptionsPtr& options);

device::CtapGetAssertionRequestExtra CreateCtapGetAssertionRequestExtra(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialRequestOptionsPtr& options);

blink::mojom::MakeCredentialAuthenticatorResponsePtr CreateMakeCredentialResponse(
    const device::AuthenticatorMakeCredentialResponse& response_data);

blink::mojom::GetAssertionAuthenticatorResponsePtr CreateGetAssertionResponse(
    const device::AuthenticatorGetAssertionResponse& response_data);

void GetClientCapabilitiesFromOhosWebAuthnApi(
    blink::mojom::Authenticator::GetClientCapabilitiesCallback callback);

} //namespace content

#endif  // CONTENT_BROWSER_WEBAUTH_UTILS_H_
