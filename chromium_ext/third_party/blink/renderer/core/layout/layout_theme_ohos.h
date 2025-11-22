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

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_LAYOUT_LAYOUT_THEME_OHOS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_LAYOUT_LAYOUT_THEME_OHOS_H_

#include "third_party/blink/renderer/core/layout/layout_theme_mobile.h"

namespace blink {

class LayoutThemeOhos final : public LayoutThemeMobile {
 public:
  static scoped_refptr<LayoutTheme> Create();

  String ExtraDefaultStyleSheet() override;
  bool DelegatesMenuListRendering() const override { return false; }
  Color PlatformActiveSelectionBackgroundColor(
      mojom::blink::ColorScheme color_scheme) const override;
  Color PlatformActiveSelectionForegroundColor(
      mojom::blink::ColorScheme color_scheme) const override;
  void AdjustInnerSpinButtonStyle(ComputedStyleBuilder&) const override;
  bool SupportsSelectionForegroundColors() const override { return false; }
  Color PlatformTapHighlightColor() const override;

 private:
  ~LayoutThemeOhos() override;
  static constexpr Color kDefaultActiveSelectionBackgroundColor =
      Color::FromRGBA32(0x330a59f7);
  static constexpr Color kDefaultDrakSchemeActiveSelectionBackgroundColor =
      Color::FromRGBA32(0x66317af7);
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_LAYOUT_LAYOUT_THEME_OHOS_H_
