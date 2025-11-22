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

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_WINDOW_TREE_HOST_OHOS_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_WINDOW_TREE_HOST_OHOS_H_

#include "ui/views/views_export.h"
#include "ui/views/widget/desktop_aura/desktop_window_tree_host_platform.h"

namespace views {

class WindowEventFilterOhos;

class VIEWS_EXPORT DesktopWindowTreeHostOhos
    : public DesktopWindowTreeHostPlatform {
 public:
  DesktopWindowTreeHostOhos(
      internal::NativeWidgetDelegate* native_widget_delegate,
      DesktopNativeWidgetAura* desktop_native_widget_aura);

  DesktopWindowTreeHostOhos(const DesktopWindowTreeHostOhos&) = delete;
  DesktopWindowTreeHostOhos& operator=(const DesktopWindowTreeHostOhos&) =
      delete;

  ~DesktopWindowTreeHostOhos() override;

 protected:
  // Overridden from DesktopWindowTreeHost:
  void OnNativeWidgetCreated(const Widget::InitParams& params) override;
  // PlatformWindowDelegate:
  void DispatchEvent(ui::Event* event) override;
  void OnClosed() override;

  // DesktopWindowTreeHostPlatform:
  void AddAdditionalInitProperties(
      const Widget::InitParams& params,
      ui::PlatformWindowInitProperties* properties) override;

 private:
  void CreateNonClientEventFilter();
  void DestroyNonClientEventFilter();

  // A handler for events intended for non client area.
  // A posthandler for events intended for non client area. Handles events if no
  // other consumer handled them.
  std::unique_ptr<WindowEventFilterOhos> non_client_window_event_filter_;
};

}  // namespace views

#endif  // UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_WINDOW_TREE_HOST_OHOS_H_