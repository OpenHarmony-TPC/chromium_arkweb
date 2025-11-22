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

#include "arkweb/chromium_ext/services/network/prp_preload/src/preload_runner/preconnect_runner.h"

#include "base/logging.h"
#include "net/base/http_user_agent_settings.h"
#include "net/http/http_network_session.h"
#include "net/http/http_transaction_factory.h"
#include "net/http/transport_security_state.h"
#include "net/url_request/url_request_context.h"

namespace ohos_prp_preload {

void PreconnectRunner::PreconnectSocket(
    const GURL& original_url,
    bool allow_credentials,
    const net::NetworkAnonymizationKey& network_anonymization_key,
    base::WeakPtr<net::URLRequestContext> url_request_context) {
  if (url_request_context.get() == nullptr) {
    return;
  }

  GURL url = GetHSTSRedirect(original_url, url_request_context);

  std::string user_agent;
  if (url_request_context->http_user_agent_settings()) {
    user_agent =
        url_request_context->http_user_agent_settings()->GetUserAgent();
  }
  net::HttpRequestInfo request_info;
  request_info.url = url;
  request_info.method = net::HttpRequestHeaders::kGetMethod;
  request_info.extra_headers.SetHeader(net::HttpRequestHeaders::kUserAgent,
                                       user_agent);

  if (allow_credentials) {
    request_info.load_flags = net::LOAD_NORMAL;
    request_info.privacy_mode = net::PRIVACY_MODE_DISABLED;
  } else {
    request_info.load_flags = net::LOAD_DO_NOT_SAVE_COOKIES;
    request_info.privacy_mode = net::PRIVACY_MODE_ENABLED;
  }

  request_info.network_anonymization_key = network_anonymization_key;

  net::HttpTransactionFactory* factory =
      url_request_context->http_transaction_factory();
  net::HttpNetworkSession* session = factory->GetSession();
  net::HttpStreamFactory* http_stream_factory = session->http_stream_factory();
  LOG(DEBUG) << "PRPPreload.PreconnectRunner::PreconnectSocket start";
  http_stream_factory->PreconnectStreams(1, request_info, true);
}

GURL PreconnectRunner::GetHSTSRedirect(
    const GURL& original_url,
    base::WeakPtr<net::URLRequestContext> url_request_context) {
  if (!url_request_context->transport_security_state() ||
      !original_url.SchemeIs("http") ||
      !url_request_context->transport_security_state()->ShouldUpgradeToSSL(
          original_url.host())) {
    return original_url;
  }

  GURL::Replacements replacements;
  replacements.SetSchemeStr("https");
  return original_url.ReplaceComponents(replacements);
}

}  // namespace ohos_prp_preload