/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "async_stack.h"
#include <cstdlib>

static CollectAsyncStackFunc g_collectAsyncStackFunc = nullptr;
static SetStackIdFunc g_setStackIdFunc = nullptr;
static uint64_t g_asyncType = 0;

__attribute__((visibility("default"))) void ArkWebSetAsyncStackFunc(
    CollectAsyncStackFunc collectAsyncStackFunc,
    SetStackIdFunc setStackIdFunc) {
  g_collectAsyncStackFunc = collectAsyncStackFunc;
  g_setStackIdFunc = setStackIdFunc;
  g_asyncType = v8::dfx::kArkWebAsyncType;
}
__attribute__((visibility("default"))) void JsvmSetAsyncStackFunc(
    CollectAsyncStackFunc collectAsyncStackFunc,
    SetStackIdFunc setStackIdFunc) {
  g_collectAsyncStackFunc = collectAsyncStackFunc;
  g_setStackIdFunc = setStackIdFunc;
  g_asyncType = v8::dfx::kJsvmAsyncType;
}

namespace v8 {
namespace dfx {

uint64_t CollectAsyncStack(void) {
  auto func = g_collectAsyncStackFunc;
  if (func != nullptr && g_asyncType != 0) {
    return func(g_asyncType);
  }
  return kInvalidStackId;
}

void SetStackId(uint64_t stackId) {
  auto func = g_setStackIdFunc;
  if (func != nullptr) {
    return func(stackId);
  }
}

}  // namespace dfx
}  // namespace v8
