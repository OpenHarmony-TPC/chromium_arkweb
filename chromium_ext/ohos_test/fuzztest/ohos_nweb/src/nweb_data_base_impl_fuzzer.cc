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

#include "ohos_nweb/src/nweb_data_base_impl.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "ohos_nweb/include/nweb.h"
#include "ohos_nweb/src/nweb_impl.h"

using namespace OHOS::NWeb;

void NWebSaveHttpAuthCredentialsFuzzTest(FuzzedDataProvider* fdp) {
    NWebDataBaseImpl impl;

    std::string host = fdp->ConsumeRandomLengthString(256);
    std::string realm = fdp->ConsumeRandomLengthString(256);
    std::string username = fdp->ConsumeRandomLengthString(32);
    char* pd = strdup((fdp->ConsumeRandomLengthString(64)).c_str());
    impl.SaveHttpAuthCredentials(host, realm, username, pd);
    free(pd);
}

void NWebGetHttpAuthCredentialsFuzzTest(FuzzedDataProvider* fdp) {
    NWebDataBaseImpl impl;

    std::string host = fdp->ConsumeRandomLengthString(256);
    std::string realm = fdp->ConsumeRandomLengthString(256);
    std::string username = fdp->ConsumeRandomLengthString(32);
    std::string passwordStr = fdp->ConsumeRandomLengthString(64);
    char* pd = strdup(passwordStr.c_str());
    uint32_t passwordSize = static_cast<uint32_t>(passwordStr.length());
    impl.GetHttpAuthCredentials(host, realm, username, pd, passwordSize);
    free(pd);
}

void NWebExistPermissionByOriginFuzzTest(FuzzedDataProvider* fdp) {
    NWebDataBaseImpl impl;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    int type = fdp->ConsumeIntegralInRange<int>(0, 64);
    bool incognito = false;
    impl.ExistPermissionByOrigin(origin, type, incognito);
}

void NWebGetPermissionResultByOriginFuzzTest(FuzzedDataProvider* fdp) {
    NWebDataBaseImpl impl;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    int type = fdp->ConsumeIntegralInRange<int>(0, 64);
    bool result = fdp->ConsumeBool();
    bool incognito = false;
    impl.GetPermissionResultByOrigin(origin, type, result, incognito);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
   if (data == nullptr || size == 0) {
    return 0;
  }

  FuzzedDataProvider fdp(data, size);

  NWebSaveHttpAuthCredentialsFuzzTest(&fdp);
  NWebGetHttpAuthCredentialsFuzzTest(&fdp);
  NWebExistPermissionByOriginFuzzTest(&fdp);
  NWebGetPermissionResultByOriginFuzzTest(&fdp);
  return 0;
}
