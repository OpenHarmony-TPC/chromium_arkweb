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

#ifndef CEF_LIBCEF_BROWSER_DOWNLOAD_ITEM_IMPL_EXT_H_
#define CEF_LIBCEF_BROWSER_DOWNLOAD_ITEM_IMPL_EXT_H_
#pragma once

#include "arkweb/build/features/features.h"
#include "cef/libcef/browser/download_item_impl.h"
#include "cef/libcef/common/value_base.h"
#include "cef/ohos_cef_ext/include/cef_download_item_ext.h"

// CefDownloadItem implementation
class CefDownloadItemImplExt : public CefDownloadItemExt,
                               public CefDownloadItemImpl {
 public:
  explicit CefDownloadItemImplExt(download::DownloadItem* value);
  explicit CefDownloadItemImplExt(download::DownloadItem* value, int nweb_id);
  CefString GetOriginalMimeType() override;
  CefString GetGuid() override;

  // additional methods
  int GetState() override;
  bool IsPaused() override;
  CefString GetMethod() override;
  int GetLastErrorCode() override;
  bool IsPending() override;
  CefString GetLastModifiedTime() override;
  CefString GetETag() override;
  CefString GetReceivedSlices() override;
  int GetNWebId() override;
  CefRefPtr<CefDownloadItemExt> AsArkDownloadItem() override;
  CefRefPtr<CefValue> GetOriginContentDisposition() override;
};

#endif  // CEF_LIBCEF_BROWSER_DOWNLOAD_ITEM_IMPL_H_
