// Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef CEF_OHOS_CEF_EXT_LIBCEF_BROWSER_ALLOY_ALLOY_BROWSER_HOST_IMPL_UTILS_H_
#define CEF_OHOS_CEF_EXT_LIBCEF_BROWSER_ALLOY_ALLOY_BROWSER_HOST_IMPL_UTILS_H_
#pragma once

#include "base/memory/raw_ptr.h"
#include "cef/libcef/browser/alloy/alloy_browser_host_impl.h"
#include "content/public/browser/web_contents.h"

class AlloyBrowserHostImplUtils
{
public:
    raw_ptr<AlloyBrowserHostImpl> alloyBrowserHostImpl;
    AlloyBrowserHostImplUtils(AlloyBrowserHostImpl* impl) { alloyBrowserHostImpl = impl; }
    ~AlloyBrowserHostImplUtils() = default;

#if BUILDFLAG(ARKWEB_CLIPBOARD)
  void UpdateZoomSupportEnabled();
#endif

#if BUILDFLAG(ARKWEB_REPORT_RENDER_STATE)
  base::ProcessId GetRenderProcessId();
#endif

#if BUILDFLAG(ARKWEB_VIDEO_LTPO)
  void manageVSyncFrequencyOnTouchEvent(const CefTouchEvent& event);
#endif

#if BUILDFLAG(ARKWEB_EXT_GET_ZOOM_LEVEL)
  void commitPendingZoomLevelPreferences();
#endif

#if BUILDFLAG(ARKWEB_INPUT_EVENTS)
  int handleZoomEventWithInput(bool zoom_in);
#endif

#if BUILDFLAG(ARKWEB_EXT_GET_ZOOM_LEVEL)
  void enableZoomLevelController(content::WebContents* web_contents);
#endif

#if BUILDFLAG(ARKWEB_WEBRTC) && BUILDFLAG(ARKWEB_PERMISSION)
  int conditionalHandleMediaStreamPermissionRequest(
    content::MediaResponseCallback callback,
    const content::MediaStreamRequest& request);
#endif // BUILDFLAG(ARKWEB_WEBRTC) && BUILDFLAG(ARKWEB_PERMISSION)

#if BUILDFLAG(ARKWEB_INPUT_EVENTS)
  bool handleAndReDispatchKeyboardEvent(content::WebContents* source, const input::NativeWebKeyboardEvent& event);
#endif

#if BUILDFLAG(ARKWEB_RENDERER_ANR_DUMP)
  int handleRendererUnresponsive(content::WebContents* source, content::RendererIsUnresponsiveReason reason);
#endif

#if BUILDFLAG(ARKWEB_IMMEDIATE_DESTORY)
  void handleSingleRenderDelayShutdown(content::WebContents* source);
#endif

};


#endif  // CEF_OHOS_CEF_EXT_LIBCEF_BROWSER_ALLOY_ALLOY_BROWSER_HOST_IMPL_UTILS_H_
