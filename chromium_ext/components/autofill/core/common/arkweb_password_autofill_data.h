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

// Based on ohos_password_autofill_data.h originally written by
// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_COMMON_OHOS_PASSWORD_AUTOFILL_DATA_H_
#define COMPONENTS_AUTOFILL_CORE_COMMON_OHOS_PASSWORD_AUTOFILL_DATA_H_

#include <string>

#include "build/build_config.h"
#include "components/autofill/core/common/unique_ids.h"
#include "ui/gfx/geometry/rect_f.h"

namespace autofill {

namespace mojom {
enum class OhosInputElementType;
}

// Structure used for sending information from browser to renderer about on
// which fields password should be generated.
struct InputFillRequestData {
  FieldRendererId field_renderer_id;
  bool is_focused;
  mojom::OhosInputElementType type;
  gfx::RectF bounds;
  std::u16string value;
  std::u16string placeholder;
  std::string autocomplete_attr;
};

}  // namespace autofill

#endif  // COMPONENTS_AUTOFILL_CORE_COMMON_OHOS_PASSWORD_AUTOFILL_DATA_H_