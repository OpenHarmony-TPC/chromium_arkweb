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
#include "components/crx_file/crx_key_service.h"

namespace crx_file {
class CrxKeyServiceTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST(CrxKeyServiceTest, SetPublisherKeysEmptyPath) {
  auto* service = CrxKeyService::GetInstance();
  service->SetPublisherKeys({});
  auto crx2_key = service->GetCrx2PublicKey();
  auto crx3_hashes = service->GetCrx3PublicKeyHashes();
  EXPECT_TRUE(crx2_key.empty());
  EXPECT_TRUE(crx3_hashes.empty());
}

TEST(CrxKeyServiceTest, SetPublisherKeysSingleKeyPath) {
  auto* service = CrxKeyService::GetInstance();
  std::vector<uint8_t> test_key = {0x01, 0x02, 0x03};
  service->SetPublisherKeys({test_key});
  auto crx2_key = service->GetCrx2PublicKey();
  EXPECT_EQ(test_key, crx2_key);
  auto crx3_hashes = service->GetCrx3PublicKeyHashes();
  EXPECT_EQ(1u, crx3_hashes.size());
}

TEST(CrxKeyServiceTest, SetPublisherKeysMultipleKeysPath) {
  auto* service = CrxKeyService::GetInstance();
  std::vector<uint8_t> key1 = {0x01, 0x02};
  std::vector<uint8_t> key2 = {0x03, 0x04};
  std::vector<uint8_t> key3 = {0x05, 0x06};
  service->SetPublisherKeys({key1, key2, key3});
  auto crx2_key = service->GetCrx2PublicKey();
  EXPECT_EQ(key1, crx2_key);
  auto crx3_hashes = service->GetCrx3PublicKeyHashes();
  EXPECT_EQ(3u, crx3_hashes.size());
}
}  // namespace crx_file
