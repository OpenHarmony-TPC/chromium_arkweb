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

#include "services/shape_detection/text_detection_impl_ohos.h"

#include <algorithm>
#include <memory>

#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"
#include "ohos/adapter/shape_detection/shape_detection_adapter.h"
#include "services/shape_detection/text_detection_impl.h"
#include "ui/gfx/geometry/rect_f.h"

namespace shape_detection {

// static
void TextDetectionImpl::Create(
    mojo::PendingReceiver<mojom::TextDetection> receiver) {
  mojo::MakeSelfOwnedReceiver(std::make_unique<TextDetectionImplOhos>(),
                              std::move(receiver));
}

void TextDetectionImplOhos::Detect(const SkBitmap& bitmap,
                                   DetectCallback callback) {
  SkImageInfo info = SkImageInfo::Make(bitmap.width(), bitmap.height(),
                                       SkColorType::kRGBA_8888_SkColorType,
                                       bitmap.alphaType());
  auto buffer = std::make_unique<char[]>(bitmap.computeByteSize());
  bitmap.readPixels(info, buffer.get(), bitmap.rowBytes(), 0, 0);
  std::vector<mojom::TextDetectionResultPtr> results;
  std::vector<::ohos::adapter::ShapeDetectionAdapter::TextLine> lineVec =
      ::ohos::adapter::ShapeDetectionAdapter::TextDetect(
          buffer.get(), bitmap.computeByteSize(), bitmap.width(),
          bitmap.height());
  for (const auto& it : lineVec) {
    float x = std::min(it.topLeft.x, it.bottomLeft.x);
    float y = std::min(it.topLeft.y, it.topRight.y);
    float height = std::max(it.bottomRight.y, it.bottomLeft.y) -
                   std::min(it.topLeft.y, it.topRight.y);
    float width = std::max(it.topRight.x, it.bottomRight.x) -
                  std::min(it.bottomLeft.x, it.topLeft.x);
    auto result = mojom::TextDetectionResult::New();
    result->raw_value = it.value;
    result->bounding_box = gfx::RectF(x, y, width, height);
    result->corner_points.emplace_back(it.topLeft.x, it.topLeft.y);
    result->corner_points.emplace_back(it.topRight.x, it.topRight.y);
    result->corner_points.emplace_back(it.bottomRight.x, it.bottomRight.y);
    result->corner_points.emplace_back(it.bottomLeft.x, it.bottomLeft.y);

    results.push_back(std::move(result));
  }
  std::move(callback).Run(std::move(results));
}
}  // namespace shape_detection