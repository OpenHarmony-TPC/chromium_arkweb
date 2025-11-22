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

#ifndef SERVICES_SHAPE_DETECTION_TEXT_DETECTION_IMPL_OHOS_H_
#define SERVICES_SHAPE_DETECTION_TEXT_DETECTION_IMPL_OHOS_H_

#include "services/shape_detection/public/mojom/textdetection.mojom.h"

namespace shape_detection {

class TextDetectionImplOhos : public mojom::TextDetection {
 public:
  TextDetectionImplOhos() = default;

  TextDetectionImplOhos(const TextDetectionImplOhos&) = delete;
  TextDetectionImplOhos& operator=(const TextDetectionImplOhos&) = delete;

  ~TextDetectionImplOhos() override = default;

  void Detect(const SkBitmap& bitmap,
              mojom::TextDetection::DetectCallback callback) override;
};

}  // namespace shape_detection

#endif  // SERVICES_SHAPE_DETECTION_TEXT_DETECTION_IMPL_OHOS_H_
