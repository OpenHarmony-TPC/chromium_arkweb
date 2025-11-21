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

#include "arkweb/chromium_ext/third_party/blink/renderer/platform/bindings/parkable_string_utils.h"
#include "third_party/blink/renderer/platform/bindings/parkable_string_manager.h"
#include "third_party/blink/renderer/platform/bindings/parkable_string.h"

namespace blink {

// LCOV_EXCL_START
scoped_refptr<ParkableStringImpl> ParkableStringUtils::GetParkableString(
    scoped_refptr<StringImpl>&& impl, bool is_parkable)
{
   if (!impl) {
     return nullptr;
   }

  return is_parkable
      ? ParkableStringManager::Instance().Add(std::move(impl), nullptr)
      : ParkableStringImpl::MakeNonParkable(std::move(impl));
}
// LCOV_EXCL_STOP

}  // namespace blink