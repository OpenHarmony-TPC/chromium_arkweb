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

#ifndef CEF_LIBCEF_BROWSER_NET_DNS_DATA_BASE_IMPL_H_
#define CEF_LIBCEF_BROWSER_NET_DNS_DATA_BASE_IMPL_H_

#include "net/base/address_list.h"

void CacheHostName(const std::string& hostname);

net::AddressList GetAddrList(const std::string& hostname);

#endif  // CEF_LIBCEF_BROWSER_NET_DNS_DATA_BASE_IMPL_H_
