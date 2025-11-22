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

#include "chrome/browser/ui/views/frame/browser_desktop_window_tree_host_ohos.h"

#include "chrome/browser/ui/views/frame/browser_frame.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/browser/ui/views/frame/desktop_browser_frame_aura_ohos.h"

BrowserDesktopWindowTreeHostOhos::BrowserDesktopWindowTreeHostOhos(
    views::internal::NativeWidgetDelegate* native_widget_delegate,
    views::DesktopNativeWidgetAura* desktop_native_widget_aura,
    BrowserView* browser_view,
    BrowserFrame* browser_frame)
    : views::DesktopWindowTreeHostOhos(native_widget_delegate,
                                       desktop_native_widget_aura) {
  auto* native_frame = static_cast<DesktopBrowserFrameAuraOhos*>(
      browser_frame->native_browser_frame());
  native_frame->set_host(this);
}

views::DesktopWindowTreeHost*
BrowserDesktopWindowTreeHostOhos::AsDesktopWindowTreeHost() {
  return this;
}

int BrowserDesktopWindowTreeHostOhos::GetMinimizeButtonOffset() const {
  return 0;
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
    BrowserFrame* browser_frame) {
  return new BrowserDesktopWindowTreeHostOhos(native_widget_delegate,
                                              desktop_native_widget_aura,
                                              browser_view, browser_frame);
}
