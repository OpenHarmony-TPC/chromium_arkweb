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

#ifndef MEDIA_BASE_CUSTOM_MEDIA_PLAYER_URL_PARAMS_H_
#define MEDIA_BASE_CUSTOM_MEDIA_PLAYER_URL_PARAMS_H_

#include <map>
#include <string>

#include "base/containers/flat_map.h"
#include "base/logging.h"
#include "net/cookies/site_for_cookies.h"
#include "net/storage_access_api/status.h"
#include "url/gurl.h"
#include "url/origin.h"

namespace media {

// OHOS custom media URL parameters.
// This class contains all fields that were previously in MediaUrlParams,
// which was deleted in Chromium 144. It is used to pass media URL information
// to the OHOS custom media player.
class MediaPlayerUrlParams {
 public:
  MediaPlayerUrlParams();
  explicit MediaPlayerUrlParams(const GURL& media_url);
  MediaPlayerUrlParams(const MediaPlayerUrlParams& other);

  // Full parameter constructor
  MediaPlayerUrlParams(
      const GURL& media_url,
      const net::SiteForCookies& site_for_cookies,
      const url::Origin& top_frame_origin,
      net::StorageAccessApiStatus storage_access_api_status,
      bool is_hls,
      const base::flat_map<std::string, std::string>& headers,
      uint32_t preload_type,
      uint32_t media_source_type);

  ~MediaPlayerUrlParams();

  // Media URL (the video/audio resource URL)
  const GURL& MediaUrl() const { return media_url_; }
  void SetMediaUrl(const GURL& url) { media_url_ = url; }

  // Site-for-cookies for the media request
  const net::SiteForCookies& SiteForCookies() const {
    return site_for_cookies_;
  }
  void SetSiteForCookies(const net::SiteForCookies& value) {
    site_for_cookies_ = value;
  }

  // Top-frame origin for the media request
  const url::Origin& TopFrameOrigin() const { return top_frame_origin_; }
  void SetTopFrameOrigin(const url::Origin& origin) {
    top_frame_origin_ = origin;
  }

  // Storage Access API status
  net::StorageAccessApiStatus GetStorageAccessApiStatus() const {
    return storage_access_api_status_;
  }
  void SetStorageAccessApiStatus(net::StorageAccessApiStatus status) {
    storage_access_api_status_ = status;
  }

  // Whether this is an HLS stream
  bool IsHls() const { return is_hls_; }
  void SetIsHls(bool is_hls) { is_hls_ = is_hls; }

  // HTTP headers (Cookie, Referer, User-Agent, etc.)
  const base::flat_map<std::string, std::string>& Headers() const {
    return headers_;
  }
  void SetHeaders(const base::flat_map<std::string, std::string>& headers) {
    headers_ = headers;
  }
  void AddHeader(const std::string key, const std::string value) {
    headers_.insert_or_assign(key, value);
  }

  // OHOS-specific custom media URL params
  // Preload type: 0=none, 1=metadata, 2=auto
  uint32_t PreloadType() const { return preload_type_; }
  void SetPreloadType(uint32_t type) { preload_type_ = type; }

  // Media source type: 0=URL, 1=MSE (Media Source Extensions)
  uint32_t MediaSourceType() const { return media_source_type_; }
  void SetMediaSourceType(uint32_t type) { media_source_type_ = type; }

  // Check if the URL is valid
  bool IsValid() const { return media_url_.is_valid() && !media_url_.is_empty(); }

 public:
  GURL media_url_;
  net::SiteForCookies site_for_cookies_;
  url::Origin top_frame_origin_;
  net::StorageAccessApiStatus storage_access_api_status_;
  bool is_hls_ = false;
  base::flat_map<std::string, std::string> headers_;

  // OHOS-specific fields
  uint32_t preload_type_ = 0;      // Default: none
  uint32_t media_source_type_ = 0;  // Default: URL
};

}  // namespace media

#endif  // MEDIA_BASE_CUSTOM_MEDIA_PLAYER_URL_PARAMS_H_
