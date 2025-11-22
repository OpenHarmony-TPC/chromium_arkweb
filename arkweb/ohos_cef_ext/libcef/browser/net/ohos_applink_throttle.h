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

#ifndef CEF_OHOS_CEF_EXT_LIBCEF_BROWSER_NET_OHOS_APPLINK_THROTTLE_H_
#define CEF_OHOS_CEF_EXT_LIBCEF_BROWSER_NET_OHOS_APPLINK_THROTTLE_H_
#pragma once

#include <memory>
#include <vector>

#include "content/public/browser/frame_tree_node_id.h"
#include "third_party/blink/public/common/loader/url_loader_throttle.h"

namespace throttle {
class OhosAppLinkThrottle : public blink::URLLoaderThrottle {
 public:
  // explicit OhosAppLinkThrottle(content::FrameTreeNodeId frame_tree_node_id);
  OhosAppLinkThrottle(content::FrameTreeNodeId frame_tree_node_id,
                      bool is_client_redirect);
  OhosAppLinkThrottle(const OhosAppLinkThrottle&) = delete;
  OhosAppLinkThrottle& operator=(const OhosAppLinkThrottle&) = delete;
  ~OhosAppLinkThrottle() override;

  // blink::URLLoaderThrottle:
  void WillStartRequest(network::ResourceRequest* request,
                        bool* defer) override;
  void WillRedirectRequest(
      net::RedirectInfo* redirect_info,
      const network::mojom::URLResponseHead& response_head,
      bool* defer,
      std::vector<std::string>* to_be_removed_request_headers,
      net::HttpRequestHeaders* modified_request_headers,
      net::HttpRequestHeaders* modified_cors_exempt_request_headers) override;
  void WillProcessResponse(const GURL& response_url,
                           network::mojom::URLResponseHead* response_head,
                           bool* defer) override;
  void ContinueLoad();
  void CancelLoad();

 private:
  content::FrameTreeNodeId frame_tree_node_id_;
  bool is_client_redirect_ = false;

  SEQUENCE_CHECKER(sequence_checker_);
  base::WeakPtrFactory<OhosAppLinkThrottle> weak_factory_{this};
};

}  // namespace throttle

#endif  // CEF_OHOS_CEF_EXT_LIBCEF_BROWSER_NET_OHOS_APPLINK_THROTTLE_H_
