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
//
// This file defines utility functions for eliding URLs.

#ifndef COMPONENTS_URL_FORMATTER_ARKWEB_ELIDE_URL_EXT_H_
#define COMPONENTS_URL_FORMATTER_ARKWEB_ELIDE_URL_EXT_H_

#include <string>

#include "build/build_config.h"

#if BUILDFLAG(IS_ARKWEB_EXT)
#include "url/third_party/mozilla/url_parse.h"
#endif

class GURL;

namespace url_formatter {

#if BUILDFLAG(IS_ARKWEB_EXT)
/**
 * Parse the character string entered by the user and return the type of the
 * character string.
 * @param String the input to parse
 * @return  INVALID 0 invalid type
 *          URL     1 URL type
 *          QUERY   2 QUERY type
 *          UNKNOWN 3 UNKNOW type
 */
enum UrlType { INVALID = 0, URL = 1, QUERY = 2, UNKNOWN = 3 };

UrlType ParseInput(const std::u16string& input,
                   url::Parsed* parts,
                   std::u16string* scheme,
                   GURL* canonicalized_url);

#if BUILDFLAG(ARKWEB_TEST)
int TestNumNonHostComponents(const url::Parsed& parts);

UrlType TestGetInputTypeForScheme(const std::string& scheme);
#endif  // BUILDFLAG(ARKWEB_TEST)

#endif  // BUILDFLAG(IS_ARKWEB_EXT)

}  // namespace url_formatter

#endif  // COMPONENTS_URL_FORMATTER_ARKWEB_ELIDE_URL_EXT_H_
