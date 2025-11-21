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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PRELOAD_RUNNER_PRPP_REQUEST_LOADER_FACTORY_H
#define SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PRELOAD_RUNNER_PRPP_REQUEST_LOADER_FACTORY_H

#include "arkweb/chromium_ext/net/base/page_res_request_info.h"
#include "services/network/public/mojom/network_context.mojom.h"

namespace net {
class URLRequestContext;
} // namespace net

namespace network {
class NetworkContext;
class URLLoaderContext;
} // namespace network

namespace ohos_prp_preload {
class PRPPRequestLoader;
// only run in network thread
class PRPPRequestLoaderFactory {
 public:
  // create PRPPRequestLoaderFactory
  static std::shared_ptr<PRPPRequestLoaderFactory> CreatePRPPRequestLoaderFactory(
	    const std::string& url,
	    base::WeakPtr<net::URLRequestContext> url_request_context);

  // destroy PRPPRequestLoaderFactory object
  virtual ~PRPPRequestLoaderFactory() = default;

  // create preload loader and start
  virtual void CreateReqLoaderAndStart(const std::shared_ptr<PRRequestInfo>& info,
	    std::set<std::string> need_record_header_urls) = 0;

  // set isolation info created with cached origin
  virtual void SetPRPPIsolation(const net::IsolationInfo& isl) = 0;

  // get preload loader
  virtual std::shared_ptr<PRPPRequestLoader> GetPRPPReqLoader(
      const network::URLLoaderContext& context,
	    const network::ResourceRequest& resource_request,
	    std::shared_ptr<PRRequestInfo> req_info_binding) = 0;

  // get weak ptr of PRPPRequestLoaderFactory
  virtual base::WeakPtr<PRPPRequestLoaderFactory> GetWeak() = 0;

  // get main url of page
  virtual const std::string& GetMainUrl() const = 0;
};

} // namespace ohos_prp_preload

#endif // SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PRELOAD_RUNNER_PRPP_REQUEST_LOADER_FACTORY_H