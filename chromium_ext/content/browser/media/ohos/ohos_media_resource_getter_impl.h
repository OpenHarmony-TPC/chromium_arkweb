// Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef CONTENT_BROWSER_MEDIA_OHOS_MEDIA_RESOURCE_GETTER_IMPL_H_
#define CONTENT_BROWSER_MEDIA_OHOS_MEDIA_RESOURCE_GETTER_IMPL_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/waitable_event.h"
#include "media/base/ohos/ohos_media_resource_getter.h"
#include "net/base/auth.h"
#include "net/cookies/canonical_cookie.h"
#include "net/cookies/site_for_cookies.h"

namespace content {

class BrowserContext;
class ResourceContext;

// This class implements media::MediaResourceGetter to retrieve resources
// asynchronously on the UI thread.
class OHOSMediaResourceGetterImpl : public media::OHOSMediaResourceGetter {
 public:
  // Construct a MediaResourceGetterImpl object. `browser_context` and
  // `render_process_id` are passed to retrieve the CookieStore.
  OHOSMediaResourceGetterImpl(BrowserContext* browser_context,
                          int render_process_id,
                          int render_frame_id);

  OHOSMediaResourceGetterImpl(const OHOSMediaResourceGetterImpl&) = delete;
  OHOSMediaResourceGetterImpl& operator=(const OHOSMediaResourceGetterImpl&) = delete;

  ~OHOSMediaResourceGetterImpl() override;

  // media::MediaResourceGetter implementation.
  // Must be called on the UI thread.
  void GetAuthCredentials(const GURL& url,
                          GetAuthCredentialsCB callback) override;
  void GetCookies(const GURL& url,
                  const net::SiteForCookies& site_for_cookies,
                  const url::Origin& top_frame_origin,
                  net::StorageAccessApiStatus storage_access_api_status,
                  GetCookieCB callback) override;

 private:
  // Called when GetAuthCredentials() finishes.
  void GetAuthCredentialsCallback(
      GetAuthCredentialsCB callback,
      const std::optional<net::AuthCredentials>& credentials);

  // BrowserContext to retrieve URLRequestContext and ResourceContext.
  raw_ptr<BrowserContext> browser_context_;

  // Render process id, used to check whether the process can access cookies.
  int render_process_id_;

  // Render frame id, used to check tab specific cookie policy.
  int render_frame_id_;

  // NOTE: Weak pointers must be invalidated before all other member variables.
  base::WeakPtrFactory<OHOSMediaResourceGetterImpl> weak_factory_{this};
};

}  // namespace content

#endif  // CONTENT_BROWSER_MEDIA_OHOS_MEDIA_RESOURCE_GETTER_IMPL_H_