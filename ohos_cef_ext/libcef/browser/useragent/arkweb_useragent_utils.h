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

#ifndef CEF_LIBCEF_BROWSER_ARKWEB_USERAGENT_UTILS_H_
#define CEF_LIBCEF_BROWSER_ARKWEB_USERAGENT_UTILS_H_
#pragma once

#include "content/public/browser/navigation_handle.h"

namespace arkweb_useragent_utils {
  void MaybeOverrideUserAgentOnStartNavigation(content::NavigationHandle* navigation);
  void MaybeOverrideUserAgentOnRedirectNavigation(content::NavigationHandle* navigation);
  void CheckRedirectChainForDuplicates(content::NavigationHandle* navigation);
  bool ShouldUpdateErrorPageUrl(const std::vector<std::string>& redirect_chain,
                                const std::string& current_url);
} // namespace arkweb_useragent_utils

#endif // CEF_LIBCEF_BROWSER_ARKWEB_USERAGENT_UTILS_H_