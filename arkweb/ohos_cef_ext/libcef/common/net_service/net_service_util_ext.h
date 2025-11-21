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

#ifndef CEF_LIBCEF_COMMON_NET_SERVICE_NET_SERVICE_UTIL_EXT_H_
#define CEF_LIBCEF_COMMON_NET_SERVICE_NET_SERVICE_UTIL_EXT_H_

#include <map>
#include <string>

#include "base/memory/scoped_refptr.h"
#include "cef/include/internal/cef_types_wrappers.h"
#include "net/cookies/cookie_constants.h"

namespace net {
class CanonicalCookie;
class HttpResponseHeaders;
struct RedirectInfo;
}  // namespace net

namespace network {
struct ResourceRequest;
}  // namespace network

class GURL;

namespace net_service {
// Populate |cookie|. Returns true on success.
bool MakeCefCookieEXT(const GURL& url,
                      const std::string& cookie_line,
#if BUILDFLAG(ARKWEB_COOKIE)
                   bool block_truncated,
#endif // BUILDFLAG(ARKWEB_COOKIE)
                   CefCookie& cookie);

}  // namespace net_service

#endif  // CEF_LIBCEF_COMMON_NET_SERVICE_NET_SERVICE_UTIL_EXT_H_
