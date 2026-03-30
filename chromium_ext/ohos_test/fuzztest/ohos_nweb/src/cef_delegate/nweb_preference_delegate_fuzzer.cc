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

#include "ohos_nweb/src/cef_delegate/nweb_preference_delegate.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "ohos_nweb/include/nweb.h"
#include "ohos_nweb/src/nweb_impl.h"

using namespace OHOS::NWeb;

void NWebPutUserAgentFuzzTest(FuzzedDataProvider* fdp) {
    NWebPreferenceDelegate delegate;

    std::string ua = fdp->ConsumeRandomLengthString(256);
    delegate.PutUserAgent(ua);
}

void NWebPutOverscrollModeFuzzTest(FuzzedDataProvider* fdp) {
    NWebPreferenceDelegate delegate;

    int mode = fdp->ConsumeIntegralInRange<int>(0, 64);
    delegate.PutOverscrollMode(mode);
}

void NWebSetScrollableFuzzTest(FuzzedDataProvider* fdp) {
    NWebPreferenceDelegate delegate;

    int32_t scrollType = fdp->ConsumeIntegralInRange<int32_t>(0, 64);
    bool enable = fdp->ConsumeBool();
    delegate.SetScrollable(enable, scrollType);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
   if (data == nullptr || size == 0) {
    return 0;
  }
 
  FuzzedDataProvider fdp(data, size);

  NWebPutUserAgentFuzzTest(&fdp);
  NWebPutOverscrollModeFuzzTest(&fdp);
  NWebSetScrollableFuzzTest(&fdp);
  return 0;
}
