// Copyright (c) 2022 Huawei Device Co., Ltd.
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

// Defines base::PathProviderOHOS which replaces base::PathProviderPosix for
// OHOS in base/path_service.cc.
#include "base/base_paths_ohos.h"

#include <limits.h>
#include <unistd.h>

#include "base/base_paths.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/notreached.h"
#include "base/process/process_metrics.h"

namespace base {
// TODO: temporary solution to load resources for multiple processes
bool ParseAssetsOHOS(FilePath* result) {
  if (!base::CommandLine::ForCurrentProcess()) {
    LOG(ERROR) << "CommandLine not init";
    return false;
  }
  auto bundle_path = base::CommandLine::ForCurrentProcess()->
    GetSwitchValueASCII(switches::kBundleInstallationDir);
  if (bundle_path.empty()) {
    FilePath bin_dir;
    if (!ReadSymbolicLink(FilePath(kProcSelfExe), &bin_dir)) {
      LOG(ERROR) << "Unable to resolve " << kProcSelfExe << ".";
      return false;
    }
    *result = bin_dir.DirName();
    return true;
  }
  bool for_test = base::CommandLine::ForCurrentProcess()->HasSwitch(switches::kForTest);
  if (for_test) {
    *result = FilePath(bundle_path + "/entry/resources/rawfile");
  } else {
    *result = FilePath(bundle_path + "/nweb/entry/resources/rawfile");
  }
  return true;
}

bool PathProviderOHOS(int key, FilePath* result) {
  FilePath bin_dir;
  switch (key) {
    case base::FILE_EXE: {
      if (!ReadSymbolicLink(FilePath(kProcSelfExe), &bin_dir)) {
        NOTREACHED() << "Unable to resolve " << kProcSelfExe << ".";
      }
      *result = bin_dir;
      return true;
    }
    case base::FILE_MODULE:
      NOTIMPLEMENTED();
      return false;
    case base::DIR_MODULE: {
      if (!ReadSymbolicLink(FilePath(kProcSelfExe), &bin_dir)) {
        NOTREACHED() << "Unable to resolve " << kProcSelfExe << ".";
      }
      *result = bin_dir.DirName();
      return true;
    }
    case base::DIR_SOURCE_ROOT:
      if (!ReadSymbolicLink(FilePath(kProcSelfExe), &bin_dir)) {
        NOTREACHED() << "Unable to resolve " << kProcSelfExe << ".";
      }
      *result = bin_dir.DirName();
      return true;
    case base::DIR_USER_DESKTOP:
      NOTIMPLEMENTED();
      return false;
    case base::DIR_CACHE:
    #if BUILDFLAG(IS_ARKWEB) && BUILDFLAG(ARKWEB_COOKIE)
      *result = FilePath("/data/storage/el2/base/cache/web");
    #else
      // set to /data/local directory for W|X permission.
      *result = FilePath("/data/local");
    #endif // #ifdef ARKWEB_COOKIE
      return true;
    case base::DIR_ASSETS:
      // resource file packed to system images
      return ParseAssetsOHOS(result);
    case base::DIR_OHOS_APP_DATA:
      *result = FilePath("/data/local");
      return true;
    case base::DIR_OHOS_EXTERNAL_STORAGE:
      return false;
    default:
      return false;
  }
}

}  // namespace base
