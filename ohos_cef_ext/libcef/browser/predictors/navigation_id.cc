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

#include "ohos_cef_ext/libcef/browser/predictors/navigation_id.h"

#include <string>
#include <tuple>

#include "components/prefs/pref_service.h"
#include "components/sessions/content/session_tab_helper.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/web_contents.h"
#include "ohos_cef_ext/libcef/browser/predictors/loading_predictor_config.h"

namespace ohos_predictors {

NavigationID::NavigationID() : tab_id(SessionID::InvalidValue()) {}

NavigationID::NavigationID(const NavigationID& other)
    : tab_id(other.tab_id),
      main_frame_url(other.main_frame_url),
      creation_time(other.creation_time) {}

NavigationID::NavigationID(content::WebContents* web_contents)
    : tab_id(sessions::SessionTabHelper::IdForTab(web_contents)),
      main_frame_url(web_contents->GetLastCommittedURL()),
      creation_time(base::TimeTicks::Now()) {}

NavigationID::NavigationID(content::WebContents* web_contents,
                           const GURL& main_frame_url,
                           const base::TimeTicks& creation_time)
    : tab_id(sessions::SessionTabHelper::IdForTab(web_contents)),
      main_frame_url(main_frame_url),
      creation_time(creation_time) {}

bool NavigationID::is_valid() const {
  return tab_id.is_valid() && !main_frame_url.is_empty();
}

bool NavigationID::operator<(const NavigationID& rhs) const {
  DCHECK(is_valid() && rhs.is_valid());
  return std::tie(tab_id, main_frame_url) <
         std::tie(rhs.tab_id, rhs.main_frame_url);
}

bool NavigationID::operator==(const NavigationID& rhs) const {
  DCHECK(is_valid() && rhs.is_valid());
  return tab_id == rhs.tab_id && main_frame_url == rhs.main_frame_url;
}

}  // namespace ohos_predictors
