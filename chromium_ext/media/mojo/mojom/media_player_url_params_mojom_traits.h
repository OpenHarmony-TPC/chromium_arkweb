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
 
#ifndef MEDIA_MOJO_MOJOM_CUSTOM_MEDIA_URL_PARAMS_MOJOM_TRAITS_H_
#define MEDIA_MOJO_MOJOM_CUSTOM_MEDIA_URL_PARAMS_MOJOM_TRAITS_H_

#include "arkweb/chromium_ext/media/base/media_player_url_params.h"
#include "arkweb/chromium_ext/media/mojo/mojom/media_player_url_params.mojom.h"
#include "mojo/public/cpp/bindings/struct_traits.h"

namespace mojo {

template <>
struct StructTraits<media::mojom::MediaPlayerUrlParamsDataView,
                     media::MediaPlayerUrlParams> {
  static const GURL& media_url(
      const media::MediaPlayerUrlParams& params) {
    return params.media_url_;
  }

  static const net::SiteForCookies& site_for_cookies(
      const media::MediaPlayerUrlParams& params) {
    return params.site_for_cookies_;
  }

  static const url::Origin& top_frame_origin(
      const media::MediaPlayerUrlParams& params) {
    return params.top_frame_origin_;
  }

  static int32_t storage_access_api_status(
      const media::MediaPlayerUrlParams& params) {
    return static_cast<int32_t>(params.storage_access_api_status_);
  }

  static bool is_hls(const media::MediaPlayerUrlParams& params) {
    return params.is_hls_;
  }

  static const base::flat_map<std::string, std::string>& headers(
      const media::MediaPlayerUrlParams& params) {
    return params.headers_;
  }

  static uint32_t preload_type(
      const media::MediaPlayerUrlParams& params) {
    return params.preload_type_;
  }

  static uint32_t media_source_type(
      const media::MediaPlayerUrlParams& params) {
    return params.media_source_type_;
  }

  static bool Read(media::mojom::MediaPlayerUrlParamsDataView data,
                   media::MediaPlayerUrlParams* out_params);
};

}  // namespace mojo

#endif  // MEDIA_MOJO_MOJOM_CUSTOM_MEDIA_URL_PARAMS_MOJOM_TRAITS_H_