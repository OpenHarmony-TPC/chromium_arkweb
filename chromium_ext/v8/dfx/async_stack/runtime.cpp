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

namespace v8 {
namespace internal {

RUNTIME_FUNCTION(Runtime_DfxPromiseThen) {
#ifdef V8_ENABLE_OHOS_ASYNC_STACK
  DCHECK_EQ(1, args.length());
  HandleScope scope(isolate);
  Handle<JSReceiver> promise = args.at<JSReceiver>(0);
  if (IsJSPromise(*promise)) {
    // collect async stack
    uint64_t stack_id = dfx::CollectAsyncStack();
    if (stack_id != dfx::kInvalidStackId) {
      isolate->DfxSetPromiseId(Cast<JSPromise>(promise), stack_id);
    }
  }
#endif  // V8_ENABLE_OHOS_ASYNC_STACK
  return ReadOnlyRoots(isolate).undefined_value();
}

RUNTIME_FUNCTION(Runtime_SetAsyncTraceOfMicrotask) {
#ifdef V8_ENABLE_OHOS_ASYNC_STACK
  DCHECK_EQ(1, args.length());
  HandleScope scope(isolate);

  DirectHandle<Object> microtask = args.at(0);
  DirectHandle<JSPromise> promise;
  if (TryGetPromiseFromTask(isolate, microtask).ToHandle(&promise)) {
    uint64_t stack_id = isolate->DfxGetPromiseId(promise);
    if (stack_id != dfx::kInvalidStackId) {
      dfx::SetStackId(stack_id);
    }
  }
#endif
  return ReadOnlyRoots(isolate).undefined_value();
}

RUNTIME_FUNCTION(Runtime_ClearAsyncTraceOfMicrotask) {
#ifdef V8_ENABLE_OHOS_ASYNC_STACK
  DCHECK_EQ(1, args.length());
  HandleScope scope(isolate);

  DirectHandle<Object> microtask = args.at(0);
  DirectHandle<JSPromise> promise;
  if (TryGetPromiseFromTask(isolate, microtask).ToHandle(&promise)) {
    if (isolate->DfxClearPromiseId(promise)) {
      dfx::SetStackId(dfx::kInvalidStackId);
    }
  }
#endif
  return ReadOnlyRoots(isolate).undefined_value();
}

}  // namespace internal
}  // namespace v8
