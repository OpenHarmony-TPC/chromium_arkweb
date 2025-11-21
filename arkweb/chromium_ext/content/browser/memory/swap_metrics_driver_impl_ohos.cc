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

#include "content/browser/memory/swap_metrics_driver_impl_ohos.h"

#include <memory>

#include "base/memory/ptr_util.h"
#include "base/process/process_metrics.h"
#include "base/time/time.h"
#include "content/public/browser/swap_metrics_driver.h"

namespace content {

namespace {
using SwapMetricsUpdateResult = SwapMetricsDriver::SwapMetricsUpdateResult;
bool HasSwap() {
  base::SystemMemoryInfoKB memory_info;
  if (!base::GetSystemMemoryInfo(&memory_info)) {
    return false;
  }
  return memory_info.swap_total > 0;
}

}  // namespace

// static
std::unique_ptr<SwapMetricsDriver> SwapMetricsDriver::Create(
    std::unique_ptr<Delegate> delegate,
    const base::TimeDelta update_interval) {
  return HasSwap() ? base::WrapUnique<SwapMetricsDriver>(
                         new SwapMetricsDriverImplOhos(std::move(delegate),
                                                        update_interval))
                   : std::unique_ptr<SwapMetricsDriver>();
}

SwapMetricsDriverImplOhos::SwapMetricsDriverImplOhos(
    std::unique_ptr<Delegate> delegate,
    const base::TimeDelta update_interval)
    : SwapMetricsDriverImpl(std::move(delegate), update_interval) {}

SwapMetricsDriverImplOhos::~SwapMetricsDriverImplOhos() = default;

SwapMetricsUpdateResult SwapMetricsDriverImplOhos::UpdateMetricsInternal(
    base::TimeDelta interval) {
  base::VmStatInfo vmstat;
  if (!base::GetVmStatInfo(&vmstat)) {
    return SwapMetricsDriver::SwapMetricsUpdateResult::kSwapMetricsUpdateFailed;
  }

  uint64_t in_counts = vmstat.pswpin - last_pswpin_;
  uint64_t out_counts = vmstat.pswpout - last_pswpout_;
  last_pswpin_ = vmstat.pswpin;
  last_pswpout_ = vmstat.pswpout;

  if (interval.is_zero())
    return SwapMetricsDriver::SwapMetricsUpdateResult::
        kSwapMetricsUpdateSuccess;

  delegate_->OnSwapInCount(in_counts, interval);
  delegate_->OnSwapOutCount(out_counts, interval);

  return SwapMetricsDriver::SwapMetricsUpdateResult::kSwapMetricsUpdateSuccess;
}

}  // namespace content
