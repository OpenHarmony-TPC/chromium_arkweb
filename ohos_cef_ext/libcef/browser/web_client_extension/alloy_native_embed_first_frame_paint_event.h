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

#ifndef CEF_LIBCEF_BROWSER_WEB_CLIENT_EXTENSION_ALLOY_NATIVE_EMBED_FIRST_FRAME_PAINT_EVENT_H_
#define CEF_LIBCEF_BROWSER_WEB_CLIENT_EXTENSION_ALLOY_NATIVE_EMBED_FIRST_FRAME_PAINT_EVENT_H_

#include <string>

#include "include/cef_native_embed_first_frame_paint_event.h"

namespace content {
struct NativeEmbedFirstPaintEvent;
}

class AlloyNativeEmbedFirstFramePaintEvent
    : public CefNativeEmbedFirstFramePaintEvent {
 public:
  AlloyNativeEmbedFirstFramePaintEvent(
      const content::NativeEmbedFirstPaintEvent& event);
  AlloyNativeEmbedFirstFramePaintEvent(
      const AlloyNativeEmbedFirstFramePaintEvent&) = delete;
  AlloyNativeEmbedFirstFramePaintEvent& operator=(
      const AlloyNativeEmbedFirstFramePaintEvent&) = delete;
  virtual ~AlloyNativeEmbedFirstFramePaintEvent();

  CefString GetEmbedId() override;
  CefString GetSurfaceId() override;
  CefString GetEmbedIdAttribute() override;

 private:
  CefString embed_id_;
  CefString surface_id_;
  CefString embed_id_attribute_;

  IMPLEMENT_REFCOUNTING(AlloyNativeEmbedFirstFramePaintEvent);
};

#endif  // CEF_LIBCEF_BROWSER_WEB_CLIENT_EXTENSION_ALLOY_NATIVE_EMBED_FIRST_FRAME_PAINT_EVENT_H_
