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

#ifndef MEDIA_BASE_CUSTOM_MEDIA_URL_PARAMS_H_
#define MEDIA_BASE_CUSTOM_MEDIA_URL_PARAMS_H_

#include <cstdint>

#include "media/base/media_export.h"

namespace media {

struct MEDIA_EXPORT CustomMediaUrlParams {
  CustomMediaUrlParams();
  CustomMediaUrlParams(uint32_t preload_type, uint32_t media_source_type);
  CustomMediaUrlParams(const CustomMediaUrlParams& other);
  ~CustomMediaUrlParams();

  uint32_t preload_type;
  uint32_t media_source_type;
};

}  // namespace media

#endif  // MEDIA_BASE_CUSTOM_MEDIA_URL_PARAMS_H_
