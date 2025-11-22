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

#include "content/browser/webauth/utils.h"

#include "base/logging.h"
#include "content/browser/webauth/common_utils.h"
#include "device/fido/ohos/ohos_authenticator.h"

namespace content {

device::CredentialMediationRequirement Convert(
    const blink::mojom::PublicKeyCredentialMediationRequirement& mediation)
{
    switch (mediation) {
        case blink::mojom::PublicKeyCredentialMediationRequirement::SILENT:
            return device::CredentialMediationRequirement::kSilent;
        case blink::mojom::PublicKeyCredentialMediationRequirement::OPTIONAL:
            return device::CredentialMediationRequirement::kOptional;
        case blink::mojom::PublicKeyCredentialMediationRequirement::REQUIRED:
            return device::CredentialMediationRequirement::kRequired;
        case blink::mojom::PublicKeyCredentialMediationRequirement::CONDITIONAL:
            return device::CredentialMediationRequirement::kConditional;
    }
    return device::CredentialMediationRequirement::kSilent;
}

device::CredentialHint Convert(const blink::mojom::Hint& hint)
{
    switch (hint) {
        case blink::mojom::Hint::SECURITY_KEY:
            return device::CredentialHint::kSecurityKey;
        case blink::mojom::Hint::CLIENT_DEVICE:
            return device::CredentialHint::kClientDevice;
        case blink::mojom::Hint::HYBRID:
            return device::CredentialHint::kHintHybrid;
    }
    return device::CredentialHint::kHintHybrid;
}

device::CtapRequestExtraCommon CreateCtapRequestExtraCommon(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialCreationOptionsPtr& options)
{
    device::CtapRequestExtraCommon ret;
    ret.origin = caller_origin.Serialize();
    ret.challenge = options->challenge;
    ret.mediation = Convert(options->mediation);
    if (options->timeout) {
        ret.timeout = *options->timeout;
    }
    ret.hints.reserve(options->hints.size());
    for (const auto& hint : options->hints) {
        ret.hints.push_back(Convert(hint));
    }
    return ret;
}

device::CtapRequestExtraCommon CreateCtapRequestExtraCommon(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialRequestOptionsPtr& options)
{
    device::CtapRequestExtraCommon ret;
    ret.origin = caller_origin.Serialize();
    ret.challenge = options->challenge;
    ret.mediation = Convert(options->mediation);
    if (options->timeout) {
        ret.timeout = *options->timeout;
    }
    ret.hints.reserve(options->hints.size());
    for (const auto& hint : options->hints) {
        ret.hints.push_back(Convert(hint));
    }
    // Not support extensions.
    ret.extensions = std::nullopt;
    return ret;
}

device::CtapMakeCredentialRequestExtra CreateCtapMakeCredentialRequestExtra(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialCreationOptionsPtr& options)
{
    device::CtapMakeCredentialRequestExtra ret;
    ret.common = CreateCtapRequestExtraCommon(caller_origin, options);
    ret.attestation_formats = options->attestation_formats;
    return ret;
}

device::CtapGetAssertionRequestExtra CreateCtapGetAssertionRequestExtra(
    const url::Origin& caller_origin,
    const blink::mojom::PublicKeyCredentialRequestOptionsPtr& options)
{
    device::CtapGetAssertionRequestExtra ret;
    ret.common = CreateCtapRequestExtraCommon(caller_origin, options);
    return ret;
}

blink::mojom::MakeCredentialAuthenticatorResponsePtr CreateMakeCredentialResponse(
    const device::AuthenticatorMakeCredentialResponse& response_data)
{
    LOG(INFO) << "CreateMakeCredentialResponse response_extra";
    auto response = blink::mojom::MakeCredentialAuthenticatorResponse::New();
    auto common_info = blink::mojom::CommonCredentialInfo::New();

    common_info->client_data_json =
        response_data.response_extra->common.client_data_json;
    common_info->raw_id = response_data.response_extra->common.raw_id;
    common_info->id = Base64UrlEncodeChallenge(common_info->raw_id);
    common_info->authenticator_data =
        response_data.response_extra->common.authenticator_data;
    response->info = std::move(common_info);
    response->attestation_object =
        response_data.response_extra->attestation_object;
    if (response_data.transports) {
        response->transports.assign(
            response_data.transports->begin(),
            response_data.transports->end());
    }
    response->public_key_der = response_data.response_extra->public_key;
    response->public_key_algo =
        response_data.response_extra->public_key_algorithm;

    return response;
}

blink::mojom::GetAssertionAuthenticatorResponsePtr CreateGetAssertionResponse(
    const device::AuthenticatorGetAssertionResponse& response_data)
{
    LOG(INFO) << "CreateGetAssertionResponse response_extra";
    auto response = blink::mojom::GetAssertionAuthenticatorResponse::New();
    auto common_info = blink::mojom::CommonCredentialInfo::New();

    common_info->client_data_json =
        response_data.response_extra->common.client_data_json;
    common_info->raw_id = response_data.response_extra->common.raw_id;
    common_info->id = Base64UrlEncodeChallenge(common_info->raw_id);
    common_info->authenticator_data =
        response_data.response_extra->common.authenticator_data;
    response->info = std::move(common_info);

    response->authenticator_attachment =
        response_data.response_extra->common.autenticator_attachment;
    response->signature = response_data.response_extra->signature;
    response->user_handle = response_data.response_extra->user_handle;
    response->extensions =
        blink::mojom::AuthenticationExtensionsClientOutputs::New();

    return response;
}

void GetClientCapabilitiesFromOhosWebAuthnApi(
    blink::mojom::Authenticator::GetClientCapabilitiesCallback callback)
{
    device::OhosAuthenticator::GetClientCapabilities(base::BindOnce(
        [](const std::vector<std::pair<std::string, bool>>& capabilities) {
            std::vector<blink::mojom::WebAuthnClientCapabilityPtr> result;
            result.reserve(capabilities.size());
            for (const auto& capability : capabilities) {
                result.push_back(blink::mojom::WebAuthnClientCapability::New(
                    capability.first, capability.second));
            }
            return result;
        }).Then(std::move(callback)));
}

} // namespace content
