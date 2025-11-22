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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PAGE_RES_PARALLEL_PRELOAD_MGR_H
#define SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PAGE_RES_PARALLEL_PRELOAD_MGR_H

#include "base/task/thread_pool.h"
#include "net/base/network_anonymization_key.h"
#include "services/network/public/mojom/network_context.mojom.h"

namespace net {
class URLRequestContext;
}  // namespace net

namespace ohos_prp_preload {
class PRRequestInfo;
class PRPPRequestLoaderFactory;
enum class PRPPreloadMode {
  NONE, // close preload
  PRECONNECT, // only preconnect
  PRELOAD, // preconnect and prevalidate
};
using PageOriginCallback = base::OnceCallback<void(const std::string&)>;
class PRParallelPreloadMgr {
 public:
  // get single instance of PRParallelPreloadMgr
  static PRParallelPreloadMgr& GetInstance();

  // get preload mode: none, preconnect or preload
  static PRPPreloadMode GetPRParallelPreloadMode();

  // destroy the PRParallelPreloadMgr object
  virtual ~PRParallelPreloadMgr() = default;

  // init preload module, load preload info cache index and start preload thread
  virtual void Init(const scoped_refptr<base::SingleThreadTaskRunner>& net_task_runner) = 0;

  // start preload page sub_request
  virtual void StartPage(const std::string& url,
                         const net::NetworkAnonymizationKey& networkAnonymizationKey,
                         base::WeakPtr<net::URLRequestContext> url_request_context,
                         uint64_t addr_web_handle,
                         PageOriginCallback callback,
                         bool no_use_cache) = 0;

  // stop preload page
  virtual void StopPage(uint64_t addr_web_handle) = 0;

  // update preload request info
  virtual void UpdateResRequestInfo(const std::string& key,
                                    const std::shared_ptr<PRRequestInfo>& info) = 0;

  // update preload url for redirect page
  virtual void UpdateRedirectUrl(const std::string& org_url,
                                 const std::string& redirect_url,
                                 bool replace = false) = 0;

  // set URLLoaderFactoryParam, update isolation info
  virtual void SetURLLoaderFactoryParam(network::mojom::URLLoaderFactoryParamsPtr params) = 0;

  // set isolation info and origin
  virtual void SetPageOrigin(const std::string& url, const net::IsolationInfo& isl) = 0;

  // excute callback NavigationRequest::OnGetIsolation, create isolation info and set
  // callback by ResPreloadScheduler
  virtual void OnPageOrigin(const std::string& url, const std::string& page_origin) = 0;

  // get PRPPRequestLoaderFactory for page
  virtual base::WeakPtr<PRPPRequestLoaderFactory> GetRequestLoaderFactory(
    const std::string& main_url) = 0;

  // update the count of prerequest can be send to scheduler
  virtual void UpdateIdlePrerequestCount(const std::string& key) = 0;

  // remove_cache, called when excute removeCache of ets
  virtual void RemoveCache(base::Time start_time, base::Time end_time) = 0;
};

}  // namespace ohos_prp_preload

#endif  // SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PAGE_RES_PARALLEL_PRELOAD_MGR_H
