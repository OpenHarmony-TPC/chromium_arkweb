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

#ifndef COMPONENTS_PERMISSIONS_CONTEXTS_GEOLOCATION_PERMISSION_CONTEXT_OHOS_H_
#define COMPONENTS_PERMISSIONS_CONTEXTS_GEOLOCATION_PERMISSION_CONTEXT_OHOS_H_

#include "base/memory/weak_ptr.h"
#include "components/permissions/contexts/geolocation_permission_context.h"
#include "components/permissions/permission_request_id.h"

namespace permissions {

class GeolocationPermissionContextOHOS : public GeolocationPermissionContext {
 public:
  GeolocationPermissionContextOHOS(content::BrowserContext* browser_context,
                                   std::unique_ptr<Delegate> delegate);

  GeolocationPermissionContextOHOS(const GeolocationPermissionContextOHOS&) =
      delete;
  GeolocationPermissionContextOHOS& operator=(
      const GeolocationPermissionContextOHOS&) = delete;

  ~GeolocationPermissionContextOHOS() override;

 private:
  void RequestPermission(PermissionRequestData request_data,
                         BrowserPermissionCallback callback) override;

  void RequestReply(PermissionRequestData request_data,
                    BrowserPermissionCallback callback,
                    bool reply_success);
  base::WeakPtrFactory<GeolocationPermissionContextOHOS> weak_factory_{this};
};

}  // namespace permissions

#endif  // COMPONENTS_PERMISSIONS_CONTEXTS_GEOLOCATION_PERMISSION_CONTEXT_OHOS_H_
