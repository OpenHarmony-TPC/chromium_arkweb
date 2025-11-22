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

#include "components/os_crypt/sync/ohos_huks_crypto.h"

#include <string>

#include "testing/gtest/include/gtest/gtest.h"

namespace crypto {

namespace ohos {

TEST(OhosKeyStoreUtilTest, TestEncryptDecrypt) {
  std::string plaintext;
  std::string result;
  std::string ciphertext;
  std::string alias = "chrome_huks_os_crypt_password_v1";

  // Test a simple string.
  plaintext = "hello";
  ASSERT_TRUE(
      OhosHuksCrypto::GetInstance().EncryptKey(alias, plaintext, &ciphertext));
  ASSERT_TRUE(
      OhosHuksCrypto::GetInstance().DecryptKey(alias, ciphertext, &result));
  EXPECT_EQ(plaintext, result);

  // Make sure it null terminates.
  plaintext.assign("hello", 3);
  ASSERT_TRUE(
      OhosHuksCrypto::GetInstance().EncryptKey(alias, plaintext, &ciphertext));
  ASSERT_TRUE(
      OhosHuksCrypto::GetInstance().DecryptKey(alias, ciphertext, &result));
  EXPECT_EQ(plaintext, "hel");

  // Test diff alias
  alias = "no_peanut";
  ASSERT_FALSE(
      OhosHuksCrypto::GetInstance().EncryptKey(alias, plaintext, &ciphertext));
  ASSERT_FALSE(
      OhosHuksCrypto::GetInstance().DecryptKey(alias, ciphertext, &result));
}

}  // namespace ohos

}  // namespace crypto
