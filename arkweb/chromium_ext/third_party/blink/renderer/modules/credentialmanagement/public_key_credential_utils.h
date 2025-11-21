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

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_CREDENTIALMANAGEMENT_PUBLIC_KEY_CREDENTIAL_UTILS_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_CREDENTIALMANAGEMENT_PUBLIC_KEY_CREDENTIAL_UTILS_H_

#include "third_party/blink/public/mojom/webauthn/authenticator.mojom-blink.h"
#include "third_party/blink/renderer/bindings/core/v8/idl_types.h"
#include "third_party/blink/renderer/bindings/core/v8/script_promise_resolver.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"

namespace blink {

void OnGetClientCapabilitiesFullComplete(
    ScriptPromiseResolver<IDLRecord<IDLString, IDLBoolean>>* resolver,
    const Vector<mojom::blink::WebAuthnClientCapabilityPtr> capabilities);

} // namspace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_CREDENTIALMANAGEMENT_PUBLIC_KEY_CREDENTIAL_UTILS_H_
