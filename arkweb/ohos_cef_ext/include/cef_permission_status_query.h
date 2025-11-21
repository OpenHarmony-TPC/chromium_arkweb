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
 
#ifndef CEF_INCLUDE_CEF_PERMISSION_STATUS_QUERY_H_
#define CEF_INCLUDE_CEF_PERMISSION_STATUS_QUERY_H_
#pragma once
 
#include "include/cef_base.h"
#include "include/internal/cef_types.h"
 
///
/// Class used to query permission status.
///
/*--cef(source=library)--*/
class CefAccessQuery : public virtual CefBaseRefCounted {
 public:
  ///
  /// Get the origin that is trying to acess the resource.
  ///
  /*--cef()--*/
  virtual CefString Origin() = 0;
  ///
  /// Get the resource that the origin is trying to acess.
  ///
  /*--cef()--*/
  virtual int ResourceAcessId() = 0;
  ///
  /// Report the permission status of resource.
  ///
  /*--cef()--*/
  virtual void ReportQueryResult(int32_t status) = 0;
};
 
///
/// Implement this interface to handle permission status query.
///
/*--cef(source=library)--*/
class CefPermissionQuery : public virtual CefBaseRefCounted {
 public:
  ///
  /// Get permission status.
  ///
  static void GetPermissionStatusAsync(CefRefPtr<CefAccessQuery>);

#if BUILDFLAG(ARKWEB_CLIPBOARD)
  ///
  /// Is clipboard site permission enabled.
  ///
  static bool IsClipboardSitePermissionEnabled();
#endif  // BUILDFLAG(ARKWEB_CLIPBOARD)
};
 
 
#endif // CEF_INCLUDE_CEF_PERMISSION_STATUS_QUERY_H_