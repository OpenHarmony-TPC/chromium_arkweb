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

#ifndef CEF_INCLUDE_CEF_FORM_HANDLER_H_
#define CEF_INCLUDE_CEF_FORM_HANDLER_H_
#pragma once

#include "include/cef_base.h"
#include "include/cef_browser.h"

///
/// Implement this interface to handle events related to browser form status.
/// The methods of this class will be called on the browser process UI thread or
/// render process main thread (TID_RENDERER).
///
/*--cef(source=client)--*/
class CefFormHandler : public virtual CefBaseRefCounted {
 public:
  ///
  /// Called when the user edited.
  ///
  /*--cef()--*/
  virtual void OnFormEditingStateChanged(CefRefPtr<CefBrowser> browser,
                                         bool is_editing,
                                         uint64_t form_id) {}
};

#endif  // CEF_INCLUDE_CEF_FORM_HANDLER_H_
