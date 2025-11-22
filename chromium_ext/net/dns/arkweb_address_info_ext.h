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

#ifndef NET_DNS_ARKWEB_ADDRESS_INFO_EXT_H_
#define NET_DNS_ARKWEB_ADDRESS_INFO_EXT_H_

#include <memory>
#include <optional>
#include <string>
#include <tuple>

#include "base/memory/raw_ptr.h"
#include "build/build_config.h"
#include "net/base/address_family.h"
#include "net/base/net_export.h"
#include "net/base/network_handle.h"
#include "net/base/sys_addrinfo.h"

namespace net {

#if BUILDFLAG(ARKWEB_EXT_NETWORK_CONNECTION)
using OHGetAddrInfoForNetwork = int32_t (*)(char* host,
                                            char* serv,
                                            struct addrinfo* hints,
                                            struct addrinfo** res,
                                            int32_t net_id);

using OHFreeDnsResult = int32_t (*)(struct addrinfo* res);

#if BUILDFLAG(ARKWEB_TEST)
#ifdef __cplusplus
extern "C" {
#endif
OHGetAddrInfoForNetwork GetOHGetAddrInfoForNetwork();

OHFreeDnsResult GetOHFreeDnsResult();
#ifdef __cplusplus
}
#endif
#else
OHGetAddrInfoForNetwork GetOHGetAddrInfoForNetwork();

OHFreeDnsResult GetOHFreeDnsResult();
#endif //ARKWEB_TEST

namespace ohos {

int GetAddrInfoForNetwork(char* host,
                          char* serv,
                          struct addrinfo* hints,
                          struct addrinfo** res,
                          int32_t network);

NO_SANITIZE("cfi-icall") int FreeDnsResult(struct addrinfo* res);

}  // namespace ohos

#endif  // ARKWEB_EXT_NETWORK_CONNECTION

}  // namespace net

#endif  // NET_DNS_ARKWEB_ADDRESS_INFO_EXT_H_
