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

#include "nweb_image_info_impl.h"

namespace OHOS::NWeb {

NWebImageInfoImpl::NWebImageInfoImpl() {

}

int32_t NWebImageInfoImpl::GetColorType() {
  return color_type_;
}

int32_t NWebImageInfoImpl::GetAlphaType() {
  return alpha_type_;
}

uint32_t* NWebImageInfoImpl::GetData() {
  return data_;
}

uint32_t NWebImageInfoImpl::GetDataSize() {
  return data_size_;
}

int32_t NWebImageInfoImpl::GetWidth() {
  return width_;
}

int32_t NWebImageInfoImpl::GetHeight() {
  return height_;
}

void NWebImageInfoImpl::SetColorType(int32_t color) {
  color_type_ = color;
}

void NWebImageInfoImpl::SetAlphaType(int32_t alpha) {
  alpha_type_ = alpha;
}

void NWebImageInfoImpl::SetData(uint32_t* data) {
  data_ = data;
}

void NWebImageInfoImpl::SetDataSize(uint32_t size) {
  data_size_ = size;
}

void NWebImageInfoImpl::SetWidth(int32_t width) {
  width_ = width;
}

void NWebImageInfoImpl::SetHeight(int32_t height) {
  height_ = height;
}

}  // namespace OHOS::NWeb
