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

#ifndef CONTENT_BROWSER_MEMORY_SWAP_METRICS_DRIVER_IMPL_OHOS_H_
#define CONTENT_BROWSER_MEMORY_SWAP_METRICS_DRIVER_IMPL_OHOS_H_

#include "base/time/time.h"
#include "content/browser/memory/swap_metrics_driver_impl.h"

#include <memory>

namespace content {

class SwapMetricsDriverImplOhos : public SwapMetricsDriverImpl {
 public:
  SwapMetricsDriverImplOhos(std::unique_ptr<Delegate> delegate,
                             const base::TimeDelta update_interval);
  ~SwapMetricsDriverImplOhos() override;

 protected:
  SwapMetricsDriver::SwapMetricsUpdateResult UpdateMetricsInternal(
      base::TimeDelta interval) override;

 private:
  uint64_t last_pswpin_ = 0;
  uint64_t last_pswpout_ = 0;
};

}  // namespace content

#endif  // CONTENT_BROWSER_MEMORY_SWAP_METRICS_DRIVER_IMPL_OHOS_H_
