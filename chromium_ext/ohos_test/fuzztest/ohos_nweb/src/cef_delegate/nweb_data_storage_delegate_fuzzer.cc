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

#include "ohos_nweb/src/cef_delegate/nweb_web_storage_delegate.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "ohos_nweb/include/nweb.h"
#include "ohos_nweb/src/nweb_impl.h"

using namespace OHOS::NWeb;

void NWebDeleteOriginFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    delegate.DeleteOrigin(origin);
}

void NWebGetOriginQuotaFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    delegate.GetOriginQuota(origin);
}

void NWebGetOriginUsageFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    delegate.GetOriginUsage(origin);
}

void NWebGetPasswordFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    std::string url = fdp->ConsumeRandomLengthString(256);
    std::string username = fdp->ConsumeRandomLengthString(32);
    int callback_id = fdp->ConsumeIntegralInRange<int>(0, 64);
    delegate.GetPassword(url, username, callback_id);
}

void NWebGetSavedPasswordsInfoFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    int callback_id = fdp->ConsumeIntegralInRange<int>(0, 64);
    delegate.GetSavedPasswordsInfo(callback_id);
}

void NWebRemovePasswordFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    std::string origin = fdp->ConsumeRandomLengthString(256);
    std::string username = fdp->ConsumeRandomLengthString(64);
    delegate.RemovePassword(origin, username);
}

void NWebModifyPasswordFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    std::string url = fdp->ConsumeRandomLengthString(256);
    std::string old_username = fdp->ConsumeRandomLengthString(64);
    std::string new_username = fdp->ConsumeRandomLengthString(64);
    std::string new_code = fdp->ConsumeRandomLengthString(64);
    delegate.ModifyPassword(url, old_username, new_username, new_code);
}

void NWebRemovePasswordByUrlFuzzTest(FuzzedDataProvider* fdp) {
    NWebWebStorageDelegate delegate;

    std::string url = fdp->ConsumeRandomLengthString(256);
    delegate.RemovePasswordByUrl(url);
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
  NWebGetSavedPasswordsInfoFuzzTest(&fdp);
  NWebRemovePasswordFuzzTest(&fdp);
  NWebModifyPasswordFuzzTest(&fdp);
  NWebRemovePasswordByUrlFuzzTest(&fdp);
  return 0;
}
