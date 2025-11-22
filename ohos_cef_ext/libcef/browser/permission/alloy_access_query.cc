// Copyright (c) 2022 Huawei Device Co., Ltd.
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
 
#include "ohos_cef_ext/libcef/browser/permission/alloy_access_query.h"
#include "base/logging.h"
 
AlloyAccessQuery::AlloyAccessQuery(const CefString& origin,
                                   int resources,
                                   cef_permission_status_query_callback_t callback)
    : origin_(origin), resources_(resources), callback_(std::move(callback)) {}
 
AlloyAccessQuery::~AlloyAccessQuery() {
  if (!callback_.is_null()) {
    std::move(callback_).Run(0);
  }
}
 
CefString AlloyAccessQuery::Origin() {
  return origin_;
}
 
int AlloyAccessQuery::ResourceAcessId() {
  return resources_;
}
 
void AlloyAccessQuery::ReportQueryResult(int32_t status) {
  if (!callback_.is_null()) {
    std::move(callback_).Run(status);
  }
}