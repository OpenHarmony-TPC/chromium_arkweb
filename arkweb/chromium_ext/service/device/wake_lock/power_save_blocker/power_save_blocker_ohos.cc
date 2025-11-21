// Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "services/device/wake_lock/power_save_blocker/power_save_blocker.h"

#include <mutex>
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "services/device/wake_lock/power_save_blocker/power_save_blocker.h"
#include "arkweb/chromium_ext/service/device/wake_lock/power_save_blocker/nweb_screen_lock_tracker.h"

namespace device {

class PowerSaveBlocker::Delegate
    : public base::RefCountedThreadSafe<PowerSaveBlocker::Delegate> {
 public:
  Delegate(mojom::WakeLockType type) : type_(type) {}

  Delegate(const Delegate&) = delete;
  Delegate& operator=(const Delegate&) = delete;

  void ApplyBlock(const int32_t& id);
  void RemoveBlock(const int32_t& id);

 private:
  mojom::WakeLockType type_;
  std::map<int32_t, mojom::WakeLockType> lock_map_;
  std::mutex lock_map_mutex_;
  friend class base::RefCountedThreadSafe<Delegate>;
  ~Delegate() {}
};

void PowerSaveBlocker::Delegate::ApplyBlock(const int32_t& id) {
  std::lock_guard<std::mutex> lock(lock_map_mutex_);
  switch (type_) {
    case mojom::WakeLockType::kPreventAppSuspension:
      if (id != -1) {
        lock_map_.emplace(id, type_);
        NWebScreenLockTracker::Instance().Lock(id);
      }
      break;
    case mojom::WakeLockType::kPreventDisplaySleep:
    case mojom::WakeLockType::kPreventDisplaySleepAllowDimming:
      lock_map_.emplace(id, type_);
      NWebScreenLockTracker::Instance().Lock(id);
      break;
    default:
      LOG(INFO) << "Unhandled block type " << type_;
  }
}

void PowerSaveBlocker::Delegate::RemoveBlock(const int32_t& id) {
  std::lock_guard<std::mutex> lock(lock_map_mutex_);
  if (lock_map_.find(id) == lock_map_.end() || type_ != lock_map_[id]) {
    LOG(WARNING) << "The lock dose not exist, id: " << id
                 << ", type_: " << type_;
    return;
  }

  switch (type_) {
    case mojom::WakeLockType::kPreventAppSuspension:
      if (id != -1) {
        lock_map_.erase(id);
        NWebScreenLockTracker::Instance().UnLock(id);
      }
      break;
    case mojom::WakeLockType::kPreventDisplaySleep:
    case mojom::WakeLockType::kPreventDisplaySleepAllowDimming:
      lock_map_.erase(id);
      NWebScreenLockTracker::Instance().UnLock(id);
      break;
    default:
      LOG(INFO) << "Unhandled block type " << type_;
  }
}

PowerSaveBlocker::PowerSaveBlocker(
    mojom::WakeLockType type,
    mojom::WakeLockReason reason,
    const std::string& description,
    scoped_refptr<base::SequencedTaskRunner> ui_task_runner,
    scoped_refptr<base::SingleThreadTaskRunner> blocking_task_runner,
    int32_t id)
    : delegate_(new Delegate(type)),
      ui_task_runner_(ui_task_runner),
      blocking_task_runner_(blocking_task_runner),
      id_(id) {
}

PowerSaveBlocker::~PowerSaveBlocker() {
  if (delegate_.get()) {
    delegate_->RemoveBlock(id_);
  }
}

void PowerSaveBlocker::InitDisplaySleepBlocker(const int32_t id) {
  if (delegate_.get()) {
    delegate_->ApplyBlock(id);
  }
}

}  // namespace device
