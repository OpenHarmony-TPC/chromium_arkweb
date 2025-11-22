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

#include "components/permissions/contexts/geolocation_permission_context_ohos.h"

#include "base/functional/callback.h"
#include "base/task/task_traits.h"
#include "base/task/thread_pool.h"
#include "ohos/adapter/permission_manager/permission_manager_adapter.h"

namespace permissions {

GeolocationPermissionContextOHOS::GeolocationPermissionContextOHOS(
    content::BrowserContext* browser_context,
    std::unique_ptr<Delegate> delegate)
    : GeolocationPermissionContext(browser_context, std::move(delegate)) {}

GeolocationPermissionContextOHOS::~GeolocationPermissionContextOHOS() = default;

void GeolocationPermissionContextOHOS::RequestPermission(
    PermissionRequestData request_data,
    BrowserPermissionCallback callback) {
  namespace ohos_permission = ohos::adapter::permission;
  base::ThreadPool::PostTaskAndReplyWithResult(
      FROM_HERE, {base::MayBlock()},
      base::BindOnce(
          &ohos_permission::PermissionManagerAdapter::RequestPermission,
          ohos_permission::OHOSPermissionType::LOCATION),
      base::BindOnce(&GeolocationPermissionContextOHOS::RequestReply,
                     weak_factory_.GetWeakPtr(), std::move(request_data),
                     std::move(callback)));
}

void GeolocationPermissionContextOHOS::RequestReply(
    PermissionRequestData request_data,
    BrowserPermissionCallback callback,
    bool reply_success) {
  if (!reply_success) {
    std::move(callback).Run(CONTENT_SETTING_ASK);
    return;
  }

  GeolocationPermissionContext::RequestPermission(std::move(request_data),
                                                  std::move(callback));
}

}  // namespace permissions
