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

#ifndef CEF_LIBCEF_BROWSER_OSR_TOUCH_HANDLE_DRAWABLE_OSR_EXT_H_
#define CEF_LIBCEF_BROWSER_OSR_TOUCH_HANDLE_DRAWABLE_OSR_EXT_H_

#include "cef/libcef/browser/osr/touch_handle_drawable_osr.h"

class CefTouchHandleDrawableOSR;
class ArkWebCefTouchHandleDrawableOSRExt : public CefTouchHandleDrawableOSR {
 public:
  explicit ArkWebCefTouchHandleDrawableOSRExt(CefRenderWidgetHostViewOSR* rwhv);
  ArkWebCefTouchHandleDrawableOSRExt* AsArkWebCefTouchHandleDrawableOSRExt()
      override {
    return this;
  }
  void SetOrigin(const gfx::PointF& position) override;
  void SetAlpha(float alpha) override;
  gfx::RectF GetVisibleBounds() const override;

#if BUILDFLAG(ARKWEB_MENU)
  void SetEdge(const gfx::PointF& top, const gfx::PointF& bottom) override;
  void UpdateVisiableBounds();
#endif  // BUILDFLAG(ARKWEB_MENU)

#if BUILDFLAG(ARKWEB_MENU)
  // Handle line height
  float edge_height_ = 0.f;
#endif  // BUILDFLAG(ARKWEB_MENU)
};
#endif  // CEF_LIBCEF_BROWSER_OSR_TOUCH_HANDLE_DRAWABLE_OSR_EXT_H_
