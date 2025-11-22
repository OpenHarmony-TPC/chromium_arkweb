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

#ifndef CEF_LIBCEF_BROWSER_SAFE_BROWSING_MALICIOUS_ALLOWLIST_H_
#define CEF_LIBCEF_BROWSER_SAFE_BROWSING_MALICIOUS_ALLOWLIST_H_

#include <mutex>
#include <string>

#include "base/values.h"

namespace ohos_safe_browsing {

class MaliciousAllowlist {
 public:
  static MaliciousAllowlist& GetInstance();

  void AddToAllowlist(const std::string& url, bool incognito_mode);
  bool IsInAllowlist(const std::string& url, bool incognito_mode) const;

 private:
  MaliciousAllowlist() = default;
  ~MaliciousAllowlist() = default;

  base::Value::List incognito_allowlist_;
  base::Value::List allowlist_;
  mutable std::mutex mutex_;
};

}  // namespace ohos_safe_browsing

#endif  // CEF_LIBCEF_BROWSER_SAFE_BROWSING_MALICIOUS_ALLOWLIST_H_
