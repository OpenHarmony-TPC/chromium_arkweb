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

#include "content/browser/screenlock_monitor/screenlock_monitor_device_source.h"

#include "ohos/adapter/screenlock_monitor/screenlock_monitor_adapter.h"

namespace content {

using ScreenlockMonitorAdapter = ohos::adapter::ScreenlockMonitorAdapter;

namespace {

void OnScreenlockNotificationReceived(const std::string& event_type) {
  ScreenlockMonitorSource::ScreenlockEvent screenlock_event;
  if (event_type == "locked") {
    screenlock_event = ScreenlockMonitorSource::SCREEN_LOCK_EVENT;
  } else if (event_type == "unlocked") {
    screenlock_event = ScreenlockMonitorSource::SCREEN_UNLOCK_EVENT;
  } else {
    return;
  }

  ScreenlockMonitorSource::ProcessScreenlockEvent(screenlock_event);
}

}  //  namespace

void ScreenlockMonitorDeviceSource::StartListeningForScreenlock() {
  ScreenlockMonitorAdapter::GetInstance().StartListeningForScreenlock(
      OnScreenlockNotificationReceived);
}

void ScreenlockMonitorDeviceSource::StopListeningForScreenlock() {
  ScreenlockMonitorAdapter::GetInstance().StopListeningForScreenlock();
}

}  // namespace content
