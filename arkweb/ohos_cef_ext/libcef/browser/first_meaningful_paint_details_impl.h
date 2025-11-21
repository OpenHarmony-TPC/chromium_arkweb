// Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef CEF_LIBCEF_BROWSER_FIRST_MEANINGFUL_PAINT_DETAILS_IMPL_H_
#define CEF_LIBCEF_BROWSER_FIRST_MEANINGFUL_PAINT_DETAILS_IMPL_H_
#pragma once

#include "include/cef_first_meaningful_paint_details.h"
#include "libcef/common/value_base.h"

// CefFirstMeaningfulPaintDetails implementation
class CefFirstMeaningfulPaintDetailsImpl
    : public CefFirstMeaningfulPaintDetails {
 public:
  explicit CefFirstMeaningfulPaintDetailsImpl(int64_t navigationStartTime,
                                              int64_t firstMeaningfulPaintTime);

  CefFirstMeaningfulPaintDetailsImpl(
      const CefFirstMeaningfulPaintDetailsImpl&) = delete;
  CefFirstMeaningfulPaintDetailsImpl& operator=(
      const CefFirstMeaningfulPaintDetailsImpl&) = delete;

  // CefFirstMeaningfulPaintDetailsImpl methods.
  int64_t GetNavigationStartTime() override;
  int64_t GetFirstMeaningfulPaintTime() override;

 private:
  int64_t navigationStartTime_;
  int64_t firstMeaningfulPaintTime_;

  IMPLEMENT_REFCOUNTING(CefFirstMeaningfulPaintDetailsImpl);
};

#endif  // CEF_LIBCEF_BROWSER_FIRST_MEANINGFUL_PAINT_DETAILS_IMPL_H_
