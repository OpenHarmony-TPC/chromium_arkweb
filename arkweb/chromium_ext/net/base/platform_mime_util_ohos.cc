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

#include "net/base/platform_mime_util.h"

#include <string>

#include "arkweb/chromium_ext/third_party/xdg_shared_mime_info/mime_cache.h"
#include "base/nix/mime_util_xdg.h"
#include "build/build_config.h"
#include "net/base/platform_mime_util.h"

namespace net {

bool PlatformMimeUtil::GetPlatformMimeTypeFromExtension(
    const base::FilePath::StringType& ext,
    std::string* result) const {
  return xdg_shared_mime_info::GetMimeCacheTypeFromExtension(ext, result);
}

bool PlatformMimeUtil::GetPlatformPreferredExtensionForMimeType(
    std::string_view mime_type,
    base::FilePath::StringType* ext) const {
  return false;
}

void PlatformMimeUtil::GetPlatformExtensionsForMimeType(
    std::string_view mime_type,
    std::unordered_set<base::FilePath::StringType>* extensions) const {
}

}  // namespace net
