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

#ifndef NWEB_ALL_SSL_ERROR_INFO_IMPL_H_
#define NWEB_ALL_SSL_ERROR_INFO_IMPL_H_
#pragma once

#include "nweb_handler.h"

namespace OHOS::NWeb {

class NWebAllSslErrorInfoImpl : public NWebAllSslErrorInfo {
 public:
  NWebAllSslErrorInfoImpl(SslError error, const std::string& url, const std::string& originalUrl,
      const std::string& referrer, bool isFatalError, bool isMainFrame,
      std::vector<std::string>& certChainData) : error_(error),
                                                 url_(url),
                                                 originalUrl_(originalUrl),
                                                 referrer_(referrer),
                                                 isFatalError_(isFatalError),
                                                 isMainFrame_(isMainFrame),
                                                 certChainData_(certChainData) {}

  SslError GetError() override;

  std::string GetUrl() override;

  std::string GetOriginalUrl() override;

  std::string GetReferrer() override;

  bool GetIsFatalError() override;

  bool GetIsMainFrame() override;

  std::vector<std::string> GetCertChainData() override;

 private:
  SslError error_;
  std::string url_;
  std::string originalUrl_;
  std::string referrer_;
  bool isFatalError_ = false;
  bool isMainFrame_ = false;
  std::vector<std::string> certChainData_;
};

} // namespace OHOS::NWeb

#endif // NWEB_ALL_SSL_ERROR_INFO_IMPL_H_
