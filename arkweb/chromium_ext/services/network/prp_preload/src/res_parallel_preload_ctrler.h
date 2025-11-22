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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_PARALLEL_PRELOAD_CTRLER_H
#define SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_PARALLEL_PRELOAD_CTRLER_H

#include "arkweb/chromium_ext/services/network/prp_preload/src/res_preload_scheduler.h"
#include "arkweb/chromium_ext/services/network/prp_preload/src/res_request_info_updater.h"

namespace ohos_prp_preload {
using PRPPCtrlerTimeoutCB = base::RepeatingCallback<void(const std::string& url)>;
class ResParallelPreloadCtrler : public base::RefCountedThreadSafe<ResParallelPreloadCtrler> {
 public:
  ResParallelPreloadCtrler(const std::string& url,
                           const net::NetworkAnonymizationKey& networkAnonymizationKey,
                           const scoped_refptr<base::SingleThreadTaskRunner>& sth_task_runner,
                           const PRPPCtrlerTimeoutCB& timeout_cb);
  ~ResParallelPreloadCtrler()
  {
    LOG(INFO) << "PRPPreload.ResParallelPreloadCtrler::~ResParallelPreloadCtrler";
  }

  static void InitDiskCacheBackendFactory();
  static void RemoveCache(base::Time start_time, base::Time end_time);
  void Init(const scoped_refptr<base::SingleThreadTaskRunner>& net_task_runner,
    base::WeakPtr<net::URLRequestContext> url_request_context,
    const PRPPOnPageOriginCB& on_page_origin_cb);
  void Start();
  void Stop();
  void UpdateResRequestInfo(const std::shared_ptr<PRRequestInfo>& info);
  void SetPageOrigin(const std::string& page_origin);
  void SetPRPPReqLoaderFac(base::WeakPtr<PRPPRequestLoaderFactory> loader_fac_weak);
  void UpdateIdlePrerequestCount();
 private:
  void DoInit(const scoped_refptr<base::SingleThreadTaskRunner>& net_task_runner,
    base::WeakPtr<net::URLRequestContext> url_request_context,
    const PRPPOnPageOriginCB& on_page_origin_cb);
  void DoStart();
  void DoStop();
  void DoUpdateResRequestInfo(const std::shared_ptr<PRRequestInfo>& info);
  void DoSetPageOrigin(const std::string& page_origin);
  void DoSetPRPPReqLoaderFac(base::WeakPtr<PRPPRequestLoaderFactory> loader_fac_weak);
  void DoUpdateIdlePrerequestCount();
  void OnResPreloadInfos(const PRPPPreconnectInfoList& preconnect_info_list,
    const std::shared_ptr<PRPPReqInfoTreeNode>& preload_info_tree,
    const std::set<std::string>& need_record_header_urls);
  void OnTimeout();
  void InitDiskCacheBackendFactoryForTest();
  void ResetDiskCacheBackendFactoryForTest();
  std::string url_;
  const net::NetworkAnonymizationKey networkAnonymizationKey_;
  scoped_refptr<base::SingleThreadTaskRunner> sth_task_runner_;
  scoped_refptr<ResRequestInfoUpdater> res_req_info_updater_;
  scoped_refptr<ResPreloadScheduler> res_preload_scheduler_;
  PRPPCtrlerTimeoutCB timeout_cb_;
  bool start_filter_info_ { false };
  uint32_t filter_count_ { 0 };

  base::WeakPtrFactory<ResParallelPreloadCtrler> weak_factory_{this};
};

}  // namespace ohos_prp_preload

#endif  // SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_PARALLEL_PRELOAD_CTRLER_H