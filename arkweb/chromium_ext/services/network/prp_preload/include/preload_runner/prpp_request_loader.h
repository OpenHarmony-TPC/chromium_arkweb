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

#ifndef SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PRELOAD_RUNNER_PRPP_REQUEST_LOADER_H
#define SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PRELOAD_RUNNER_PRPP_REQUEST_LOADER_H

#include "net/url_request/url_request.h"

namespace net {
class URLRequestContext;
}  // namespace net

// only run in network thread
namespace ohos_prp_preload {
class PRPPRequestLoader;
class PRRequestInfo;
using ResPreloadedCB = base::OnceCallback<void(PRPPRequestLoader* prpp_loader)>;
using ResetUrlRequestCallback =
  base::OnceCallback<void(const std::shared_ptr<net::URLRequest>& url_request)>;
using UpdateResRequestInfoCallback =
  base::OnceCallback<void(const std::string& key,
    const std::shared_ptr<ohos_prp_preload::PRRequestInfo>& info)>;

constexpr int32_t PRPP_ERROR = -3000; // considering range of NET_ERROR in "net/base/net_error_list.h"
class PRPPRequestLoader {
 public:
  enum PRPPReqLoaderState : uint8_t {
    STATE_IDLE,
    STATE_CONNECTED,
    STATE_REQ_SENT,
    STATE_ERALY_HEAD_RESPONSED,
    STATE_HEAD_RESPONSED,
    STATE_RESPONSE_STARTED,
    STATE_RESPONSED,
    STATE_UNSUPPORT,
    STATE_ERROR,
  };

  // create PRPPRequestLoader
  static std::shared_ptr<PRPPRequestLoader> CreatePRPPRequestLoader(
    const std::string& main_url,
    const std::shared_ptr<PRRequestInfo>& info,
    const net::IsolationInfo& isolation_info,
    base::WeakPtr<net::URLRequestContext> url_request_context,
    ResPreloadedCB res_loaded_cb);

  // destroy the PRPPRequestLoader object
  virtual ~PRPPRequestLoader() = default;

  // init and start preload request
  virtual bool Init(const net::IsolationInfo& isolation_info) = 0;

  // binding the url loader of formal request
  virtual void SetRequestDelegate(net::URLRequest::Delegate* delegate) = 0;

  // start replay recorded message
  virtual bool StartReplay() = 0;

  // set the RequestHeadersCallback of formal request
  virtual void SetRequestHeadersCallback(net::RequestHeadersCallback callback) = 0;
  
  // set the ResponseHeadersCallback of formal request
  virtual void SetResponseHeadersCallback(net::ResponseHeadersCallback callback) = 0;

  // set the EarlyResponseHeadersCallback of formal request
  virtual void SetEarlyResponseHeadersCallback(net::ResponseHeadersCallback callback) = 0;

  // set the ResetUrlRequestCallback. if reinit prpp request, reset it to formal URLLoader
  virtual void SetResetUrlRequestCallback(ResetUrlRequestCallback callback) = 0;

  // set the UpdateResRequestInfoCallback. if reinit prpp request, reset it to formal URLLoader
  virtual void SetUpdateResRequestInfoCallback(UpdateResRequestInfoCallback callback) = 0;

  // read response body to the buffer of formal request
  virtual int Read(net::IOBuffer* buf, int max_bytes) = 0;

  // get preload URLRequest
  virtual std::shared_ptr<net::URLRequest> GetURLRequest() = 0;

  // get PRRequestInfo
  virtual std::shared_ptr<PRRequestInfo> GetPRRequestInfo() = 0;

  // get preload timing info
  virtual void GetLoadTimingInfo(net::LoadTimingInfo* load_timing_info) const = 0;

  // get preload state
  virtual PRPPReqLoaderState GetState() const = 0;

  // clear callback
  virtual void ClearLoaderCallback(bool has_devtools_request_id) = 0;
};

}  // namespace ohos_prp_preload

#endif  // SERVICES_NETWORK_PRP_PRELOAD_INCLUDE_PRELOAD_RUNNER_PRPP_REQUEST_LOADER_H