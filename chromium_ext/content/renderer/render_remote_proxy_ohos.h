// Copyright 2022 Huawei Device Co., Ltd.
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

#ifndef CONTENT_RENDERER_RENDER_REMOTE_PROXY_OHOS_H_
#define CONTENT_RENDERER_RENDER_REMOTE_PROXY_OHOS_H_

#include <condition_variable>
#include <mutex>

#include "build/build_config.h"

#if BUILDFLAG(IS_OHOS)
#include "third_party/ohos_ndk/includes/ohos_adapter/aafwk_render_scheduler_host_adapter.h"

namespace base {
class CommandLine;
}

namespace content {
class RenderRemoteProxy : public OHOS::NWeb::AafwkRenderSchedulerHostAdapter {
 public:
  RenderRemoteProxy() = default;
  ~RenderRemoteProxy() = default;

  virtual void NotifyBrowserFd(int32_t ipcFd,
                               int32_t sharedFd,
                               int32_t crashFd) override;

  virtual void NotifyBrowser(
      int32_t ipcFd,
      int32_t sharedFd,
      int32_t crashFd,
      std::shared_ptr<OHOS::NWeb::AafwkBrowserClientAdapter> clientAdapter)
      override;

  static void CreateAndRegist(const base::CommandLine& command_line);
  static bool WaitForBrowserFd();

 private:
  int32_t ipc_fd_ = 0;
  int32_t shared_fd_ = 0;
  int32_t crash_id_ = 0;

  static std::mutex browser_fd_mtx_;
  static std::condition_variable browser_fd_cv_;
  static bool is_browser_fd_received_;
  static bool is_for_test_;
};
#endif

}  // namespace content

#endif  // CONTENT_RENDERER_RENDER_REMOTE_PROXY_OHOS_H_
