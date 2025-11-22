// Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "libcef/browser/web_client_extension/alloy_native_embed_first_frame_paint_event.h"

#include "content/common/native_embed_first_paint_event.h"

AlloyNativeEmbedFirstFramePaintEvent::AlloyNativeEmbedFirstFramePaintEvent(
    const content::NativeEmbedFirstPaintEvent& event)
    : embed_id_(event.embed_id),
      surface_id_(event.surface_id),
      embed_id_attribute_(event.embed_id_attribute) {}

AlloyNativeEmbedFirstFramePaintEvent::~AlloyNativeEmbedFirstFramePaintEvent() =
    default;

CefString AlloyNativeEmbedFirstFramePaintEvent::GetEmbedId() {
  return embed_id_;
}
CefString AlloyNativeEmbedFirstFramePaintEvent::GetSurfaceId() {
  return surface_id_;
}
CefString AlloyNativeEmbedFirstFramePaintEvent::GetEmbedIdAttribute() {
  return embed_id_attribute_;
}
 