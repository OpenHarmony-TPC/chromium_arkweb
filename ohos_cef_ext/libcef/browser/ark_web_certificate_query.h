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

#ifndef CEF_LIBCEF_BROWSER_ARK_WEB_CERTIFICATE_QUERY_H_
#define CEF_LIBCEF_BROWSER_ARK_WEB_CERTIFICATE_QUERY_H_

#include <string>

#include "arkweb/build/features/features.h"
#include "cef/libcef/browser/certificate_query.h"

namespace content {
class WebContents;
}

namespace net {
class SSLInfo;
}

class GURL;

namespace certificate_query {

#if BUILDFLAG(ARKWEB_NETWORK_LOAD)
// Called from ContentBrowserClient::AllowAllCertificateError.
// |callback| will be returned if the request is unhandled and
// |default_disallow| is false.
[[nodiscard]] CertificateErrorCallback AllowAllCertificateError(
    content::WebContents* web_contents,
    int cert_error,
    const net::SSLInfo& ssl_info,
    const GURL& request_url,
    bool is_main_frame_request,
    bool strict_enforcement,
    const GURL& origin_url,
    const std::string& referrer,
    CertificateErrorCallback callback,
    bool default_disallow);
#endif  // BUILDFLAG(ARKWEB_NETWORK_LOAD)

}  // namespace certificate_query

#endif  // CEF_LIBCEF_BROWSER_ARK_WEB_CERTIFICATE_QUERY_H_
