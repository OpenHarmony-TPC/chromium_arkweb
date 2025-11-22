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

#include "base/logging.h"
#include "base/notreached.h"
#include "chrome/browser/shell_integration.h"

namespace shell_integration {

bool SetAsDefaultBrowser() {
  return false;
}

bool SetAsDefaultClientForScheme(const std::string& scheme) {
  NOTIMPLEMENTED_LOG_ONCE();
  return false;
}

std::u16string GetApplicationNameForScheme(const GURL& url) {
  NOTIMPLEMENTED_LOG_ONCE();
  return {};
}

DefaultWebClientState GetDefaultBrowser() {
  bool ret = 0;
  VLOG(1) << "GetDefaultBrowser ret: " << ret;
  if (ret) {
    return DefaultWebClientState::IS_DEFAULT;
  }
  return DefaultWebClientState::NOT_DEFAULT;
}

bool IsFirefoxDefaultBrowser() {
  NOTIMPLEMENTED_LOG_ONCE();
  return false;
}

DefaultWebClientState IsDefaultClientForScheme(const std::string& scheme) {
  return GetDefaultBrowser();
}

namespace internal {

DefaultWebClientSetPermission GetPlatformSpecificDefaultWebClientSetPermission(
    WebClientSetMethod method) {
  NOTIMPLEMENTED_LOG_ONCE();
  return SET_DEFAULT_UNATTENDED;
}

}  // namespace internal

}  // namespace shell_integration
