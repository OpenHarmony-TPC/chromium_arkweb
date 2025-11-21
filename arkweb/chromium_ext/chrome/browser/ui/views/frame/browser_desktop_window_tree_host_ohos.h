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

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_OHOS_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_OHOS_H_

#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/views/frame/browser_desktop_window_tree_host.h"
#include "ui/views/widget/desktop_aura/desktop_window_tree_host_ohos.h"  // nogncheck

class BrowserFrame;
class BrowserView;

namespace views {
class DesktopNativeWidgetAura;
}  // namespace views

class BrowserDesktopWindowTreeHostOhos
    : public BrowserDesktopWindowTreeHost,
      public views::DesktopWindowTreeHostOhos {
 public:
  BrowserDesktopWindowTreeHostOhos(
      views::internal::NativeWidgetDelegate* native_widget_delegate,
      views::DesktopNativeWidgetAura* desktop_native_widget_aura,
      BrowserView* browser_view,
      BrowserFrame* browser_frame);

  ~BrowserDesktopWindowTreeHostOhos() override = default;

  BrowserDesktopWindowTreeHostOhos(const BrowserDesktopWindowTreeHostOhos&) =
      delete;
  BrowserDesktopWindowTreeHostOhos& operator=(
      const BrowserDesktopWindowTreeHostOhos&) = delete;

 private:
  DesktopWindowTreeHost* AsDesktopWindowTreeHost() override;
  int GetMinimizeButtonOffset() const override;
  bool UsesNativeSystemMenu() const override;
};

#endif  // CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_DESKTOP_WINDOW_TREE_HOST_OHOS_H_
