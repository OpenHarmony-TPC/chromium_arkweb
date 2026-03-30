/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or wrapperied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "nweb_all_ssl_error_info_impl.h"

namespace OHOS::NWeb {

SslError NWebAllSslErrorInfoImpl::GetError() {
    return error_;
}

std::string NWebAllSslErrorInfoImpl::GetUrl() {
    return url_;
}

std::string NWebAllSslErrorInfoImpl::GetOriginalUrl() {
    return originalUrl_;
}

std::string NWebAllSslErrorInfoImpl::GetReferrer() {
    return referrer_;
}

bool NWebAllSslErrorInfoImpl::GetIsFatalError() {
    return isFatalError_;
}

bool NWebAllSslErrorInfoImpl::GetIsMainFrame() {
    return isMainFrame_;
}

std::vector<std::string> NWebAllSslErrorInfoImpl::GetCertChainData() {
    return certChainData_;
}

} // namespace OHOS::NWeb
