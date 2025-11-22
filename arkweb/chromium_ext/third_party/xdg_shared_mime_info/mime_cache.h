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

// Based on mime_cache.h originally written by
// Copyright (c) 2022 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_XDG_SHARED_MIME_INFO_MIME_CACHE_H_
#define THIRD_PARTY_XDG_SHARED_MIME_INFO_MIME_CACHE_H_

#include <string>

namespace xdg_shared_mime_info {

// Gets the mime type (if any) that is associated with the file extension.
// Returns true if a corresponding mime type exists.
bool GetMimeCacheTypeFromExtension(const std::string& ext, std::string* result);

}  // namespace xdg_shared_mime_info

#endif  // THIRD_PARTY_XDG_SHARED_MIME_INFO_MIME_CACHE_H_
