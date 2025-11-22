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

#ifndef MEDIA_BASE_OHOS_MEDIA_RESOURCE_GETTER_H_
#define MEDIA_BASE_OHOS_MEDIA_RESOURCE_GETTER_H_

#include <stdint.h>

#include <string>

#include "base/functional/callback.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "url/gurl.h"
#include "net/storage_access_api/status.h"

namespace net {
class SiteForCookies;
}  // namespace net

namespace url {
class Origin;
}  // namespace url

namespace media {

// Class for asynchronously retrieving resources for a media URL. All callbacks
// are executed on the caller's thread.
class MEDIA_EXPORT OHOSMediaResourceGetter {
 public:
  // Callback to get the cookies. Args: cookies string.
  typedef base::OnceCallback<void(const std::string&)> GetCookieCB;

  // Callback to get the auth credentials. Args: username and password.
  typedef base::OnceCallback<void(const std::u16string&, const std::u16string&)>
      GetAuthCredentialsCB;

  // Callback to get the media metadata. Args: duration, width, height, and
  // whether the information is retrieved successfully.
  typedef base::OnceCallback<void(base::TimeDelta, int, int, bool)>
      ExtractMediaMetadataCB;
  virtual ~OHOSMediaResourceGetter();

  // Method for getting the auth credentials for a URL.
  virtual void GetAuthCredentials(const GURL& url,
                                  GetAuthCredentialsCB callback) = 0;

  // Method for getting the cookies for a given URL.
  virtual void GetCookies(const GURL& url,
                          const net::SiteForCookies& site_for_cookies,
                          const url::Origin& top_frame_origin,
                          net::StorageAccessApiStatus storage_access_api_status,
                          GetCookieCB callback) = 0;
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_MEDIA_RESOURCE_GETTER_H_