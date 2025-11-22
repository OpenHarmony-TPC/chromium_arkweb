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

#ifndef CEF_LIBCEF_BROWSER_PREDICTORS_NAVIGATION_ID_H_
#define CEF_LIBCEF_BROWSER_PREDICTORS_NAVIGATION_ID_H_

#include <stddef.h>

#include "base/time/time.h"
#include "components/sessions/core/session_id.h"
#include "url/gurl.h"

namespace content {
class WebContents;
}

namespace ohos_predictors {

// Represents a single navigation for a render frame.
struct NavigationID {
  NavigationID();
  explicit NavigationID(content::WebContents* web_contents);
  NavigationID(content::WebContents* web_contents,
               const GURL& main_frame_url,
               const base::TimeTicks& creation_time);
  NavigationID(const NavigationID& other);

  bool operator<(const NavigationID& rhs) const;
  bool operator==(const NavigationID& rhs) const;

  // Returns true iff the tab_id is valid and the Main frame URL is set.
  bool is_valid() const;

  SessionID tab_id;
  GURL main_frame_url;

  // NOTE: Even though we store the creation time here, it is not used during
  // comparison of two NavigationIDs because it cannot always be determined
  // correctly.
  base::TimeTicks creation_time;
};

}  // namespace ohos_predictors

#endif  // CEF_LIBCEF_BROWSER_PREDICTORS_NAVIGATION_ID_H_
