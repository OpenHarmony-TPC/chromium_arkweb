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

#ifndef CONTENT_BROWSER_FONT_ACCESS_FONT_ENUMERATION_DATA_SOURCE_OHOS_H_
#define CONTENT_BROWSER_FONT_ACCESS_FONT_ENUMERATION_DATA_SOURCE_OHOS_H_

#include <string>

#include "base/sequence_checker.h"
#include "content/browser/font_access/font_enumeration_data_source.h"
#include "third_party/blink/public/common/font_access/font_enumeration_table.pb.h"

namespace content {

// OHOS implementation of FontEnumerationDataSource.
class FontEnumerationDataSourceOHOS : public FontEnumerationDataSource {
 public:
  FontEnumerationDataSourceOHOS();

  FontEnumerationDataSourceOHOS(const FontEnumerationDataSourceOHOS&) =
      delete;
  FontEnumerationDataSourceOHOS& operator=(
      const FontEnumerationDataSourceOHOS&) = delete;
  ~FontEnumerationDataSourceOHOS() override;
  blink::FontEnumerationTable GetFonts(const std::string& locale) override;

 private:
  SEQUENCE_CHECKER(sequence_checker_);
};

}  // namespace content

#endif  // CONTENT_BROWSER_FONT_ACCESS_FONT_ENUMERATION_DATA_SOURCE_OHOS_H_
