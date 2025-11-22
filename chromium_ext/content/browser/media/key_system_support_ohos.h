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

#ifndef CONTENT_BROWSER_MEDIA_KEY_SYSTEM_SUPPORT_OHOS_H_
#define CONTENT_BROWSER_MEDIA_KEY_SYSTEM_SUPPORT_OHOS_H_

#include <string>

#include "content/common/content_export.h"
#include "content/public/common/cdm_info.h"
#include "media/base/cdm_capability.h"

namespace content {

void CONTENT_EXPORT
GetOHOSCdmCapability(const std::string& key_system,
                     CdmInfo::Robustness robustness,
                     media::CdmCapabilityCB cdm_capability_cb);

}  // namespace content

#endif  // CONTENT_BROWSER_MEDIA_KEY_SYSTEM_SUPPORT_OHOS_H_
