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

#include "cef/ohos_cef_ext/libcef/browser/arkweb_context_menu_params_impl_ext.h"

#include "arkweb/build/features/features.h"
#include "base/logging.h"
#include "third_party/blink/public/mojom/context_menu/context_menu.mojom.h"

ArkWebCefContextMenuParamsImplExt::ArkWebCefContextMenuParamsImplExt(
    content::ContextMenuParams* value)
    : CefContextMenuParamsImpl(value) {}

#if BUILDFLAG(ARKWEB_CLIPBOARD)
ArkWebCefContextMenuParamsImplExt::InputFieldType
ArkWebCefContextMenuParamsImplExt::ConventInputField(
    blink::mojom::FormControlType formType) {
  switch (formType) {
    case blink::mojom::FormControlType::kInputText:
    case blink::mojom::FormControlType::kInputSearch:
    case blink::mojom::FormControlType::kInputEmail:
    case blink::mojom::FormControlType::kInputUrl:
      return CefContextMenuParamsImpl::InputFieldType::
          CM_INPUTFIELDTYPE_PLAINTEXT;
    case blink::mojom::FormControlType::kInputPassword:
      return CefContextMenuParamsImpl::InputFieldType::
          CM_INPUTFIELDTYPE_PASSWORD;
    case blink::mojom::FormControlType::kInputNumber:
      return CefContextMenuParamsImpl::InputFieldType::CM_INPUTFIELDTYPE_NUMBER;
    case blink::mojom::FormControlType::kInputTelephone:
      return CefContextMenuParamsImpl::InputFieldType::
          CM_INPUTFIELDTYPE_TELEPHONE;
    default:
      return CefContextMenuParamsImpl::InputFieldType::CM_INPUTFIELDTYPE_OTHER;
  }
}

ArkWebCefContextMenuParamsImplExt::InputFieldType
ArkWebCefContextMenuParamsImplExt::GetInputFieldType() {
  CEF_VALUE_VERIFY_RETURN(false, CM_INPUTFIELDTYPE_NONE);
  if (!const_value().form_control_type.has_value()) {
    return CM_INPUTFIELDTYPE_NONE;
  }
  return ConventInputField(const_value().form_control_type.value());
}

ArkWebCefContextMenuParamsImplExt::SourceType
ArkWebCefContextMenuParamsImplExt::GetSourceType() {
  CEF_VALUE_VERIFY_RETURN(false, CM_SOURCETYPE_NONE);
  return static_cast<SourceType>(const_value().source_type);
}
#endif  // #if BUILDFLAG(ARKWEB_CLIPBOARD)

#if BUILDFLAG(ARKWEB_DRAG_DROP)
void ArkWebCefContextMenuParamsImplExt::GetImageRect(int& x,
                                                     int& y,
                                                     int& w,
                                                     int& h) {
  x = static_cast<int32_t>(const_value().image_rect.x());
  y = static_cast<int32_t>(const_value().image_rect.y());
  w = static_cast<int32_t>(const_value().image_rect.width());
  h = static_cast<int32_t>(const_value().image_rect.height());
}

bool ArkWebCefContextMenuParamsImplExt::IsAILink() {
  return const_value().is_ai_link;
}
#endif
