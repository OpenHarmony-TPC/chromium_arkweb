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

#include "libcef/browser/net_database/cef_incognito_data_base_impl.h"

#include "base/functional/bind.h"
#include "base/logging.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/ohos_adapter_helper.h"

CefRefPtr<CefDataBase> CefDataBase::GetGlobalIncognitoDataBase() {
  CefRefPtr<CefRequestContext> context =
      CefRequestContext::GetGlobalOTRContext();
  LOG(INFO) << "GetGlobalIncognitoDataBase.";
  return context ? context->GetDataBase() : nullptr;
}

bool CefIncognitoDataBaseImpl::ExistHttpAuthCredentials() {
  return false;
}

void CefIncognitoDataBaseImpl::DeleteHttpAuthCredentials() {}

void CefIncognitoDataBaseImpl::SaveHttpAuthCredentials(
    const CefString& host,
    const CefString& realm,
    const CefString& username,
    const char* password) {}

void CefIncognitoDataBaseImpl::GetHttpAuthCredentials(const CefString& host,
                                                      const CefString& realm,
                                                      CefString& username,
                                                      char* password,
                                                      uint32_t passwordSize) {}

static OHOS::NWeb::WebPermissionType TypeToWebPermissionType(int type) {
  if (type == CefIncognitoDataBaseImpl::CefPermissionType::GEOLOCATION_TYPE) {
    return OHOS::NWeb::WebPermissionType::GEOLOCATION;
  }
  return OHOS::NWeb::WebPermissionType::NONE_TYPE;
}

bool CefIncognitoDataBaseImpl::ExistPermissionByOrigin(const CefString& origin,
                                                       int type) {
  if (origin.empty()) {
    return false;
  }
  OHOS::NWeb::WebPermissionType key = TypeToWebPermissionType(type);
  if (key == OHOS::NWeb::WebPermissionType::NONE_TYPE) {
    return false;
  }
  if (geolocation_permission_map_.find(origin) ==
      geolocation_permission_map_.end()) {
    return false;
  }
  return true;
}

bool CefIncognitoDataBaseImpl::GetPermissionResultByOrigin(
    const CefString& origin,
    int type,
    bool& result) {
  if (origin.empty()) {
    return false;
  }
  OHOS::NWeb::WebPermissionType key = TypeToWebPermissionType(type);
  if (key == OHOS::NWeb::WebPermissionType::NONE_TYPE) {
    return false;
  }
  std::map<CefString, bool>::iterator it =
      geolocation_permission_map_.find(origin);
  if (it == geolocation_permission_map_.end()) {
    return false;
  }

  result = it->second;
  return true;
}

void CefIncognitoDataBaseImpl::SetPermissionByOrigin(const CefString& origin,
                                                     int type,
                                                     bool result) {
  if (origin.empty()) {
    return;
  }
  OHOS::NWeb::WebPermissionType key = TypeToWebPermissionType(type);
  if (key == OHOS::NWeb::WebPermissionType::NONE_TYPE) {
    return;
  }

  geolocation_permission_map_.emplace(origin, result);
}

void CefIncognitoDataBaseImpl::ClearPermissionByOrigin(const CefString& origin,
                                                       int type) {
  if (origin.empty()) {
    return;
  }
  OHOS::NWeb::WebPermissionType key = TypeToWebPermissionType(type);
  if (key == OHOS::NWeb::WebPermissionType::NONE_TYPE) {
    return;
  }

  std::map<CefString, bool>::iterator it =
      geolocation_permission_map_.find(origin);
  if (it == geolocation_permission_map_.end()) {
    return;
  }

  geolocation_permission_map_.erase(it);
}

void CefIncognitoDataBaseImpl::ClearAllPermission(int type) {
  OHOS::NWeb::WebPermissionType key = TypeToWebPermissionType(type);
  if (key == OHOS::NWeb::WebPermissionType::NONE_TYPE) {
    return;
  }

  geolocation_permission_map_.clear();
}

void CefIncognitoDataBaseImpl::GetOriginsByPermission(
    int type,
    std::vector<CefString>& origins) {
  OHOS::NWeb::WebPermissionType key = TypeToWebPermissionType(type);
  if (key == OHOS::NWeb::WebPermissionType::NONE_TYPE) {
    return;
  }

  origins.clear();
  for (std::map<CefString, bool>::iterator it =
           geolocation_permission_map_.begin();
       it != geolocation_permission_map_.end(); ++it) {
    origins.push_back(it->first);
  }
}
