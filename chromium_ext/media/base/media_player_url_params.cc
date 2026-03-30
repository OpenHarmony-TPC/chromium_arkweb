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

#include "arkweb/chromium_ext/media/base/media_player_url_params.h"

namespace media {

MediaPlayerUrlParams::MediaPlayerUrlParams() {};

MediaPlayerUrlParams::MediaPlayerUrlParams(const GURL& media_url)
    : media_url_(media_url) {}

MediaPlayerUrlParams::MediaPlayerUrlParams(const MediaPlayerUrlParams& other) =
    default;

MediaPlayerUrlParams::MediaPlayerUrlParams(
    const GURL& media_url,
    const net::SiteForCookies& site_for_cookies,
    const url::Origin& top_frame_origin,
    net::StorageAccessApiStatus storage_access_api_status,
    bool is_hls,
    const base::flat_map<std::string, std::string>& headers,
    uint32_t preload_type,
    uint32_t media_source_type)
    : media_url_(media_url),
      site_for_cookies_(site_for_cookies),
      top_frame_origin_(top_frame_origin),
      storage_access_api_status_(storage_access_api_status),
      is_hls_(is_hls),
      headers_(headers),
      preload_type_(preload_type),
      media_source_type_(media_source_type) {}

MediaPlayerUrlParams::~MediaPlayerUrlParams() {}

}  // namespace media


