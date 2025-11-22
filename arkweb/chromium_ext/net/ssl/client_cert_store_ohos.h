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

#ifndef NET_SSL_CLIENT_CERT_STORE_OHOS_H_
#define NET_SSL_CLIENT_CERT_STORE_OHOS_H_

#include <map>
#include <string>
#include <vector>

#include "base/functional/callback.h"
#include "net/base/net_export.h"
#include "net/ssl/client_cert_store.h"

namespace net {
class SSLCertRequestInfo;

class NET_EXPORT ClientCertStoreOHOS : public ClientCertStore {
 public:
  using CertificateStore =
      std::map<std::string, std::pair<bssl::UniquePtr<X509>, std::string>>;

  ClientCertStoreOHOS();

  ClientCertStoreOHOS(const ClientCertStoreOHOS&) = delete;
  ClientCertStoreOHOS& operator=(const ClientCertStoreOHOS&) = delete;

  ~ClientCertStoreOHOS() override;

  // ClientCertStore:
  void GetClientCerts(scoped_refptr<const SSLCertRequestInfo> cert_request_info,
                      ClientCertListCallback callback) override;

  // Examines the certificates in |identities| to find all certificates that
  // match the client certificate request in |request|, removing any that don't.
  // The remaining certs will be updated to include intermediates.
  // Must be called from a worker thread.
  static void FilterCertsOnWorkerThread(
      ClientCertIdentityList* identities,
      const SSLCertRequestInfo& request);

  // Retrieves all client certificates that are stored by BoringSSL and adds
  // them to |identities|. |password_delegate| is used to unlock slots if
  // required. If |cert_filter| is not null, only certificates that it returns
  // true on will be added. Must be called from a worker thread.
  static void GetPlatformCertsOnWorkerThread(
      ClientCertIdentityList* identities);

 private:
  ClientCertIdentityList GetAndFilterCertsOnWorkerThread(
      scoped_refptr<const SSLCertRequestInfo> request);

  void OnClientCertsResponse(ClientCertListCallback callback,
                             ClientCertIdentityList identities);

  base::WeakPtrFactory<ClientCertStoreOHOS> weak_factory_{this};
};

}  // namespace net

#endif  // NET_SSL_CLIENT_CERT_STORE_OHOS_H_
