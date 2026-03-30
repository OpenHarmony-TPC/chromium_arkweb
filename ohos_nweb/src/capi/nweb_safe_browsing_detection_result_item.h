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
 
#ifndef OHOS_NWEB_SAFE_BROWSING_DETECTION_RESULT_ITEM_H_
#define OHOS_NWEB_SAFE_BROWSING_DETECTION_RESULT_ITEM_H_
 
#include <string>
 
struct SafeBrowsingDetectionResult {
  int req_id{-1};
  int code{-1};
  int policy{-1};
  std::string mappingType;
  std::string desensitizedUrl;
  bool isContentCheck{false};
  std::string accessUrl;
  std::string contentCheckParameters;
  std::string uuid;
  std::string appname;
 
  SafeBrowsingDetectionResult(
      int code,
      int policy,
      const std::string& mappingType,
      const std::string& desensitizedUrl,
      bool isContentCheck,
      const std::string& accessUrl,
      const std::string& contentCheckParams
  ) : 
      req_id(-1),
      code(code),
      policy(policy),
      mappingType(mappingType),          
      desensitizedUrl(desensitizedUrl),
      isContentCheck(isContentCheck),
      accessUrl(accessUrl),
      contentCheckParameters(contentCheckParams),
      uuid(""), 
      appname("")
  {};
  SafeBrowsingDetectionResult() : mappingType(""), desensitizedUrl(""), accessUrl(""), 
    contentCheckParameters(""), uuid(""), appname(""){}
};
 
#endif  // OHOS_NWEB_SAFE_BROWSING_DETECTION_RESULT_ITEM_H_