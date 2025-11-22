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

#include <memory>

#include "base/base_paths.h"
#include "base/files/file_util.h"
#include "base/path_service.h"
#include "base/strings/string_util.h"
#include "build/branding_buildflags.h"
#include "build/build_config.h"
#include "build/chromeos_buildflags.h"
#include "chrome/common/channel_info.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/common/chrome_paths_internal.h"

namespace chrome {

bool GetDefaultUserDataDirectory(base::FilePath* result) {
  base::FilePath config_dir;
  base::PathService::Get(base::DIR_OHOS_APP_DATA, &config_dir);
#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
  std::string data_dir_basename = "google-chrome";
#else
  std::string data_dir_basename = "chromium";
#endif
  *result = config_dir.Append(data_dir_basename);
  return true;
}

void GetUserCacheDirectory(const base::FilePath& profile_dir,
                           base::FilePath* result) {
  *result = profile_dir;
  base::FilePath cache_dir;
  if (!base::PathService::Get(base::DIR_CACHE, &cache_dir)) {
    return;
  }

  cache_dir = cache_dir.Append(profile_dir.BaseName());
  *result = cache_dir;
}

bool GetUserDocumentsDirectory(base::FilePath* result) {
  return false;
}

bool GetUserDownloadsDirectory(base::FilePath* result) {
  return false;
}

// ohos does not support music directory
bool GetUserMusicDirectory(base::FilePath* result) {
  NOTIMPLEMENTED();
  return false;
}

// ohos does not support picture directory
bool GetUserPicturesDirectory(base::FilePath* result) {
  NOTIMPLEMENTED();
  return false;
}

// ohos does not support video directory
bool GetUserVideosDirectory(base::FilePath* result) {
  NOTIMPLEMENTED();
  return false;
}

bool ProcessNeedsProfileDir(const std::string& process_type) {
  // For now we have no reason to forbid this on Linux as we don't
  // have the roaming profile troubles there. Moreover the Linux breakpad needs
  // profile dir access in all process if enabled on Linux.
  return true;
}

}  // namespace chrome
