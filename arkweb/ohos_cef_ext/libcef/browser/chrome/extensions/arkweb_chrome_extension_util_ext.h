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

#ifndef ARKWEB_LIBCEF_BROWSER_CHROME_EXTENSIONS_CHROME_EXTENSION_UTIL_EXT_H_
#define ARKWEB_LIBCEF_BROWSER_CHROME_EXTENSIONS_CHROME_EXTENSION_UTIL_EXT_H_
#pragma once

#include "arkweb/build/features/features.h"

namespace content {
class WebContents;
}  // namespace content

namespace cef {

#if BUILDFLAG(ARKWEB_ARKWEB_EXTENSIONS)
int GetTabIdForWebContents(const content::WebContents* web_contents);

content::WebContents* GetWebContentByTabId(int tab_id);

content::WebContents* GetWebContentBySessionId(int browser_id);

content::WebContents* GetWebContentByTabIdOrSessionId(int id);

bool ArkWebExtensionIsNotTabId(content::WebContents* web_contents, int tab_id);
#endif

}  // namespace cef

#endif  // ARKWEB_LIBCEF_BROWSER_CHROME_EXTENSIONS_CHROME_EXTENSION_UTIL_EXT_H_
