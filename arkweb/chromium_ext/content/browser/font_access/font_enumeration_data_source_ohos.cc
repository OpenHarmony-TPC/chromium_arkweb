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

#include "content/browser/font_access/font_enumeration_data_source_ohos.h"

#include "base/notreached.h"
#include "base/sequence_checker.h"
#include "base/threading/scoped_blocking_call.h"
#include "ohos/adapter/font/font_adapter.h"
#include "third_party/blink/public/common/font_access/font_enumeration_table.pb.h"

namespace content {
namespace {

std::vector<std::string> GetSystemFonts() {
  base::ScopedBlockingCall scoped_blocking_call(FROM_HERE,
                                                base::BlockingType::MAY_BLOCK);
  return ohos::adapter::font::FontAdapter::GetInstance().GetSystemFontList();
}

ohos::adapter::font::OhosFontInfo GetFontInformation(const std::string& name) {
  base::ScopedBlockingCall scoped_blocking_call(FROM_HERE,
                                                base::BlockingType::MAY_BLOCK);
  return ohos::adapter::font::FontAdapter::GetInstance().GetFontInfo(name);
}
}  // namespace

FontEnumerationDataSourceOHOS::FontEnumerationDataSourceOHOS() {
  DETACH_FROM_SEQUENCE(sequence_checker_);
}

FontEnumerationDataSourceOHOS::~FontEnumerationDataSourceOHOS() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
}

blink::FontEnumerationTable FontEnumerationDataSourceOHOS::GetFonts(
    const std::string& locale) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  blink::FontEnumerationTable font_enumeration_table;

  std::vector<std::string> fonts = GetSystemFonts();
  for (const auto& font : fonts) {
    ohos::adapter::font::OhosFontInfo font_info = GetFontInformation(font);
    blink::FontEnumerationTable_FontData* data =
        font_enumeration_table.add_fonts();
    if (!data) {
      continue;
    }
    data->set_postscript_name(font_info.post_script_name);
    data->set_full_name(font);
    data->set_family(font_info.family);
    data->set_style(font_info.subfamily);
  }

  return font_enumeration_table;
}

}  // namespace content
