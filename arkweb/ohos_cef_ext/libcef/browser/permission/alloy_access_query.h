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
 
#ifndef CEF_LIBCEF_BROWSER_PERMISSION_ALLOY_ACCESS_QUERY_H_
#define CEF_LIBCEF_BROWSER_PERMISSION_ALLOY_ACCESS_QUERY_H_
 
#include <memory>
 
#include "include/cef_permission_status_query.h"
 
class AlloyAccessQuery : public CefAccessQuery {
 public:
  AlloyAccessQuery(const AlloyAccessQuery&) = delete;
  AlloyAccessQuery& operator=(const AlloyAccessQuery&) = delete;
 
  AlloyAccessQuery(const CefString& origin,
                   int resources,
                   cef_permission_status_query_callback_t callback);
  ~AlloyAccessQuery() override;
 
  CefString Origin() override;
 
  int ResourceAcessId() override;
 
  void ReportQueryResult(int32_t status) override;
 
private:
 CefString origin_;
 int resources_;
 cef_permission_status_query_callback_t callback_;
 
 IMPLEMENT_REFCOUNTING(AlloyAccessQuery);
};
 
#endif  // CEF_LIBCEF_BROWSER_PERMISSION_ALLOY_ACCESS_QUERY_H_