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

#include <string>

#include "base/logging.h"
#include "base/notreached.h"
#include "chrome/browser/policy/policy_path_parser.h"

namespace policy {

namespace path_parser {

const char kMachineNamePolicyVarName[] = "${machine_name}";
const char kUserNamePolicyVarName[] = "${user_name}";

base::FilePath::StringType ExpandPathVariables(
    const base::FilePath::StringType& untranslated_string) {
  base::FilePath::StringType result(untranslated_string);
  if (result.length() == 0) {
    return result;
  }

  // Policy paths may be wrapped in quotes, which should be removed.
  constexpr int offset = 2;
  if (result.length() > 1 &&
      ((result.front() == '"' && result.back() == '"') ||
       (result.front() == '\'' && result.back() == '\''))) {
    // Strip first and last char which should be matching quotes now.
    result = result.substr(1, result.length() - offset);
  }

  // Translate two special variables ${user_name} and ${machine_name}
  // TODO(crbug.com/1231482): Integrate with platform provided values, as
  // they become available.
  size_t position = result.find(kUserNamePolicyVarName);
  if (position != std::string::npos) {
    NOTIMPLEMENTED() << "Username variable not implemented.";
    result.replace(position, strlen(kUserNamePolicyVarName), "user");
  }
  position = result.find(kMachineNamePolicyVarName);
  if (position != std::string::npos) {
    NOTIMPLEMENTED() << "Machine name variable not implemented.";
    result.replace(position, strlen(kMachineNamePolicyVarName), "machine");
  }

  return result;
}
}  // namespace path_parser
}  // namespace policy
