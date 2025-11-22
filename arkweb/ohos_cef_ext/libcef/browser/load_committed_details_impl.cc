// Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "ohos_cef_ext/libcef/browser/load_committed_details_impl.h"

#include "arkweb/chromium_ext/content/public/browser/ohos_navigation_type.h"
#include "url/gurl.h"

CefLoadCommittedDetailsImpl::CefLoadCommittedDetailsImpl(
    const std::string& current_commit_url,
    NavigationType type,
    bool is_main_frame,
    bool is_same_document,
    bool did_replace_entry)
    : current_commit_url_(current_commit_url),
      type_(type),
      is_main_frame_(is_main_frame),
      is_same_document_(is_same_document),
      did_replace_entry_(did_replace_entry) {}

bool CefLoadCommittedDetailsImpl::IsMainFrame() {
  return is_main_frame_;
}

bool CefLoadCommittedDetailsImpl::IsSameDocument() {
  return is_same_document_;
}

bool CefLoadCommittedDetailsImpl::DidReplaceEntry() {
  return did_replace_entry_;
}

CefLoadCommittedDetails::NavigationType
CefLoadCommittedDetailsImpl::GetNavigationType() {
  return type_;
}

CefString CefLoadCommittedDetailsImpl::GetCurrentURL() {
  return current_commit_url_;
}

CefLoadCommittedDetails::NavigationType
CefLoadCommittedDetailsImpl::ConvertToCefLoadCommittedDetailsType(
    const content::LoadCommittedDetails& details) {
  CefLoadCommittedDetails::NavigationType type;
  switch (details.type) {
    case content::OhosNavigationType::OHOS_NAVIGATION_TYPE_UNKNOWN:
      type = CefLoadCommittedDetails::NavigationType::NAVIGATION_TYPE_UNKNOWN;
      break;
    case content::OhosNavigationType::OHOS_NAVIGATION_TYPE_MAIN_FRAME_NEW_ENTRY:
      type = CefLoadCommittedDetails::NavigationType::
          NAVIGATION_TYPE_MAIN_FRAME_NEW_ENTRY;
      break;
    case content::OhosNavigationType::
        OHOS_NAVIGATION_TYPE_MAIN_FRAME_EXISTING_ENTRY:
      type = CefLoadCommittedDetails::NavigationType::
          NAVIGATION_TYPE_MAIN_FRAME_EXISTING_ENTRY;
      break;
    case content::OhosNavigationType::OHOS_NAVIGATION_TYPE_NEW_SUBFRAME:
      type =
          CefLoadCommittedDetails::NavigationType::NAVIGATION_TYPE_NEW_SUBFRAME;
      break;
    case content::OhosNavigationType::OHOS_NAVIGATION_TYPE_AUTO_SUBFRAME:
      type = CefLoadCommittedDetails::NavigationType::
          NAVIGATION_TYPE_AUTO_SUBFRAME;
      break;
    default:
      type = CefLoadCommittedDetails::NavigationType::NAVIGATION_TYPE_UNKNOWN;
      break;
  }
  return type;
}
