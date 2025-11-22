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

// Based on shared_image_video_provider.cc originally written by
// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. 

#include "media/gpu/ohos/shared_image_video_provider.h"

namespace media {

SharedImageVideoProvider::ImageSpec::ImageSpec() = default;
SharedImageVideoProvider::ImageSpec::ImageSpec(const gfx::Size& our_size,
                                               uint64_t our_generation_id)
    : coded_size(our_size), generation_id(our_generation_id) {}
SharedImageVideoProvider::ImageSpec::ImageSpec(const ImageSpec&) = default;
SharedImageVideoProvider::ImageSpec::~ImageSpec() = default;

bool SharedImageVideoProvider::ImageSpec::operator==(
    const ImageSpec& rhs) const {
  return coded_size == rhs.coded_size && generation_id == rhs.generation_id &&
         color_space == rhs.color_space;
}

bool SharedImageVideoProvider::ImageSpec::operator!=(
    const ImageSpec& rhs) const {
  return !(*this == rhs);
}

SharedImageVideoProvider::ImageRecord::ImageRecord() = default;
SharedImageVideoProvider::ImageRecord::ImageRecord(ImageRecord&&) = default;
SharedImageVideoProvider::ImageRecord::~ImageRecord() = default;

}  // namespace media
                     