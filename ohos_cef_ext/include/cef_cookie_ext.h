// Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_CEF_EXT_INCLUDE_CEF_COOKIE_EXT_H_
#define OHOS_CEF_EXT_INCLUDE_CEF_COOKIE_EXT_H_

///
/// Extended from CefCookieManager
///
class CefCookieManagerExt : virtual public CefCookieManager {
 public:
  ///
  /// Get whether this cookie manager can accpet and send cookies. Returns false
  /// if can't.
  /// IS_OHOS extended
  ///
  /*--cef()--*/
  virtual bool IsAcceptCookieAllowed() = 0;

  ///
  /// Set whether this cookie manager can accpet and send cookies.
  /// IS_OHOS extended
  ///
  /*--cef()--*/
  virtual void PutAcceptCookieEnabled(bool accept) = 0;

  ///
  /// Gets whether cookies of third parties are allowed to be set. Returns false
  /// if can't.
  /// IS_OHOS extended
  ///
  /*--cef()--*/
  virtual bool IsThirdPartyCookieAllowed() = 0;

  ///
  /// Set whether cookies of third parties are allowed to be set.
  /// IS_OHOS extended
  ///
  /*--cef()--*/
  virtual void PutAcceptThirdPartyCookieEnabled(bool accept) = 0;

  ///
  /// Get whether this cookie manager can accpet and send cookies for file
  /// scheme URL. Returns false if can't.
  /// IS_OHOS extended
  ///
  /*--cef()--*/
  virtual bool IsFileURLSchemeCookiesAllowed() = 0;

  ///
  /// Set whether this cookie manager can accpet and send cookies for file
  /// scheme URL.
  /// IS_OHOS extended
  ///
  /*--cef()--*/
  virtual void PutAcceptFileURLSchemeCookiesEnabled(bool allow) = 0;

  static CefRefPtr<CefCookieManagerExt> GetGlobalManager(
      CefRefPtr<CefCompletionCallback> callback);

  static CefRefPtr<CefCookieManagerExt> GetGlobalIncognitoManager(
      CefRefPtr<CefCompletionCallback> callback);
};

#endif
