// Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef CEF_LIBCEF_BROWSER_ALLOY_GEOLOCATION_PERMISSIONS_H_
#define CEF_LIBCEF_BROWSER_ALLOY_GEOLOCATION_PERMISSIONS_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "include/cef_permission_request.h"

class AlloyGeolocationAccess : public CefGeolocationAcess {
 public:
  AlloyGeolocationAccess(const AlloyGeolocationAccess&) = delete;
  AlloyGeolocationAccess& operator=(const AlloyGeolocationAccess&) = delete;

  AlloyGeolocationAccess() = default;
  ~AlloyGeolocationAccess() = default;

  bool ContainOrigin(const CefString& origin) override;
  bool IsOriginAccessEnabled(const CefString& origin) override;
  void Enabled(const CefString& origin, bool incognito) override;
  void Disabled(const CefString& origin, bool incognito) override;

 private:
  std::string GetOriginKey(std::string& origin);
  const std::string pref_prefix_ = "AlloyGeolocationAccess%";

  IMPLEMENT_REFCOUNTING(AlloyGeolocationAccess);
};

#endif  // CEF_LIBCEF_BROWSER_ALLOY_GEOLOCATION_PERMISSIONS_H_
