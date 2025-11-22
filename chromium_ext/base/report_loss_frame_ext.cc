// Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/logging.h"
#include "arkweb/chromium_ext/base/report_loss_frame_ext.h"

#include <chrono>

#include "base/logging.h"
#if defined(REPORT_SYS_EVENT)
#include "arkweb/ohos_nweb/src/sysevent/event_reporter.h"
#endif
#include "base/task/thread_pool.h"
#include "base/trace_event/trace_event.h"

#if defined(REPORT_SYS_EVENT)
constexpr int JANK_STATS_VER = 1;
#endif

ReportLossFrame* ReportLossFrame::instance = nullptr;

ReportLossFrame::ReportLossFrame() {}

ReportLossFrame* ReportLossFrame::GetInstance() {
  if (instance == nullptr) {
    instance = new ReportLossFrame();
  }
  return instance;
}

ReportLossFrame::~ReportLossFrame() {
  instance = nullptr;
}

void ReportLossFrame::SetScrollState(ScrollMode state) {
  scroll_state_ = state;
}

void ReportLossFrame::SetVsyncPeriod(int64_t vsync_period) {
  vsync_period_ = vsync_period;
}

int64_t ReportLossFrame::GetCurrentTimestampMS() {
  auto currentTime = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime)
      .count();
}

void ReportLossFrame::Report() {
  if (!need_report_) {
    start_time_for_scroll_ = 0;
    return;
  }
#if defined(REPORT_SYS_EVENT)
  int64_t now = GetCurrentTimestampMS();
  int64_t duration = now - start_time_for_scroll_;
  base::ThreadPool::PostTask(
      FROM_HERE, {base::TaskPriority::LOWEST},
      base::BindOnce(&ReportJankStats, start_time_for_scroll_, duration,
                     jank_stats_, JANK_STATS_VER));
#endif
  Reset();
}

void ReportLossFrame::Record() {
  if (scroll_state_ == ScrollMode::STOP) {
    return;
  }

  if (start_time_for_scroll_ == 0) {
    start_time_for_scroll_ = GetCurrentTimestampMS();
    start_time_ = start_time_for_scroll_;
    return;
  }

  int64_t now = GetCurrentTimestampMS();
  int64_t duration = now - start_time_;
  // ns->ms
  double period = static_cast<double>(vsync_period_) / 1000000.0;
  start_time_ = now;

  if (duration <= period * 2) {
    return;
  }

  double loss_frame = static_cast<double>(duration) / period;
  LOG(DEBUG) << "ReportLossFrame: period: " << period
             << " duration:" << duration << " loss_frame: " << loss_frame;
  TRACE_EVENT2("base", "WEBVIEW::JANK_STATS_APP", "DURATION", duration,
               "LOSS_FRAME", loss_frame);

  size_t type = JANK_FREQ_EXCEED_FRAME;
  if (loss_frame < MAX_OF_FIRST_INTERVAL) {
    type = JANK_FREQ_6_FRAME;
  } else if (loss_frame < MAX_OF_SECOND_INTERVAL) {
    type = JANK_FREQ_15_FRAME;
  } else if (loss_frame < MAX_OF_THIRD_INTERVAL) {
    type = JANK_FREQ_20_FRAME;
  } else if (loss_frame < MAX_OF_FOURTH_INTERVAL) {
    type = JANK_FREQ_36_FRAME;
  } else if (loss_frame < MAX_OF_FIFTH_INTERVAL) {
    type = JANK_FREQ_48_FRAME;
  } else if (loss_frame < MAX_OF_SIXTH_INTERVAL) {
    type = JANK_FREQ_60_FRAME;
  } else if (loss_frame < MAX_OF_SEVENTH_INTERVAL) {
    type = JANK_FREQ_120_FRAME;
  } else if (loss_frame < MAX_OF_EIGHTTH_INTERVAL) {
    type = JANK_FREQ_180_FRAME;
  }

  jank_stats_[type]++;
  need_report_ = true;
}

void ReportLossFrame::Reset() {
  start_time_for_scroll_ = 0;
  std::fill(jank_stats_.begin(), jank_stats_.end(), 0);
  need_report_ = false;
}
