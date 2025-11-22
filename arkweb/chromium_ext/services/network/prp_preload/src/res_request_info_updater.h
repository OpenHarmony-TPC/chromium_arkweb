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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_REQUEST_INFO_UPDATER_H
#define SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_REQUEST_INFO_UPDATER_H

#include "arkweb/chromium_ext/services/network/prp_preload/src/res_request_info_cache_mgr.h"

namespace ohos_prp_preload {
using ResPreloadInfosCB =
  base::RepeatingCallback<void(const PRPPPreconnectInfoList& preconnect_info_list,
    const std::shared_ptr<PRPPReqInfoTreeNode>& preload_info_tree,
    const std::set<std::string>& need_record_header_urls)>;
class ResRequestInfoUpdater : public base::RefCounted<ResRequestInfoUpdater> {
 public:
  ResRequestInfoUpdater(const std::string& url,
                        const net::NetworkAnonymizationKey& networkAnonymizationKey,
                        const scoped_refptr<DiskCacheBackendFactory>& disk_cache_backend_factory,
                        const ResPreloadInfosCB& preload_infos_cb);
  ~ResRequestInfoUpdater() = default;

  void Start();
  void UpdateResRequestInfo(const std::shared_ptr<PRRequestInfo>& info);
  void Stop();
  void SetPageOrigin(const std::string& page_origin);
 private:
  void OnResRequestInfoCacheLoaded(
    const LinkedHashMap& load_info_list,
    const LinkedHashMap& preconnect_limit_info_list,
    const net::NetworkAnonymizationKey& networkAnonymizationKey,
    const std::string& page_seq_num);
  void BuildPreconnectList(const std::shared_ptr<PRRequestInfo>& info,
    const LinkedHashMap& preconnect_limit_info_list,
    const net::NetworkAnonymizationKey& networkAnonymizationKey,
    const std::string& page_seq_num);
  void BuildPreloadTree(const std::shared_ptr<PRRequestInfo>& info,
    std::shared_ptr<PRPPReqInfoTreeNode> current,
    std::shared_ptr<PRPPReqInfoTreeNode> cur_first,
    std::shared_ptr<PRPPReqInfoTreeNode> cur_parent,
    int64_t cur_level_end_time,
    const std::string& page_seq_num);
  void UpdateResRequestInfoForDynamicHeaders(std::shared_ptr<PRPPReqInfoTreeNode> parent,
    std::shared_ptr<PRRequestInfo> child_info);
  bool IsDynamicHeadersMatch(const std::shared_ptr<PRRequestInfo>& child_info,
    const std::shared_ptr<PRRequestInfo>& parent_info);
 
  scoped_refptr<ResReqInfoCacheMgr> res_req_info_cache_mgr_;
  PRPPPreconnectInfoList prpp_preconnect_info_list_;
  std::shared_ptr<PRPPReqInfoTreeNode> preload_info_tree_;
  std::unordered_map<std::string, int32_t> preconnect_org_url_map_;
  ResPreloadInfosCB preload_infos_cb_;
  std::set<std::string> need_record_header_urls_;
  base::WeakPtrFactory<ResRequestInfoUpdater> weak_factory_{this};
};

}  // namespace ohos_prp_preload

#endif  // SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_REQUEST_INFO_UPDATER_H