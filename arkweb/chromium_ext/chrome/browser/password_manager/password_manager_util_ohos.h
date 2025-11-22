// Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef CHROME_BROWSER_PASSWORD_MANAGER_PASSWORD_MANAGER_UTIL_OHOS_H_
#define CHROME_BROWSER_PASSWORD_MANAGER_PASSWORD_MANAGER_UTIL_OHOS_H_

#include <string>

namespace password_manager_util_ohos {

// Attempts to (re-)authenticate the user of the OS account. Returns true if
// the user was successfully authenticated.
bool AuthenticateUser(std::u16string prompt_string, bool enable_biom);

}  // namespace password_manager_util_ohos

#endif  // CHROME_BROWSER_PASSWORD_MANAGER_PASSWORD_MANAGER_UTIL_OHOS_H_
