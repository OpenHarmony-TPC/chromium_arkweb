/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "base/android/linker/ashmem.h"

using namespace testing;
#define PROT_READ 0x1

class OhosAshmemTest : public ::testing::Test {
protected:
  void SetUp() override {
    fd_ = SharedMemoryRegionCreate("test_region", 4096);
    ASSERT_GE(fd_, 0) << "Failed to create ashmem region";
  }

  void TearDown() override {
    if (fd_ >= 0) close(fd_);
  }

  int fd_{-1};
};

TEST_F(OhosAshmemTest, SetGetProtection) {
  ASSERT_EQ(0, SharedMemoryRegionSetProtectionFlags(fd_, PROT_READ));
  ASSERT_EQ(PROT_READ, SharedMemoryRegionGetProtectionFlags(fd_));
}

TEST_F(OhosAshmemTest, PinUnpinRegion) {
  ASSERT_EQ(0, AshmemPinRegion(fd_, 0, 1024));
  ASSERT_EQ(0, AshmemUnpinRegion(fd_, 0, 1024));
}

TEST_F(OhosAshmemTest, DeviceSupportCheck) {
  ASSERT_EQ(1, AshmemDeviceIsSupported());
}

TEST_F(OhosAshmemTest, ashmem_create_region) {
  size_t size = 1;
  auto result = SharedMemoryRegionCreate(nullptr, size);
  ASSERT_EQ(12, result);
}