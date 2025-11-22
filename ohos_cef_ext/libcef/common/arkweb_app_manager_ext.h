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

#ifndef ARKWEB_LIBCEF_COMMON_APP_MANAGER_EXT_H_
#define ARKWEB_LIBCEF_COMMON_APP_MANAGER_EXT_H_
#pragma once

#include <list>

#include "arkweb/build/features/features.h"
#include "base/functional/callback.h"
#include "build/build_config.h"
#include "cef/include/cef_app.h"
#include "cef/include/cef_request_context.h"
#include "content/public/common/content_client.h"

class CefBrowserContext;
struct CefSchemeInfo;

// Exposes global application state in the main and render processes.
class ArkWebAppManagerExt : public CefAppManager {
 public:
  friend CefAppManager;
  ArkWebAppManagerExt *AsArkWebAppManagerExt() override { return this; }
  ArkWebAppManagerExt(const ArkWebAppManagerExt&) = delete;
  ArkWebAppManagerExt& operator=(const ArkWebAppManagerExt&) = delete;
  void AddSchemeCodeCache(const CefSchemeInfo* scheme_info);
  void SchemeHandlerAddCustomScheme(content::ContentClient::Schemes* schemes);

 private:
#if BUILDFLAG(ARKWEB_NETWORK_LOAD)
  std::vector<std::string> CustomSchemeCmdLineSplit(std::string str,
                                                    const char split);
  void RenderAddCustomSchemes();
#endif
};

#endif  // ARKWEB_LIBCEF_COMMON_APP_MANAGER_EXT_H_
