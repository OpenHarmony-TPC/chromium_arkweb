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

#define private public
#include <accesstoken/ability_access_control.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "access_token_adapter_impl.h"
#include "arkweb/ohos_nweb/src/nweb_hilog.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ohos_adapter_helper.h"

using namespace OHOS::NWeb;
namespace OHOS::NWeb {

void FuzzVerifyAccessToken(FuzzedDataProvider* fdp) {
  std::vector<std::string> permissionTypes = {
      fdp->ConsumeRandomLengthString(64), "",
      fdp->ConsumeRandomLengthString(32) + "!@#$%^&*()_+-=[]{}|;':\",./<>?",
      "ohos.permission." + fdp->ConsumeRandomLengthString(32),
      fdp->ConsumeRandomLengthString(256)};
  AccessTokenAdapterImpl& instance = AccessTokenAdapterImpl::GetInstance();
  for (const std::string& permission : permissionTypes) {
    (void)instance.VerifyAccessToken(permission);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (data == nullptr || size == 0) {
    return 0;
  }
  FuzzedDataProvider fdp(data, size);
  FuzzVerifyAccessToken(&fdp);
  return 0;
}

}  // namespace OHOS::NWeb
