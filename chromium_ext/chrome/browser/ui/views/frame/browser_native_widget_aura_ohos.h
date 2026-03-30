// Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_DESKTOP_BROWSER_FRAME_AURA_OHOS_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_DESKTOP_BROWSER_FRAME_AURA_OHOS_H_

#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/views/frame/browser_native_widget_aura.h"

class BrowserDesktopWindowTreeHostOhos;

// Provides the window frame for the Chrome browser window on Desktop ohos.
class BrowserNativeWidgetAuraOhos : public BrowserNativeWidgetAura {
 public:
  BrowserNativeWidgetAuraOhos(BrowserWidget* browser_widget,
                              BrowserView* browser_view);

  BrowserNativeWidgetAuraOhos(const BrowserNativeWidgetAuraOhos&) = delete;
  BrowserNativeWidgetAuraOhos& operator=(const BrowserNativeWidgetAuraOhos&) =
      delete;

  void set_host(BrowserDesktopWindowTreeHostOhos* host) { host_ = host; }

 protected:
  ~BrowserNativeWidgetAuraOhos() override;

  views::Widget::InitParams GetWidgetParams(
      views::Widget::InitParams::Ownership ownership) override;
  bool UseCustomFrame() const override;

 private:
  void OnWidgetInitialized();

  raw_ptr<BrowserDesktopWindowTreeHostOhos> host_ = nullptr;
};

#endif  // CHROME_BROWSER_UI_VIEWS_FRAME_DESKTOP_BROWSER_FRAME_AURA_OHOS_H_
