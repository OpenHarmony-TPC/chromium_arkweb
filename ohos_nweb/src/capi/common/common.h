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

#ifndef OHOS_NWEB_SRC_CAPI_COMMON_COMMON_H_
#define OHOS_NWEB_SRC_CAPI_COMMON_COMMON_H_

template <class T, typename MethodPointer>
bool CheckValid(T* obj, MethodPointer* pointer) {
  if (!obj || !pointer) {
    return false;
  }
  typename T::Base* base = static_cast<typename T::Base*>(obj);
  uintptr_t start_pos = reinterpret_cast<intptr_t>(base);
  uintptr_t method_pos = reinterpret_cast<intptr_t>(pointer);
  if (start_pos + obj->struct_size < method_pos + sizeof(MethodPointer)) {
    return false;
  }
  if (!(*pointer)) {
    return false;
  }
  return true;
}

#endif // OHOS_NWEB_SRC_CAPI_COMMON_COMMON_H_