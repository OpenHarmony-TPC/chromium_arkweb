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

#include "ui/base/clipboard/clipboard_format_type.h"

#include "base/no_destructor.h"
#include "base/strings/strcat.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "build/build_config.h"
#include "ui/base/clipboard/clipboard_constants.h"

namespace ui {

ClipboardFormatType::ClipboardFormatType() = default;

ClipboardFormatType::~ClipboardFormatType() = default;

ClipboardFormatType::ClipboardFormatType(const std::string& native_format)
    : data_(native_format) {}

std::string ClipboardFormatType::Serialize() const {
  return data_;
}

// static
ClipboardFormatType ClipboardFormatType::Deserialize(
    const std::string& serialization) {
  return ClipboardFormatType(serialization);
}

std::string ClipboardFormatType::GetName() const {
  return Serialize();
}

bool ClipboardFormatType::operator<(const ClipboardFormatType& other) const {
  return data_ < other.data_;
}

bool ClipboardFormatType::operator==(const ClipboardFormatType& other) const {
  return data_ == other.data_;
}

// static
ClipboardFormatType ClipboardFormatType::CustomPlatformType(
    const std::string& format_string) {
  DCHECK(base::IsStringASCII(format_string));
  return ClipboardFormatType::Deserialize(format_string);
}

// static
std::string ClipboardFormatType::WebCustomFormatName(int index) {
  const std::string webcustom_name = "application/web;type=\"custom/format";
  return base::StrCat({webcustom_name, base::NumberToString(index), "\""});
}

// static
const ClipboardFormatType& ClipboardFormatType::WebCustomFormatMap() {
  const std::string webcustom_type =
      "application/web;type=\"custom/formatmap\"";
  static base::NoDestructor<ClipboardFormatType> type(webcustom_type);
  return *type;
}

// Various predefined ClipboardFormatTypes.

// static
ClipboardFormatType ClipboardFormatType::GetType(
    const std::string& format_string) {
  return ClipboardFormatType::Deserialize(format_string);
}

// static
const ClipboardFormatType& ClipboardFormatType::FilenamesType() {
  static base::NoDestructor<ClipboardFormatType> type(kMimeTypeURIList);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::UrlType() {
  static base::NoDestructor<ClipboardFormatType> type(kMimeTypeMozillaURL);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::PlainTextType() {
  static base::NoDestructor<ClipboardFormatType> type(kMimeTypeText);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::HtmlType() {
  static base::NoDestructor<ClipboardFormatType> type(kMimeTypeHTML);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::SvgType() {
  static base::NoDestructor<ClipboardFormatType> type(kMimeTypeSvg);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::RtfType() {
  static base::NoDestructor<ClipboardFormatType> type(kMimeTypeRTF);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::PngType() {
  static base::NoDestructor<ClipboardFormatType> type(kMimeTypePNG);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::BitmapType() {
  return ClipboardFormatType::PngType();
}

// static
const ClipboardFormatType& ClipboardFormatType::WebKitSmartPasteType() {
  static base::NoDestructor<ClipboardFormatType> type(
      kMimeTypeWebkitSmartPaste);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::BookMarkType() {
  const std::string bookmark_type = "chromium/x-bookmark-entries";
  static base::NoDestructor<ClipboardFormatType> type(bookmark_type);
  return *type;
}

// static
const ClipboardFormatType& ClipboardFormatType::DataTransferCustomType() {
  static base::NoDestructor<ClipboardFormatType> type(
      kMimeTypeDataTransferCustomData);
  return *type;
}

}  // namespace ui
