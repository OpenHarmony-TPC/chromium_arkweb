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

#include "arkweb/chromium_ext/media/base/custom_media_url_params.h"

namespace media {

CustomMediaUrlParams::CustomMediaUrlParams()
    : preload_type(0), media_source_type(0) {}

CustomMediaUrlParams::CustomMediaUrlParams(uint32_t preload_type,
                                           uint32_t media_source_type)
    : preload_type(preload_type), media_source_type(media_source_type) {}

CustomMediaUrlParams::CustomMediaUrlParams(const CustomMediaUrlParams& other) =
    default;

CustomMediaUrlParams::~CustomMediaUrlParams() = default;

}  // namespace media
