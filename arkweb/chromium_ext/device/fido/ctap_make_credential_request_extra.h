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

#ifndef DEVICE_FIDO_CTAP_MAKE_CREDENTIAL_REQUEST_EXTRA_H_
#define DEVICE_FIDO_CTAP_MAKE_CREDENTIAL_REQUEST_EXTRA_H_

#include <stdint.h>
#include <optional>
#include <string>
#include <vector>

#include "device/fido/ctap_request_extra_common.h"

namespace device {

struct CtapMakeCredentialRequestExtra {
  CtapRequestExtraCommon common;
  std::vector<std::string> attestation_formats;
};

} // namespace device
#endif  // DEVICE_FIDO_CTAP_MAKE_CREDENTIAL_REQUEST_EXTRA_H_
