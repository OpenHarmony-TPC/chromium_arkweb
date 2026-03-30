// Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/frame/browser_desktop_window_tree_host_ohos.h"

#include "chrome/browser/ui/views/frame/browser_widget.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/browser/ui/views/frame/browser_native_widget_aura_ohos.h"

BrowserDesktopWindowTreeHostOhos::BrowserDesktopWindowTreeHostOhos(
    views::internal::NativeWidgetDelegate* native_widget_delegate,
    views::DesktopNativeWidgetAura* desktop_native_widget_aura,
    BrowserView* browser_view,
    BrowserWidget* browser_widget)
    : views::DesktopWindowTreeHostOhos(native_widget_delegate,
                                       desktop_native_widget_aura) {
  auto* native_widget = static_cast<BrowserNativeWidgetAuraOhos*>(
      browser_widget->browser_native_widget());
  native_widget->set_host(this);
}

views::DesktopWindowTreeHost*
BrowserDesktopWindowTreeHostOhos::AsDesktopWindowTreeHost() {
  return this;
}

bool BrowserDesktopWindowTreeHostOhos::UsesNativeSystemMenu() const {
  return false;
}

// static
BrowserDesktopWindowTreeHost*
BrowserDesktopWindowTreeHost::CreateBrowserDesktopWindowTreeHost(
    views::internal::NativeWidgetDelegate* native_widget_delegate,
    views::DesktopNativeWidgetAura* desktop_native_widget_aura,
    BrowserView* browser_view,
    BrowserWidget* browser_widget) {
  return new BrowserDesktopWindowTreeHostOhos(native_widget_delegate,
                                              desktop_native_widget_aura,
                                              browser_view, browser_widget);
}
