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

#include "ohos_nweb/src/nweb_web_storage_impl.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "ohos_nweb/include/nweb.h"
#include "ohos_nweb/src/nweb_impl.h"

using namespace OHOS::NWeb;

void NWebDeleteOriginFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageImpl impl;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    impl.DeleteOrigin(origin);
}

void NWebGetOriginQuotaFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageImpl impl;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    impl.GetOriginQuota(origin);
}

void NWebGetOriginUsageFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageImpl impl;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    impl.GetOriginUsage(origin);
}

void NWebGetPasswordFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageImpl impl;

    std::string url = fdp->ConsumeRandomLengthString(256);
    std::string username = fdp->ConsumeRandomLengthString(64);
    int callback_id = fdp->ConsumeIntegralInRange<int>(0, 64);
    impl.GetPassword(url, username, callback_id);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
   if (data == nullptr || size == 0) {
    return 0;
  }

  FuzzedDataProvider fdp(data, size);

  NWebDeleteOriginFuzzTest(&fdp);
  NWebGetOriginQuotaFuzzTest(&fdp);
  NWebGetOriginUsageFuzzTest(&fdp);
  NWebGetPasswordFuzzTest(&fdp);
  return 0;
}
