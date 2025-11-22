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

#ifndef MEDIA_CDM_WISEPLAY_CDM_COMMON_H_
#define MEDIA_CDM_WISEPLAY_CDM_COMMON_H_

#include "build/build_config.h"
#include "media/cdm/cdm_type.h"
#include "media/media_buildflags.h"

namespace media {

inline constexpr char kWiseplayKeySystem[] = "com.wiseplay.drm";
inline constexpr char kWiseplayCdmDisplayName[] =
    "Wiseplay Content Decryption Module";
inline constexpr media::CdmType kWiseplayCdmType{0x07e9461ea1caae58ull,
                                                 0xce85e30dd258547aull};

inline const uint8_t kWiseplayUuid[16] = {0x3D, 0x5E, 0x6D, 0x35, 0x9B, 0x9A,
                                          0x41, 0xE8, 0xB8, 0x43, 0xDD, 0x3C,
                                          0x6E, 0x72, 0xC4, 0x2C};
}  // namespace media

#endif  // MEDIA_CDM_WISEPLAY_CDM_COMMON_H_
