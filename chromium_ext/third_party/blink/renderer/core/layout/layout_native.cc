/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "third_party/blink/renderer/core/layout/layout_native.h"

#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/html/html_native_loader.h"
#include "third_party/blink/renderer/core/html/html_plugin_element.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/paint/native_painter.h"
#include "third_party/blink/renderer/platform/web_native_bridge.h"

namespace blink {

LayoutNative::LayoutNative(Element* native) : LayoutImage(native) {
  SetImageResource(MakeGarbageCollected<LayoutImageResource>());
}

LayoutNative::~LayoutNative() = default;

void LayoutNative::Trace(Visitor* visitor) const {
  LayoutImage::Trace(visitor);
}

void LayoutNative::PaintReplaced(const PaintInfo& paint_info,
                                 const PhysicalOffset& paint_offset) const {
  NOT_DESTROYED();
  NativePainter(*this).PaintReplaced(paint_info, paint_offset);
}

HTMLPlugInElement* LayoutNative::PluginElement() const {
  NOT_DESTROYED();
  return To<HTMLPlugInElement>(GetNode());
}

PhysicalNaturalSizingInfo LayoutNative::GetNaturalDimensions() const {
  NOT_DESTROYED();
  if (PluginElement() && PluginElement()->Utils()->CheckIntrinsicSizeEnable()) {
    PhysicalNaturalSizingInfo sizing_info;
    LayoutUnit scaled_width =
        LayoutUnit(static_cast<int>(LayoutReplaced::kDefaultWidth * StyleRef().EffectiveZoom()));
    LayoutUnit scaled_height =
        LayoutUnit(static_cast<int>(LayoutReplaced::kDefaultHeight * StyleRef().EffectiveZoom()));
    sizing_info.size = PhysicalSize(scaled_width, scaled_height);
    sizing_info.has_width = true;
    sizing_info.has_height = true;
    sizing_info.aspect_ratio = PhysicalSize();
    LOG(INFO) << "[NativeEmbed] LayoutNative::GetNaturalDimensions(Enable=true), calculate size: "
              << sizing_info.size.ToString().Utf8();
    return sizing_info;
  }
  return LayoutImage::GetNaturalDimensions();
}

PhysicalRect LayoutNative::ReplacedContentRectFrom(
    const PhysicalRect& base_content_rect) const {
  NOT_DESTROYED();

  PhysicalNaturalSizingInfo sizing_info = GetNaturalDimensions();
  return PreSnappedRectForPersistentSizing(
      ComputeReplacedContentRect(base_content_rect, sizing_info));
}

bool LayoutNative::SupportsAcceleratedRendering() const {
  NOT_DESTROYED();
  if (!PluginElement() || !PluginElement()->NativeLoader()) {
    return false;
  }
  return !!PluginElement()->NativeLoader()->CcLayer();
}

CompositingReasons LayoutNative::AdditionalCompositingReasons() const {
  NOT_DESTROYED();
  return CompositingReason::kVideo;
}

}  // namespace blink
                     