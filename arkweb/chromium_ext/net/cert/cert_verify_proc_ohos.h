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

#ifndef NET_CERT_CERT_VERIFY_PROC_OHOS_H_
#define NET_CERT_CERT_VERIFY_PROC_OHOS_H_

#include "net/base/net_export.h"
#include "net/cert/cert_verify_proc.h"

namespace net {

class CertNetFetcher;

class NET_EXPORT CertVerifyProcOHOS : public CertVerifyProc {
 public:
  explicit CertVerifyProcOHOS(scoped_refptr<CertNetFetcher> net_fetcher);

  CertVerifyProcOHOS(const CertVerifyProcOHOS&) = delete;
  CertVerifyProcOHOS& operator=(const CertVerifyProcOHOS&) = delete;

 protected:
  ~CertVerifyProcOHOS() override;

 private:
  int VerifyInternal(X509Certificate* cert,
                     const std::string& hostname,
                     const std::string& ocsp_response,
                     const std::string& sct_list,
                     int flags,
                     CertVerifyResult* verify_result,
                     const NetLogWithSource& net_log) override;

  scoped_refptr<CertNetFetcher> cert_net_fetcher_;
};

}  // namespace net

#endif  // NET_CERT_CERT_VERIFY_PROC_OHOS_H_
