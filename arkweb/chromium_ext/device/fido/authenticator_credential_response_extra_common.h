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

#ifndef DEVICE_FIDO_AUTHENTICATOR_CREDENTIAL_RESPONSE_EXTRA_COMMON_H_
#define DEVICE_FIDO_AUTHENTICATOR_CREDENTIAL_RESPONSE_EXTRA_COMMON_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "device/fido/fido_types.h"

struct AuthenticatorCredentialResponseExtraCommon {
  std::vector<uint8_t> raw_id;
  std::vector<uint8_t> client_data_json;
  std::vector<uint8_t> authenticator_data;
  device::AuthenticatorAttachment autenticator_attachment =
      device::AuthenticatorAttachment::kAny;
  std::optional<std::string> id;
  std::optional<std::string> type;
  std::string client_extension_results;
};

struct AuthenticatorMakeCredentialResponseExtra {
  AuthenticatorCredentialResponseExtraCommon common;
  std::vector<uint8_t> attestation_object;
  std::vector<uint8_t> public_key;
  int32_t public_key_algorithm = 0;
};

struct AuthenticatorGetAssertionResponseExtra {
  AuthenticatorCredentialResponseExtraCommon common;
  std::vector<uint8_t> signature;
  std::vector<uint8_t> user_handle;
};

#endif  // DEVICE_FIDO_AUTHENTICATOR_CREDENTIAL_RESPONSE_EXTRA_COMMON_H_
