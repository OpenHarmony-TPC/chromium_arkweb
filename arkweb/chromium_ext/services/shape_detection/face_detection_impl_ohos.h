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

#ifndef SERVICES_SHAPE_DETECTION_FACE_DETECTION_IMPL_OHOS_H_
#define SERVICES_SHAPE_DETECTION_FACE_DETECTION_IMPL_OHOS_H_

#include "services/shape_detection/public/mojom/facedetection.mojom.h"
#include "third_party/skia/include/core/SkBitmap.h"

namespace shape_detection {

class FaceDetectionImplOhos : public shape_detection::mojom::FaceDetection {
 public:
  explicit FaceDetectionImplOhos(
      shape_detection::mojom::FaceDetectorOptionsPtr options);

  FaceDetectionImplOhos(const FaceDetectionImplOhos&) = delete;
  FaceDetectionImplOhos& operator=(const FaceDetectionImplOhos&) = delete;

  ~FaceDetectionImplOhos() override = default;

  void Detect(
      const SkBitmap& bitmap,
      shape_detection::mojom::FaceDetection::DetectCallback callback) override;
};

}  // namespace shape_detection

#endif  // SERVICES_SHAPE_DETECTION_FACE_DETECTION_IMPL_OHOS_H_
