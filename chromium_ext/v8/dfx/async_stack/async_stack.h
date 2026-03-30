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
#ifndef V8_DFX_ASYNC_STACK_H
#define V8_DFX_ASYNC_STACK_H
#include <cstdint>

typedef uint64_t (*CollectAsyncStackFunc)(uint64_t type);
typedef void (*SetStackIdFunc)(uint64_t stackId);
extern "C" void ArkWebSetAsyncStackFunc(
    CollectAsyncStackFunc collectAsyncStackFunc,
    SetStackIdFunc setStackIdFunc);
extern "C" void JsvmSetAsyncStackFunc(
    CollectAsyncStackFunc collectAsyncStackFunc,
    SetStackIdFunc setStackIdFunc);
namespace v8 {
namespace dfx {

inline constexpr uint64_t kInvalidStackId = 0;

inline constexpr uint64_t kArkWebAsyncType = 1ULL << 18;
inline constexpr uint64_t kJsvmAsyncType = 1ULL << 19;

uint64_t CollectAsyncStack(void);
void SetStackId(uint64_t stackId);

}  // namespace dfx
}  // namespace v8

#endif
