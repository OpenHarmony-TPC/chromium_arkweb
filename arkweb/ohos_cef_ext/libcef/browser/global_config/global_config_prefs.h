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
 
#ifndef CEF_LIBCEF_BROWSER_GLOBAL_CONFIG_GLOBAL_CONFIG_PREFS_H_
#define CEF_LIBCEF_BROWSER_GLOBAL_CONFIG_GLOBAL_CONFIG_PREFS_H_
 
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
 
namespace global_config {
#if BUILDFLAG(IS_ARKWEB_EXT)
  extern const char kGlobalConfigFeaturesSwitches[];
 
  void RegisterGlobalConfigPrefs(PrefRegistrySimple* registry);
 
  bool OnGlobalConfigResult(const std::string& path, PrefService* localState);
#endif
}
#endif