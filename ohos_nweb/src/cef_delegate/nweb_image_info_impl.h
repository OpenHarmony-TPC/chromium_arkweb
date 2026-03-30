/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NWEB_IMAGE_INFO_IMPL_H
#define NWEB_IMAGE_INFO_IMPL_H

#include "nweb_handler.h"

namespace OHOS::NWeb {

class NWebImageInfoImpl : public NWebImageInfo {
 public:
  NWebImageInfoImpl();
  ~NWebImageInfoImpl() = default;

  int32_t GetWidth() override;

  int32_t GetHeight() override;

  int32_t GetColorType() override;

  int32_t GetAlphaType() override;
  
  uint32_t *GetData() override;

  uint32_t GetDataSize() override;

  void SetWidth(int32_t width) override;

  void SetHeight(int32_t height) override;

  void SetAlphaType(int32_t alphaType) override;

  void SetColorType(int32_t colorType) override;

  void SetData(uint32_t *data) override;

  void SetDataSize(uint32_t dataSize) override;

 private:
  int32_t color_type_ = -1;
  int32_t alpha_type_ = -1;
  uint32_t* data_ = nullptr;
  uint32_t data_size_ = 0;
  int32_t width_ = 0;
  int32_t height_ = 0;
};

}  // namespace OHOS::NWeb

#endif  // NWEB_IMAGE_INFO_IMPL_H
