/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "nweb_image_info_impl.h"

#include "arkweb/build/features/features.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace OHOS::NWeb {
class NWebImageInfoImplTest : public ::testing::Test {
 public:
  static void SetUpTestCase(void);
  static void TearDownTestCase(void);
  void SetUp();
  void TearDown();
};

void NWebImageInfoImplTest::SetUpTestCase(void) {}

void NWebImageInfoImplTest::TearDownTestCase(void) {}

void NWebImageInfoImplTest::SetUp() {}

void NWebImageInfoImplTest::TearDown(void) {}


#if BUILDFLAG(ARKWEB_MEDIA)

TEST_F(NWebImageInfoImplTest, NWebImageInfoImplTest_001) {
    auto nweb_image = new NWebImageInfoImpl();
    nweb_image->SetColorType(0);
    nweb_image->SetAlphaType(0);
    nweb_image->SetData(nullptr);
    nweb_image->SetDataSize(0);
    nweb_image->SetWidth(0);
    nweb_image->SetHeight(0);
    nweb_image->GetColorType();
    nweb_image->GetAlphaType();
    nweb_image->GetData();
    nweb_image->GetDataSize();
    nweb_image->GetWidth();
    nweb_image->GetHeight();
    EXPECT_EQ(nweb_image->GetHeight(), 0);
}

#endif
}  // namespace OHOS::NWeb