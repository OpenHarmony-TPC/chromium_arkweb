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

// Based on codec_buffer_wait_coordinator.cc originally written by
// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. 
 
#include "media/gpu/ohos/codec_buffer_wait_coordinator.h"

#include "base/metrics/histogram_macros.h"
#include "base/task/single_thread_task_runner.h"

namespace media {

struct FrameAvailableEvent
    : public base::RefCountedThreadSafe<FrameAvailableEvent> {
  FrameAvailableEvent()
      : event(base::WaitableEvent::ResetPolicy::AUTOMATIC,
              base::WaitableEvent::InitialState::NOT_SIGNALED) {}
  void Signal() { event.Signal(); }
  base::WaitableEvent event;

 private:
  friend class RefCountedThreadSafe<FrameAvailableEvent>;
  ~FrameAvailableEvent() = default;
};

CodecBufferWaitCoordinator::CodecBufferWaitCoordinator(
    scoped_refptr<gpu::NativeImageTextureOwner> texture_owner,
    scoped_refptr<gpu::RefCountedLock> drdc_lock)
    : RefCountedLockHelperDrDc(std::move(drdc_lock)),
      texture_owner_(std::move(texture_owner)),
      frame_available_event_(new FrameAvailableEvent()),
      task_runner_(base::SingleThreadTaskRunner::GetCurrentDefault()) {
  DCHECK(texture_owner_);
  texture_owner_->SetFrameAvailableCallback(base::BindRepeating(
      &FrameAvailableEvent::Signal, frame_available_event_));
}

CodecBufferWaitCoordinator::~CodecBufferWaitCoordinator() {
  DCHECK(texture_owner_);
}

void CodecBufferWaitCoordinator::SetReleaseTimeToNow() {
  AssertAcquiredDrDcLock();
  release_time_ = base::TimeTicks::Now();
}

bool CodecBufferWaitCoordinator::IsExpectingFrameAvailable() {
  AssertAcquiredDrDcLock();
  return !release_time_.is_null();
}

void CodecBufferWaitCoordinator::WaitForFrameAvailable() {
  AssertAcquiredDrDcLock();
  DCHECK(!release_time_.is_null());

  const base::TimeTicks call_time = base::TimeTicks::Now();
  const base::TimeDelta elapsed = call_time - release_time_;
  const base::TimeDelta remaining = max_wait_.value() - elapsed;
  release_time_ = base::TimeTicks();
  bool timed_out = false;

  if (remaining <= base::TimeDelta()) {
    if (!frame_available_event_->event.IsSignaled()) {
      LOG(ERROR) << "Deferred WaitForFrameAvailable() timed out, elapsed: "
                 << elapsed.InMillisecondsF() << "ms";
      timed_out = true;
    }
  } else {
    DCHECK_LE(remaining, max_wait_.value());
    if (!frame_available_event_->event.TimedWait(remaining)) {
      LOG(ERROR) << "WaitForFrameAvailable() timed out, elapsed: "
                 << elapsed.InMillisecondsF()
                 << "ms, additionally waited: " << remaining.InMillisecondsF()
                 << "ms, total: " << (elapsed + remaining).InMillisecondsF()
                 << "ms";
      timed_out = true;
    }
  }
}

}  // namespace media
                     