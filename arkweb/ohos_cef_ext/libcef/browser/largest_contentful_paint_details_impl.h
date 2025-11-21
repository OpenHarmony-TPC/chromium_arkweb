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

#ifndef CEF_LIBCEF_BROWSER_LARGEST_CONTENTFUL_PAINT_DETAILS_IMPL_H_
#define CEF_LIBCEF_BROWSER_LARGEST_CONTENTFUL_PAINT_DETAILS_IMPL_H_
#pragma once

#include "include/cef_largest_contentful_paint_details.h"
#include "libcef/common/value_base.h"

// CefLargestContentfulPaintDetails implementation
class CefLargestContentfulPaintDetailsImpl
    : public CefLargestContentfulPaintDetails {
 public:
  explicit CefLargestContentfulPaintDetailsImpl(
      int64_t navigationStartTime,
      int64_t largestImagePaintTime,
      int64_t largestTextPaintTime,
      int64_t largestImageLoadStartTime,
      int64_t largestImageLoadEndTime,
      double_t imageBPP);

  CefLargestContentfulPaintDetailsImpl(
      const CefLargestContentfulPaintDetailsImpl&) = delete;
  CefLargestContentfulPaintDetailsImpl& operator=(
      const CefLargestContentfulPaintDetailsImpl&) = delete;

  // CefLargestContentfulPaintDetailsImpl methods.
  int64_t GetNavigationStartTime() override;
  int64_t GetLargestImagePaintTime() override;
  int64_t GetLargestTextPaintTime() override;
  int64_t GetLargestImageLoadStartTime() override;
  int64_t GetLargestImageLoadEndTime() override;
  double_t GetImageBPP() override;

 private:
  int64_t navigationStartTime_;
  int64_t largestImagePaintTime_;
  int64_t largestTextPaintTime_;
  int64_t largestImageLoadStartTime_;
  int64_t largestImageLoadEndTime_;
  double_t imageBPP_;

  IMPLEMENT_REFCOUNTING(CefLargestContentfulPaintDetailsImpl);
};

#endif  // CEF_LIBCEF_BROWSER_LARGEST_CONTENTFUL_PAINT_DETAILS_IMPL_H_
