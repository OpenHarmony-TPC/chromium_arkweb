// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <chrono>
#include <cmath>
#include "ohos_sdk/openharmony/native/llvm/bin/../include/libcxx-ohos/include/c++/v1/__ranges/lazy_split_view.h"
#include "base/features.h"
#include "base/test/test_simple_task_runner.h"
#define private public
#include "base/ohos/ltpo/include/dynamic_frame_rate_decision.h"
#undef private
#include "build/build_config.h"
#if BUILDFLAG(ARKWEB_SLIDE_LTPO)

#include "base/no_destructor.h"
#include "base/task/single_thread_task_executor.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/thread_pool.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/test/bind.h"
#include "base/test/task_environment.h"
#include "base/trace_event/trace_event.h"
#include "build/build_config.h"
#include "content/public/browser/browser_thread.h"
#include "ohos_adapter_helper.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace base {
namespace ohos {

class DynamicFrameRateDecisionTest : public DynamicFrameRateDecision {
 public:
  DynamicFrameRateDecisionTest() = default;
};

TEST(DynamicFrameRateDecisionTest, Init) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  // Assign a value to dynamixFrameRateDecision.curent_task_runner_
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
}

TEST(DynamicFrameRateDecisionTest, Init001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.curent_task_runner_ = task_runner_1;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate001) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of false
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = false;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate002) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  if (dynamixFrameRateDecision.GetCurrentTimestampMS() -
          dynamixFrameRateDecision.touch_up_timestamp_ <
      3000) {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
  } else {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
  }
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate003) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.sliding_frame_rate_ a value of 10
  dynamixFrameRateDecision.sliding_frame_rate_ = 10;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  // dynamixFrameRateDecision.cur_frame_rate_ is 10
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 10);
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate004) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.sliding_frame_rate_ a value of 100
  dynamixFrameRateDecision.sliding_frame_rate_ = 100;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  // dynamixFrameRateDecision.cur_frame_rate_ is 100
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 100);
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate005) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.sliding_frame_rate_ a value of -10
  dynamixFrameRateDecision.sliding_frame_rate_ = -10;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  if (dynamixFrameRateDecision.GetCurrentTimestampMS() -
          dynamixFrameRateDecision.touch_up_timestamp_ <
      3000) {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
  } else {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
  }
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate006) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.video_frame_rate_ a value of 10
  dynamixFrameRateDecision.video_frame_rate_ = 10;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  if (dynamixFrameRateDecision.GetCurrentTimestampMS() -
          dynamixFrameRateDecision.touch_up_timestamp_ <
      3000) {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
  } else {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 10);
  }
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate007) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.video_frame_rate_ a value of 70
  dynamixFrameRateDecision.video_frame_rate_ = 70;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  if (dynamixFrameRateDecision.GetCurrentTimestampMS() -
          dynamixFrameRateDecision.touch_up_timestamp_ <
      3000) {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
  } else {
    EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 70);
  }
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate008) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.video_frame_rate_ a value of 200
  dynamixFrameRateDecision.video_frame_rate_ = 200;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  // dynamixFrameRateDecision.cur_frame_rate_ is 200
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 200);
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate009) {
  // Assign dynamixFrameRateDecision.frame_rate_linker_enable_ a value of true
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.video_frame_rate_ a value of 60
  dynamixFrameRateDecision.video_frame_rate_ = 60;
  dynamixFrameRateDecision.sliding_frame_rate_ = 10;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  // dynamixFrameRateDecision.cur_frame_rate_ is 60
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate010) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  // Assign dynamixFrameRateDecision.sliding_frame_rate_ a value of 80
  dynamixFrameRateDecision.video_frame_rate_ = 10;
  dynamixFrameRateDecision.sliding_frame_rate_ = 80;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  // dynamixFrameRateDecision.cur_frame_rate_ is 80
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 80);
}

TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate011) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.has_touch_point_  = true;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
}

// UpdateFramePreferredRate: 012 - sliding_frame_rate=60, video_frame_rate=30
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate012) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 60;
  dynamixFrameRateDecision.video_frame_rate_ = 30;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
}

// UpdateFramePreferredRate: 013 - sliding_frame_rate=30, video_frame_rate=60
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate013) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 30;
  dynamixFrameRateDecision.video_frame_rate_ = 60;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
}

// UpdateFramePreferredRate: 014 - within 3 sec touch-up window
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate014) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.touch_up_timestamp_ = dynamixFrameRateDecision.GetCurrentTimestampMS();
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
}

// UpdateFramePreferredRate: 015 - after 3 sec touch-up window
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate015) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.video_frame_rate_ = 0;
  dynamixFrameRateDecision.touch_up_timestamp_ = dynamixFrameRateDecision.GetCurrentTimestampMS() - 4000;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
}

// UpdateFramePreferredRate: 016 - exactly 3 sec boundary
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate016) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.touch_up_timestamp_ = dynamixFrameRateDecision.GetCurrentTimestampMS() - 3000;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
}

// UpdateFramePreferredRate: 017 - just under 3 sec
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate017) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.touch_up_timestamp_ = dynamixFrameRateDecision.GetCurrentTimestampMS() - 2999;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
}

// UpdateFramePreferredRate: 018 - video rate only after 3 sec
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate018) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.video_frame_rate_ = 30;
  dynamixFrameRateDecision.touch_up_timestamp_ = dynamixFrameRateDecision.GetCurrentTimestampMS() - 4000;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 30);
}

// UpdateFramePreferredRate: 019 - all zero rates
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate019) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.video_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.touch_up_timestamp_ = dynamixFrameRateDecision.GetCurrentTimestampMS() - 4000;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
}

// UpdateFramePreferredRate: 020 - negative sliding rate
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate020) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = -10;
  dynamixFrameRateDecision.video_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.touch_up_timestamp_ = dynamixFrameRateDecision.GetCurrentTimestampMS() - 4000;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
}

// UpdateFramePreferredRate: 021 - video higher than sliding
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate021) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 90;
  dynamixFrameRateDecision.video_frame_rate_ = 120;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
}

// UpdateFramePreferredRate: 022 - high frame rates 120 and 144
TEST(DynamicFrameRateDecisionTest, UpdateFramePreferredRate022) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.sliding_frame_rate_ = 120;
  dynamixFrameRateDecision.video_frame_rate_ = 144;
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 144);
}

TEST(DynamicFrameRateDecisionTest, SetVisible001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign dynamixFrameRateDecision.curent_task_runner_ a value of nullptr
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  bool measuring_param = true;
  dynamixFrameRateDecision.SetVisible(0, measuring_param);
  // dynamixFrameRateDecision.visible_ is false
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

TEST(DynamicFrameRateDecisionTest, SetVisible002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign dynamixFrameRateDecision.curent_task_runner_ a value of nullptr
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  bool measuring_param = false;
  dynamixFrameRateDecision.SetVisible(0, measuring_param);
  // dynamixFrameRateDecision.visible_ is false
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

TEST(DynamicFrameRateDecisionTest, SetVisible003) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign a value to dynamixFrameRateDecision.curent_task_runner_
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = true;
  dynamixFrameRateDecision.SetVisible(0, measuring_param);
  // dynamixFrameRateDecision.visible_ is true
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

TEST(DynamicFrameRateDecisionTest, SetVisible004) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = false;
  dynamixFrameRateDecision.SetVisible(0, measuring_param);
  // dynamixFrameRateDecision.visible_ is false
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

TEST(DynamicFrameRateDecisionTest, SetVisibleImpl001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.nwebVisibleSet_.insert(1);
  dynamixFrameRateDecision.SetVisibleImpl(1, false);
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

TEST(DynamicFrameRateDecisionTest, SetVisibleImpl002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  EXPECT_FALSE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

// SetVisibleImpl: 003 - multiple nweb ids
TEST(DynamicFrameRateDecisionTest, SetVisibleImpl003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  dynamixFrameRateDecision.SetVisibleImpl(2, true);
  dynamixFrameRateDecision.SetVisibleImpl(3, true);
  EXPECT_EQ(dynamixFrameRateDecision.nwebVisibleSet_.size(), 3u);
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.count(1));
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.count(2));
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.count(3));
}

// SetVisibleImpl: 004 - ALL strategy
TEST(DynamicFrameRateDecisionTest, SetVisibleImpl004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  EXPECT_FALSE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.count(1));
}

// SetVisibleImpl: 005 - DISABLED strategy
TEST(DynamicFrameRateDecisionTest, SetVisibleImpl005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::DISABLED;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

// SetVisibleImpl: 006 - APS_FLING strategy
TEST(DynamicFrameRateDecisionTest, SetVisibleImpl006) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::APS_FLING;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

// SetVisibleImpl: 007 - duplicate insert
TEST(DynamicFrameRateDecisionTest, SetVisibleImpl007) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  EXPECT_EQ(dynamixFrameRateDecision.nwebVisibleSet_.size(), 1u);
}

// SetVisibleImpl: 008 - remove non-existent
TEST(DynamicFrameRateDecisionTest, SetVisibleImpl008) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.SetVisibleImpl(1, false);
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
}

// SetVisibleImpl: 009 - frame rate linker enable
TEST(DynamicFrameRateDecisionTest, SetVisibleImpl009) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign dynamixFrameRateDecision.curent_task_runner_ a value of nullptr
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = 10;
  // The incoming argument is 10
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);
  // dynamixFrameRateDecision.sliding_frame_rate_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = 0;
  // The incoming argument is 0
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);
  // dynamixFrameRateDecision.sliding_frame_rate_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = -10;
  // The incoming argument is -10
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);
  // dynamixFrameRateDecision.sliding_frame_rate_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate004) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign a value to dynamixFrameRateDecision.curent_task_runner_
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  // The incoming argument is 10
  int32_t measuring_param = 10;
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);
  // dynamixFrameRateDecision.sliding_frame_rate_ is 0
  EXPECT_NE(dynamixFrameRateDecision.sliding_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate005) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  // The incoming argument is 0
  int32_t measuring_param = 0;
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);

  // dynamixFrameRateDecision.sliding_frame_rate_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate006) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  // The incoming argument is -10
  int32_t measuring_param = -10;
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);
  // dynamixFrameRateDecision.sliding_frame_rate_ is -10
  EXPECT_NE(dynamixFrameRateDecision.sliding_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate007) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  // The incoming argument is 1000
  int32_t measuring_param = 1000;
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);
  // dynamixFrameRateDecision.sliding_frame_rate_ is 1000
  EXPECT_NE(dynamixFrameRateDecision.sliding_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRate008) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  // The incoming argument is -1000
  int32_t measuring_param = -1000;
  dynamixFrameRateDecision.ReportSlidingFrameRate(measuring_param);
  // dynamixFrameRateDecision.sliding_frame_rate_ is -1000
  EXPECT_NE(dynamixFrameRateDecision.sliding_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign dynamixFrameRateDecision.curent_task_runner_ a value of nullptr
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = 0;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is 0, dynamixFrameRateDecision.video_frame_rate_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = 10;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is 10, dynamixFrameRateDecision.video_frame_rate_ is
  // 0
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = -10;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is -10, dynamixFrameRateDecision.video_frame_rate_ is
  // 0
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate004) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign a value to dynamixFrameRateDecision.curent_task_runner_
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = -10;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is -10, dynamixFrameRateDecision.video_frame_rate_ is
  // -10
  EXPECT_NE(dynamixFrameRateDecision.video_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate005) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = 0;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is 0, dynamixFrameRateDecision.video_frame_rate_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate006) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = 10;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is 10, dynamixFrameRateDecision.video_frame_rate_ is
  // 10
  EXPECT_NE(dynamixFrameRateDecision.video_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate007) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = 1000;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is 1000, dynamixFrameRateDecision.video_frame_rate_
  // is 1000
  EXPECT_NE(dynamixFrameRateDecision.video_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRate008) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  int32_t measuring_param = -1000;
  dynamixFrameRateDecision.ReportVideoFrameRate(measuring_param);
  // The incoming argument is -1000, dynamixFrameRateDecision.video_frame_rate_
  // is -1000
  EXPECT_NE(dynamixFrameRateDecision.video_frame_rate_, measuring_param);
}

TEST(DynamicFrameRateDecisionTest, SetVsyncEnabled001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign dynamixFrameRateDecision.curent_task_runner_ a value of nullptr
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = true;
  dynamixFrameRateDecision.SetVsyncEnabled(measuring_param);
  // dynamixFrameRateDecision.vsync_cnt_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 0);
}

TEST(DynamicFrameRateDecisionTest, SetVsyncEnabled002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = false;
  dynamixFrameRateDecision.SetVsyncEnabled(measuring_param);
  // dynamixFrameRateDecision.vsync_cnt_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 0);
}

TEST(DynamicFrameRateDecisionTest, SetVsyncEnabled003) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign a value to dynamixFrameRateDecision.curent_task_runner_
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = true;
  dynamixFrameRateDecision.SetVsyncEnabled(measuring_param);
  EXPECT_NE(dynamixFrameRateDecision.vsync_cnt_, -1);
}

TEST(DynamicFrameRateDecisionTest, SetVsyncEnabled004) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = false;
  dynamixFrameRateDecision.SetVsyncEnabled(measuring_param);
  // The incoming argument is false ,dynamixFrameRateDecision.vsync_cnt_ is 0
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 0);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPoint001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign dynamixFrameRateDecision.curent_task_runner_ a value of nullptr
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = true;
  dynamixFrameRateDecision.SetHasTouchPoint(measuring_param);
  // dynamixFrameRateDecision.has_touch_point_ is false
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPoint002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  EXPECT_EQ(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = false;
  dynamixFrameRateDecision.SetHasTouchPoint(measuring_param);
  // dynamixFrameRateDecision.has_touch_point_ is false
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPoint003) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  // Assign a value to dynamixFrameRateDecision.curent_task_runner_
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = true;
  dynamixFrameRateDecision.SetHasTouchPoint(measuring_param);
  // The incoming argument is true ,dynamixFrameRateDecision.has_touch_point_ is
  // true
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPoint004) {
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.Init();
  EXPECT_NE(nullptr, dynamixFrameRateDecision.curent_task_runner_);
  bool measuring_param = false;
  dynamixFrameRateDecision.SetHasTouchPoint(measuring_param);
  // The incoming argument is false ,dynamixFrameRateDecision.has_touch_point_
  // is false
  EXPECT_TRUE(dynamixFrameRateDecision.has_touch_point_ == false);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(1);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(0);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(1);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 1);
}

// ReportSlidingFrameRateImpl: 004 - ALL strategy
TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 60);
}

// ReportSlidingFrameRateImpl: 005 - same frame rate
TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.sliding_frame_rate_ = 60;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 60);
}

// ReportSlidingFrameRateImpl: 006 - zero frame rate
TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl006) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.sliding_frame_rate_ = 60;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(0);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

// ReportSlidingFrameRateImpl: 007 - negative frame rate
TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl007) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(-10);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, -10);
}

// ReportSlidingFrameRateImpl: 008 - DISABLED strategy
TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl008) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::DISABLED;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

// ReportSlidingFrameRateImpl: 009 - APS_FLING strategy
TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl009) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::APS_FLING;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
}

// ReportSlidingFrameRateImpl: 010 - consecutive different rates
TEST(DynamicFrameRateDecisionTest, ReportSlidingFrameRateImpl010) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(30);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 30);
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 60);
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(90);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 90);
}

TEST(DynamicFrameRateDecisionTest, SetMaxFrameRateThreeSec001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.sliding_frame_rate_ = 1;
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  EXPECT_EQ(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

TEST(DynamicFrameRateDecisionTest, SetMaxFrameRateThreeSec002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  EXPECT_EQ(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

TEST(DynamicFrameRateDecisionTest, SetMaxFrameRateThreeSec003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  EXPECT_NE(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

// SetMaxFrameRateThreeSec: 004 - non-zero sliding rate
TEST(DynamicFrameRateDecisionTest, SetMaxFrameRateThreeSec004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.sliding_frame_rate_ = 60;
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  EXPECT_EQ(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

// SetMaxFrameRateThreeSec: 005 - zero vsync_cnt
TEST(DynamicFrameRateDecisionTest, SetMaxFrameRateThreeSec005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.vsync_cnt_ = 0;
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  EXPECT_EQ(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

// SetMaxFrameRateThreeSec: 006 - valid conditions
TEST(DynamicFrameRateDecisionTest, SetMaxFrameRateThreeSec006) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  EXPECT_NE(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

// SetMaxFrameRateThreeSec: 007 - multiple calls
TEST(DynamicFrameRateDecisionTest, SetMaxFrameRateThreeSec007) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  int64_t first_timestamp = dynamixFrameRateDecision.touch_up_timestamp_;
  EXPECT_NE(first_timestamp, 0);
  dynamixFrameRateDecision.SetMaxFrameRateThreeSec();
  int64_t second_timestamp = dynamixFrameRateDecision.touch_up_timestamp_;
  EXPECT_GE(second_timestamp, first_timestamp);
}

TEST(DynamicFrameRateDecisionTest, SetLTPOStrategy001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.curent_task_runner_ = nullptr;
  ASSERT_NO_FATAL_FAILURE(dynamixFrameRateDecision.SetLTPOStrategy(1));
}

TEST(DynamicFrameRateDecisionTest, SetLTPOStrategy002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.SetLTPOStrategy(1);
  EXPECT_EQ(dynamixFrameRateDecision.strategy_, LTPOStrategy::DISABLED);
}

TEST(DynamicFrameRateDecisionTest, SetLTPOStrategyImpl001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetLTPOStrategyImpl(-1);
  EXPECT_EQ(dynamixFrameRateDecision.strategy_, LTPOStrategy::DISABLED);
}

TEST(DynamicFrameRateDecisionTest, SetLTPOStrategyImpl002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetLTPOStrategyImpl(3);
  EXPECT_EQ(dynamixFrameRateDecision.strategy_, LTPOStrategy::ALL);
}

// SetLTPOStrategyImpl: 003 - boundary values
TEST(DynamicFrameRateDecisionTest, SetLTPOStrategyImpl003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetLTPOStrategyImpl(0);
  EXPECT_EQ(dynamixFrameRateDecision.strategy_, LTPOStrategy::DISABLED);
  dynamixFrameRateDecision.SetLTPOStrategyImpl(3);
  EXPECT_EQ(dynamixFrameRateDecision.strategy_, LTPOStrategy::ALL);
}

// SetLTPOStrategyImpl: 004 - large value
TEST(DynamicFrameRateDecisionTest, SetLTPOStrategyImpl004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetLTPOStrategyImpl(100);
  EXPECT_EQ(static_cast<int>(dynamixFrameRateDecision.strategy_), 100);
}

// SetLTPOStrategyImpl: 005 - zero value
TEST(DynamicFrameRateDecisionTest, SetLTPOStrategyImpl005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.SetLTPOStrategyImpl(0);
  EXPECT_EQ(dynamixFrameRateDecision.strategy_, LTPOStrategy::DISABLED);
}

TEST(DynamicFrameRateDecisionTest, SetVsyncEnabledImpl001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 1);
}

TEST(DynamicFrameRateDecisionTest, SetVsyncEnabledImpl002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetVsyncEnabledImpl(false);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 0);
}

// SetVsyncEnabledImpl: 003 - multiple enable
TEST(DynamicFrameRateDecisionTest, SetVsyncEnabledImpl003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 1);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 2);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 3);
}

// SetVsyncEnabledImpl: 004 - multiple disable not go negative
TEST(DynamicFrameRateDecisionTest, SetVsyncEnabledImpl004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.vsync_cnt_ = 2;
  dynamixFrameRateDecision.SetVsyncEnabledImpl(false);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 1);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(false);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 0);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(false);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 0);
}

// SetVsyncEnabledImpl: 005 - enable disable sequence
TEST(DynamicFrameRateDecisionTest, SetVsyncEnabledImpl005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 1);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(false);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 0);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 1);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 2);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(false);
  EXPECT_EQ(dynamixFrameRateDecision.vsync_cnt_, 1);
}

// SetVsyncEnabledImpl: 006 - with visible set
TEST(DynamicFrameRateDecisionTest, SetVsyncEnabledImpl006) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.nwebVisibleSet_.insert(1);
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

// SetVsyncEnabledImpl: 007 - empty visible set
TEST(DynamicFrameRateDecisionTest, SetVsyncEnabledImpl007) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
  dynamixFrameRateDecision.SetVsyncEnabledImpl(true);
  EXPECT_FALSE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(1);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(0);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(1);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 1);
}

// ReportVideoFrameRateImpl: 004 - HGM_FLING strategy
TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

// ReportVideoFrameRateImpl: 005 - DISABLED strategy
TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::DISABLED;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

// ReportVideoFrameRateImpl: 006 - APS_FLING strategy
TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl006) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::APS_FLING;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 0);
}

// ReportVideoFrameRateImpl: 007 - same frame rate
TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl007) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.video_frame_rate_ = 30;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(30);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 30);
}

// ReportVideoFrameRateImpl: 008 - consecutive different rates
TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl008) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(24);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 24);
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(30);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 30);
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 60);
}

// ReportVideoFrameRateImpl: 009 - common video rates
TEST(DynamicFrameRateDecisionTest, ReportVideoFrameRateImpl009) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(24);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 24);
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(25);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 25);
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(30);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 30);
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(50);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 50);
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 60);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.SetHasTouchPointImpl(false);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_TRUE(dynamixFrameRateDecision.has_touch_point_);
}

TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.has_touch_point_ = true;
  dynamixFrameRateDecision.SetHasTouchPointImpl(false);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

// SetHasTouchPointImpl: 005 - HGM_FLING strategy
TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::HGM_FLING;
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

// SetHasTouchPointImpl: 006 - DISABLED strategy
TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl006) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::DISABLED;
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

// SetHasTouchPointImpl: 007 - APS_FLING strategy
TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl007) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::APS_FLING;
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

// SetHasTouchPointImpl: 008 - same value true
TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl008) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.has_touch_point_ = true;
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_TRUE(dynamixFrameRateDecision.has_touch_point_);
}

// SetHasTouchPointImpl: 009 - same value false
TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl009) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.SetHasTouchPointImpl(false);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
}

// SetHasTouchPointImpl: 010 - touch down updates frame rate
TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl010) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.has_touch_point_ = false;
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_TRUE(dynamixFrameRateDecision.has_touch_point_);
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 120);
}

// SetHasTouchPointImpl: 011 - touch up triggers timeout
TEST(DynamicFrameRateDecisionTest, SetHasTouchPointImpl011) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.sliding_frame_rate_ = 0;
  dynamixFrameRateDecision.has_touch_point_ = true;
  dynamixFrameRateDecision.SetHasTouchPointImpl(false);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
  EXPECT_NE(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

TEST(DynamicFrameRateDecisionTest, SetFrameRateLinkerEnable001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(false);
  EXPECT_FALSE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

TEST(DynamicFrameRateDecisionTest, SetFrameRateLinkerEnable002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(true);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

// SetFrameRateLinkerEnable: 003 - already true
TEST(DynamicFrameRateDecisionTest, SetFrameRateLinkerEnable003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(true);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

// SetFrameRateLinkerEnable: 004 - already false
TEST(DynamicFrameRateDecisionTest, SetFrameRateLinkerEnable004) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = false;
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(false);
  EXPECT_FALSE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

// SetFrameRateLinkerEnable: 005 - toggle
TEST(DynamicFrameRateDecisionTest, SetFrameRateLinkerEnable005) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = false;
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(true);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(false);
  EXPECT_FALSE(dynamixFrameRateDecision.frame_rate_linker_enable_);
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(true);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

// GetCurrentTimestampMS: 001 - returns valid value
TEST(DynamicFrameRateDecisionTest, GetCurrentTimestampMS001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  int64_t timestamp = dynamixFrameRateDecision.GetCurrentTimestampMS();
  EXPECT_GT(timestamp, 0);
}

// GetCurrentTimestampMS: 002 - monotonic increase
TEST(DynamicFrameRateDecisionTest, GetCurrentTimestampMS002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  int64_t timestamp1 = dynamixFrameRateDecision.GetCurrentTimestampMS();
  int64_t timestamp2 = dynamixFrameRateDecision.GetCurrentTimestampMS();
  EXPECT_GE(timestamp2, timestamp1);
}

// GetCurrentTimestampMS: 003 - reasonable range
TEST(DynamicFrameRateDecisionTest, GetCurrentTimestampMS003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  int64_t timestamp = dynamixFrameRateDecision.GetCurrentTimestampMS();
  EXPECT_GT(timestamp, 1577836800000LL);
  EXPECT_LT(timestamp, 4102444800000LL);
}

// GetInstance: 001 - returns same instance
TEST(DynamicFrameRateDecisionTest, GetInstance001) {
  DynamicFrameRateDecision& instance1 = DynamicFrameRateDecision::GetInstance();
  DynamicFrameRateDecision& instance2 = DynamicFrameRateDecision::GetInstance();
  EXPECT_EQ(&instance1, &instance2);
}

// GetInstance: 002 - not null
TEST(DynamicFrameRateDecisionTest, GetInstance002) {
  DynamicFrameRateDecision& instance = DynamicFrameRateDecision::GetInstance();
  EXPECT_NE(&instance, nullptr);
}

// Integration: 001 - full sliding cycle
TEST(DynamicFrameRateDecisionTest, Integration001) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  scoped_refptr<SingleThreadTaskRunner> task_runner_1(MakeRefCounted<TestSimpleTaskRunner>());
  SingleThreadTaskRunner::CurrentDefaultHandle sttcd1(task_runner_1);
  dynamixFrameRateDecision.Init();
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.nwebVisibleSet_.insert(1);
  dynamixFrameRateDecision.SetFrameRateLinkerEnable(true);
  dynamixFrameRateDecision.SetHasTouchPointImpl(true);
  EXPECT_TRUE(dynamixFrameRateDecision.has_touch_point_);
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(90);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 90);
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 90);
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(0);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 0);
  dynamixFrameRateDecision.SetHasTouchPointImpl(false);
  EXPECT_FALSE(dynamixFrameRateDecision.has_touch_point_);
  EXPECT_NE(dynamixFrameRateDecision.touch_up_timestamp_, 0);
}

// Integration: 002 - video and sliding conflict
TEST(DynamicFrameRateDecisionTest, Integration002) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.frame_rate_linker_enable_ = true;
  dynamixFrameRateDecision.ReportVideoFrameRateImpl(30);
  EXPECT_EQ(dynamixFrameRateDecision.video_frame_rate_, 30);
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(60);
  EXPECT_EQ(dynamixFrameRateDecision.sliding_frame_rate_, 60);
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 60);
  dynamixFrameRateDecision.ReportSlidingFrameRateImpl(24);
  dynamixFrameRateDecision.UpdateFramePreferredRate();
  EXPECT_EQ(dynamixFrameRateDecision.cur_frame_rate_, 30);
}

// Integration: 003 - multiple nweb visibility
TEST(DynamicFrameRateDecisionTest, Integration003) {
  DynamicFrameRateDecision dynamixFrameRateDecision;
  dynamixFrameRateDecision.strategy_ = LTPOStrategy::ALL;
  dynamixFrameRateDecision.vsync_cnt_ = 1;
  dynamixFrameRateDecision.SetVisibleImpl(1, true);
  EXPECT_EQ(dynamixFrameRateDecision.nwebVisibleSet_.size(), 1u);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
  dynamixFrameRateDecision.SetVisibleImpl(2, true);
  EXPECT_EQ(dynamixFrameRateDecision.nwebVisibleSet_.size(), 2u);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
  dynamixFrameRateDecision.SetVisibleImpl(1, false);
  EXPECT_EQ(dynamixFrameRateDecision.nwebVisibleSet_.size(), 1u);
  EXPECT_TRUE(dynamixFrameRateDecision.frame_rate_linker_enable_);
  dynamixFrameRateDecision.SetVisibleImpl(2, false);
  EXPECT_TRUE(dynamixFrameRateDecision.nwebVisibleSet_.empty());
  EXPECT_FALSE(dynamixFrameRateDecision.frame_rate_linker_enable_);
}

}  // namespace ohos
}  // namespace base
#endif
