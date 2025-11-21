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

#ifndef BASE_BASE_PATHS_OHOS_H_
#define BASE_BASE_PATHS_OHOS_H_

#include "arkweb/build/features/features.h"
#include "build/build_config.h"

namespace base {

enum {
  PATH_OHOS_START = 500,

  DIR_OHOS_APP_DATA,
  DIR_OHOS_EXTERNAL_STORAGE,
  DIR_OHOS_APP_INSTALLATION,
#if BUILDFLAG(IS_ARKWEB) && BUILDFLAG(ARKWEB_CRASHPAD)
  DIR_OHOS_CRASHPAD,
#endif
  PATH_OHOS_END
};

}  // namespace base

#endif  // BASE_BASE_PATHS_OHOS_H_
