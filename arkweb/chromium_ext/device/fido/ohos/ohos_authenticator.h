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

#ifndef DEVICE_FIDO_OHOS_OHOS_AUTHENTICATOR_H_
#define DEVICE_FIDO_OHOS_OHOS_AUTHENTICATOR_H_

#include <memory>
#include <optional>
#include <string>

#include "base/component_export.h"
#include "base/containers/span.h"
#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "device/fido/fido_authenticator.h"
#include "device/fido/fido_constants.h"

namespace device {

class OhosWebAuthnApi;

class COMPONENT_EXPORT(DEVICE_FIDO) OhosAuthenticator
    : public FidoAuthenticator {
 public:
  static void IsUserVerifyingPlatformAuthenticatorAvailable(
      base::OnceCallback<void(bool)>);

  static void SignalUnknownCredential(const std::vector<uint8_t>& credential_id,
                                      const std::string& relying_party_id);

  static void SignalAllAcceptedCredentials(
      const std::string& relying_party_id,
      const std::vector<uint8_t>& user_id,
      const std::vector<std::vector<uint8_t>>& all_accepted_credential_ids);

  using ClientCapabilities = std::vector<std::pair<std::string, bool>>;
  static void GetClientCapabilities(
      base::OnceCallback<void(const ClientCapabilities&)>);

  OhosAuthenticator();

  OhosAuthenticator(const OhosAuthenticator&) = delete;
  OhosAuthenticator& operator=(const OhosAuthenticator&) = delete;

  ~OhosAuthenticator() override;

 private:
  // FidoAuthenticator:
  void InitializeAuthenticator(base::OnceClosure callback) override;
  void MakeCredential(CtapMakeCredentialRequest request,
                      MakeCredentialOptions options,
                      MakeCredentialCallback callback) override;
  void GetAssertion(CtapGetAssertionRequest request,
                    CtapGetAssertionOptions options,
                    GetAssertionCallback callback) override;
  void GetPlatformCredentialInfoForRequest(
      const CtapGetAssertionRequest& request,
      const CtapGetAssertionOptions& options,
      GetPlatformCredentialInfoForRequestCallback callback) override;
  void GetTouch(base::OnceClosure callback) override;
  void Cancel() override;
  AuthenticatorType GetType() const override;
  std::string GetId() const override;
  const AuthenticatorSupportedOptions& Options() const override;
  std::optional<FidoTransportProtocol> AuthenticatorTransport() const override;
  base::WeakPtr<FidoAuthenticator> GetWeakPtr() override;

  void MakeCredentialDone(
      MakeCredentialCallback callback,
      std::pair<MakeCredentialStatus,
                std::optional<AuthenticatorMakeCredentialResponse>> result);
  void GetAssertionDone(
      GetAssertionCallback callback,
      std::pair<GetAssertionStatus,
                std::optional<AuthenticatorGetAssertionResponse>> result);

  const AuthenticatorSupportedOptions options_;
  bool is_pending_ = false;
  bool waiting_for_cancellation_ = false;

  SEQUENCE_CHECKER(sequence_checker_);
  base::WeakPtrFactory<OhosAuthenticator> weak_factory_{this};
};

}  // namespace device

#endif  // DEVICE_FIDO_OHOS_OHOS_AUTHENTICATOR_H_
