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

#include "libcef/browser/ohos_safe_browsing/ohos_sb_malicious_allowlist.h"

namespace ohos_safe_browsing {

MaliciousAllowlist& MaliciousAllowlist::GetInstance() {
  static MaliciousAllowlist maliciousAllowlist;
  return maliciousAllowlist;
}

void MaliciousAllowlist::AddToAllowlist(const std::string& url,
                                        bool incognito_mode) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (incognito_mode) {
    incognito_allowlist_.Append(url);
  } else {
    allowlist_.Append(url);
  }
}

bool MaliciousAllowlist::IsInAllowlist(const std::string& url,
                                       bool incognito_mode) const {
  std::lock_guard<std::mutex> lock(mutex_);
  const base::Value::List& list =
      incognito_mode ? incognito_allowlist_ : allowlist_;
  for (const base::Value& value : list) {
    if (value.GetString() == url) {
      return true;
    }
  }
  return false;
}

}  // namespace ohos_safe_browsing
