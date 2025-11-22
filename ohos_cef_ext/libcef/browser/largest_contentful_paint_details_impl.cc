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

#include "libcef/browser/largest_contentful_paint_details_impl.h"

CefLargestContentfulPaintDetailsImpl::CefLargestContentfulPaintDetailsImpl(
    int64_t navigationStartTime,
    int64_t largestImagePaintTime,
    int64_t largestTextPaintTime,
    int64_t largestImageLoadStartTime,
    int64_t largestImageLoadEndTime,
    double_t imageBPP)
    : navigationStartTime_(navigationStartTime),
      largestImagePaintTime_(largestImagePaintTime),
      largestTextPaintTime_(largestTextPaintTime),
      largestImageLoadStartTime_(largestImageLoadStartTime),
      largestImageLoadEndTime_(largestImageLoadEndTime),
      imageBPP_(imageBPP) {}

int64_t CefLargestContentfulPaintDetailsImpl::GetNavigationStartTime() {
  return navigationStartTime_;
}

int64_t CefLargestContentfulPaintDetailsImpl::GetLargestImagePaintTime() {
  return largestImagePaintTime_;
}

int64_t CefLargestContentfulPaintDetailsImpl::GetLargestTextPaintTime() {
  return largestTextPaintTime_;
}

int64_t CefLargestContentfulPaintDetailsImpl::GetLargestImageLoadStartTime() {
  return largestImageLoadStartTime_;
}

int64_t CefLargestContentfulPaintDetailsImpl::GetLargestImageLoadEndTime() {
  return largestImageLoadEndTime_;
}

double_t CefLargestContentfulPaintDetailsImpl::GetImageBPP() {
  return imageBPP_;
}
 