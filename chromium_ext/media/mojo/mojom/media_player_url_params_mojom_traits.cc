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
 
#include "arkweb/chromium_ext/media/mojo/mojom/media_player_url_params_mojom_traits.h"

#include "url/origin.h"
#include "net/storage_access_api/status.h"

namespace mojo {

bool StructTraits<media::mojom::MediaPlayerUrlParamsDataView,
                  media::MediaPlayerUrlParams>::
    Read(media::mojom::MediaPlayerUrlParamsDataView data,
         media::MediaPlayerUrlParams* out_params) {
  if (!data.ReadMediaUrl(&out_params->media_url_))
    return false;
  if (!data.ReadSiteForCookies(&out_params->site_for_cookies_))
    return false;
  if (!data.ReadTopFrameOrigin(&out_params->top_frame_origin_))
    return false;

  out_params->storage_access_api_status_ = 
    static_cast<net::StorageAccessApiStatus>(data.storage_access_api_status());
  out_params->is_hls_ = data.is_hls();
  if (!data.ReadHeaders(&out_params->headers_))
    return false;

  out_params->preload_type_ = data.preload_type();
  out_params->media_source_type_ = data.media_source_type();

  return true;
}

}  // namespace mojo