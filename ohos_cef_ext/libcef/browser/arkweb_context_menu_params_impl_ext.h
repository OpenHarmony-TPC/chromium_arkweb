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

#ifndef CEF_LIBCEF_BROWSER_CONTEXT_MENU_PARAMS_IMPL_EXT_H_
#define CEF_LIBCEF_BROWSER_CONTEXT_MENU_PARAMS_IMPL_EXT_H_
#pragma once

#include "cef/libcef/browser/context_menu_params_impl.h"

class CefContextMenuParamsImpl;
class ArkWebCefContextMenuParamsImplExt : public CefContextMenuParamsImpl {
 public:
  explicit ArkWebCefContextMenuParamsImplExt(content::ContextMenuParams* value);

  ArkWebCefContextMenuParamsImplExt(const ArkWebCefContextMenuParamsImplExt&) =
      delete;
  ArkWebCefContextMenuParamsImplExt& operator=(
      const ArkWebCefContextMenuParamsImplExt&) = delete;
  ArkWebCefContextMenuParamsImplExt* AsArkWebCefContextMenuParamsImplExt()
      override {
    return this;
  }

#if BUILDFLAG(ARKWEB_CLIPBOARD)
  InputFieldType GetInputFieldType() override;
  SourceType GetSourceType() override;
  InputFieldType ConventInputField(blink::mojom::FormControlType formType);
#endif  // #if BUILDFLAG(ARKWEB_CLIPBOARD)

#if BUILDFLAG(ARKWEB_DRAG_DROP)
  void GetImageRect(int& x, int& y, int& w, int& h) override;
  bool IsAILink() override;
#endif
};
#endif  // CEF_LIBCEF_BROWSER_CONTEXT_MENU_PARAMS_IMPL_EXT_H_
