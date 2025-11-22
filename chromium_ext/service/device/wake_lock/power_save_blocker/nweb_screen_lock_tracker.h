// Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef NWEB_SCREEN_LOCK_TRACKER_H
#define NWEB_SCREEN_LOCK_TRACKER_H

#define NWEB_EXPORT __attribute__((visibility("default")))

#include <functional>
#include <mutex>
#include <unordered_map>
using SetKeepScreenOn = std::function<void(bool)>;

class SetKeepScreenLock {
 public:
  SetKeepScreenLock(const SetKeepScreenOn& handle)
      : handle_(std::move(handle)) {}

  int32_t count_ = 0;

  SetKeepScreenOn handle_;
};

class SetKeepScreenLockHandle {
 public:
  SetKeepScreenLockHandle(int32_t id, const SetKeepScreenOn& handle);

  void AddScreenLockHandle(int32_t id, const SetKeepScreenOn& handle);

  void RemoveScreenLockHandle(int32_t id);

  bool IsEmpty();

  bool Lock(int32_t id);

  bool UnLock(int32_t id);

 private:
  enum ScreenOnOffReason {
    kRemoveLockHandle,
    kLockWithInvalidID,
    kLock,
    kUnlockWithInvalidID,
    kUnlock,
  };

  void set_screen_on(bool is_screen_on, ScreenOnOffReason reason);

  int32_t screen_lock_count_ = 0;

  int32_t screen_lock_invalid_id_count_ = 0;

  bool is_screen_on_ = false;

  std::unordered_map<int32_t, std::unique_ptr<SetKeepScreenLock>> handle_map_;
  std::mutex handle_map_mutex_;
};

class NWEB_EXPORT NWebScreenLockTracker {
 public:
  static NWebScreenLockTracker& Instance();
  void AddScreenLock(int32_t windowId,
                     int32_t id,
                     const SetKeepScreenOn& handle);
  void RemoveScreenLock(int32_t windowId, int32_t id);
  void Lock(int32_t id);
  void UnLock(int32_t id);

 private:
  std::mutex screen_lock_map_lock_;
  std::unordered_map<int32_t, std::unique_ptr<SetKeepScreenLockHandle>>
      screen_lock_map_;
};

#endif  // NWEB_SCREEN_LOCK_TRACKER_H
