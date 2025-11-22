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

#ifndef ARKWEB_CONTENT_RENDERER_CLIENT_CEF_EXT_
#define ARKWEB_CONTENT_RENDERER_CLIENT_CEF_EXT_

#include <memory>

#include "arkweb/build/features/features.h"
#include "base/memory/scoped_refptr.h"
#include "base/task/single_thread_task_runner.h"
#include "chrome/renderer/chrome_content_renderer_client.h"
#include "cef/libcef/renderer/chrome/chrome_content_renderer_client_cef.h"

class CefRenderManager;

// ArkWeb override of ChromeContentRendererClientCef.
class ArkWebContentRendererClientCefExt
    : public ChromeContentRendererClientCef {
 public:
  ArkWebContentRendererClientCefExt();

  ArkWebContentRendererClientCefExt(const ArkWebContentRendererClientCefExt&) =
      delete;
  ArkWebContentRendererClientCefExt& operator=(
      const ArkWebContentRendererClientCefExt&) = delete;

  ~ArkWebContentRendererClientCefExt() override;

  ArkWebContentRendererClientCefExt* AsArkWebContentRendererClientCef()
      override {
    return this;
  }

#if BUILDFLAG(ARKWEB_NO_STATE_PREFETCH)
  void NoStatePrefetchRenderFrame(content::RenderFrame* render_frame);
#endif  // ARKWEB_NO_STATE_PREFETCH

#if BUILDFLAG(ARKWEB_NO_STATE_PREFETCH)
  std::unique_ptr<blink::WebPrescientNetworking> CreatePrescientNetworking(
      content::RenderFrame* render_frame) override;
  bool IsPrefetchOnly(content::RenderFrame* render_frame) override;
#endif  // ARKWEB_NO_STATE_PREFETCH

#if BUILDFLAG(ARKWEB_NETWORK_LOAD)
  bool HandleNavigation(content::RenderFrame* render_frame,
                        blink::WebFrame* frame,
                        const blink::WebURLRequest& request,
                        blink::WebNavigationType type,
                        blink::WebNavigationPolicy default_policy,
                        bool is_redirect) override;
#endif

#if BUILDFLAG(ARKWEB_SAFEBROWSING) && !BUILDFLAG(ARKWEB_NWEB_EX)
  void PrepareErrorPage(content::RenderFrame* render_frame,
                        const blink::WebURLError& error,
                        const std::string& http_method,
                        content::mojom::AlternativeErrorPageOverrideInfoPtr
                            alternative_error_page_info,
                        std::string* error_html) override;
#endif
#if BUILDFLAG(ARKWEB_JS_ON_DOCUMENT_END)
  void RunScriptsAtDocumentStart(content::RenderFrame* render_frame) override;
  void RunScriptsAtDocumentEnd(content::RenderFrame* render_frame) override;
#endif
#if BUILDFLAG(ARKWEB_JSPROXY)
  void RunScriptsAtHeadReady(content::RenderFrame* render_frame) override;
#endif
};

#endif  // ARKWEB_CONTENT_RENDERER_CLIENT_CEF_EXT_
