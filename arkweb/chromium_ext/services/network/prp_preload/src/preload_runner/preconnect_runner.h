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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_SRC_PRELOAD_RUNNER_PRECONNECT_RUNNER_H
#define SERVICES_NETWORK_PRP_PRELOAD_SRC_PRELOAD_RUNNER_PRECONNECT_RUNNER_H

#include "base/memory/weak_ptr.h"
#include "net/base/network_anonymization_key.h"

namespace net {
class URLRequestContext;
}  // namespace net

class GURL;

namespace ohos_prp_preload {
// only run in network thread
class PreconnectRunner {
 public:
  static void PreconnectSocket(const GURL& original_url,
    bool allow_credentials,
    const net::NetworkAnonymizationKey& network_anonymization_key,
    base::WeakPtr<net::URLRequestContext> url_request_context);
  static GURL GetHSTSRedirect(const GURL& original_url,
    base::WeakPtr<net::URLRequestContext> url_request_context);
 private:
  PreconnectRunner() = default;
  ~PreconnectRunner() = default;
};

}  // namespace ohos_prp_preload

#endif  // SERVICES_NETWORK_PRP_PRELOAD_SRC_PRELOAD_RUNNER_PRECONNECT_RUNNER_H