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

#include "ohos_nweb/src/cef_delegate/nweb_access_query_delegate.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "ohos_nweb/include/nweb.h"
#include "ohos_nweb/src/nweb_impl.h"

using namespace OHOS::NWeb;

class CefAccessQueryForFuzz : public CefAccessQuery{
public:
  using CefBaseRefCounted::AddRef;
  using CefBaseRefCounted::Release;
  using CefBaseRefCounted::HasOneRef;
  using CefBaseRefCounted::HasAtLeastOneRef;
  CefString Origin()  override {return CefString("");};
  int ResourceAcessId() override {return 0;};
  void ReportQueryResult(int32_t status) override {};
  void AddRef() const override {};
  bool Release() const override {return false;};
  bool HasOneRef() const override {return false;};
  bool HasAtLeastOneRef() const override {return false;};
};

void NWebAccessQueryDelegateFuzzTest(FuzzedDataProvider* fdp) {
  auto query = new CefAccessQueryForFuzz();
  NWebAccessQueryDelegate delegate(query);
  auto status = fdp->ConsumeIntegral<uint32_t>();
  delegate.ReportQueryResult(status);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
   if (data == nullptr || size == 0) {
    return 0;
  }

  FuzzedDataProvider fdp(data, size);

  NWebAccessQueryDelegateFuzzTest(&fdp);
  return 0;
}
