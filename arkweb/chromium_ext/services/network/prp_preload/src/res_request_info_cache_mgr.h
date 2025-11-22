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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_REQUEST_INFO_CACHE_MGR_H
#define SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_REQUEST_INFO_CACHE_MGR_H

#include "arkweb/chromium_ext/services/network/prp_preload/src/disk_cache_file.h"
#include "arkweb/chromium_ext/services/network/prp_preload/src/disk_cache_info_parser.h"
#include "base/task/thread_pool.h"
#include "net/base/network_anonymization_key.h"
#include "quiche/common/quiche_linked_hash_map.h"

namespace ohos_prp_preload {
using LinkedHashMap = quiche::QuicheLinkedHashMap<std::string, std::shared_ptr<PRRequestInfo>>;
using ResRequestInfoCacheLoadedCB =
  base::RepeatingCallback<void(
    const LinkedHashMap& load_info_list,
    const LinkedHashMap& preconnect_limit_info_list,
    const net::NetworkAnonymizationKey& networkAnonymizationKey,
    const std::string& page_seq_num)>;
class ResReqInfoCacheMgr : public base::RefCounted<ResReqInfoCacheMgr> {
 public:
  ResReqInfoCacheMgr(const std::string& url,
                     const net::NetworkAnonymizationKey& networkAnonymizationKey,
                     const scoped_refptr<DiskCacheBackendFactory>& disk_cache_backend_factory,
                     const ResRequestInfoCacheLoadedCB& info_list_cb);
  ~ResReqInfoCacheMgr() = default;

  static void GetPreconnectLimitListKey(const GURL& origin_url, bool allow_credentials, std::string& key);
  static void GetPreconnectOriginUrl(const std::shared_ptr<PRRequestInfo>& info, GURL& origin_url);
  void Start();
  void UpdateResRequestInfo(const std::shared_ptr<PRRequestInfo>& info);
  void Stop();
  void SetPageOrigin(const std::string& page_origin);
 private:
  void OnEntryLoadedCallback(const std::string& entry_content);
  void CheckFlush(bool checkflush_immediately);
  bool UpdatePreconnectInfo(const std::shared_ptr<PRRequestInfo>& info);
  void UpdatePreloadInfo(const std::string& key, const std::shared_ptr<PRRequestInfo>& info);
  bool IsRequestWithCookie(const std::shared_ptr<PRRequestInfo>& info);

  const net::NetworkAnonymizationKey networkAnonymizationKey_;
  scoped_refptr<DiskCacheFile> disk_cache_;
  LinkedHashMap new_preload_info_list_;
  LinkedHashMap load_preload_info_list_;
  LinkedHashMap new_preconnect_limit_list_;
  LinkedHashMap load_preconnect_limit_list_;
  size_t last_flush_len_{ 0 };
  ResRequestInfoCacheLoadedCB info_cache_loaded_cb_;
  bool is_start_{ false };
  std::string page_origin_;
  int64_t page_index_ { 0 };
  base::WeakPtrFactory<ResReqInfoCacheMgr> weak_factory_{this};
};

}  // namespace ohos_prp_preload

#endif  // SERVICES_NETWORK_PRP_PRELOAD_SRC_RES_REQUEST_INFO_CACHE_MGR_H
