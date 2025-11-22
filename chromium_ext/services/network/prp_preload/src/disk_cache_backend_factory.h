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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_SRC_DISK_CACHE_BACKEND_FACTORY_H
#define SERVICES_NETWORK_PRP_PRELOAD_SRC_DISK_CACHE_BACKEND_FACTORY_H

#include <list>
#include "base/files/file_path.h"
#include "net/base/io_buffer.h"
#include "net/disk_cache/disk_cache.h"

namespace ohos_prp_preload {
using BackendCompleteCallback = base::OnceCallback<void()>;
class DiskCacheBackendFactory : public base::RefCountedThreadSafe<DiskCacheBackendFactory> {
 public:
  DiskCacheBackendFactory() = default;
  ~DiskCacheBackendFactory()
  {
    LOG(INFO) << "PRPPreload.DiskCacheBackendFactory::~DiskCacheBackendFactory";
  }
  DiskCacheBackendFactory(const DiskCacheBackendFactory&) = delete;
  DiskCacheBackendFactory& operator=(const DiskCacheBackendFactory&) = delete;
  void CreateBackend();
  bool CheckBackendAsync(BackendCompleteCallback callback);
  disk_cache::Backend* Backend() const { return backend_.get(); }
  void RemoveCache(base::Time start_time, base::Time end_time);
 private:
  void CacheCreatedCallback(disk_cache::BackendResult result);
  void ClearPreloadCacheDone(int rv);

  base::FilePath cache_path_;
  std::atomic<bool> is_inited_ { false };
  std::unique_ptr<disk_cache::Backend> backend_;
  std::list<BackendCompleteCallback> backend_complete_callback_list_;
  base::WeakPtrFactory<DiskCacheBackendFactory> weak_factory_ { this };
};

}  // namespace ohos_prp_preload

#endif  // SERVICES_NETWORK_PRP_PRELOAD_SRC_DISK_CACHE_BACKEND_FACTORY_H