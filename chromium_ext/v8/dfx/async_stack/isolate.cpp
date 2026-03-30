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

#ifdef V8_ENABLE_OHOS_ASYNC_STACK
#include "async_stack.h"
namespace v8 {
namespace internal {
MaybeHandle<JSPromise> TryGetPromiseFromTask(Isolate* isolate,
                                             DirectHandle<Object> microtask) {
  if (IsPromiseReactionJobTask(*microtask)) {
    auto promise_reaction_job_task = Cast<PromiseReactionJobTask>(microtask);
    // Check if the {reaction} has one of the known async function or
    // async generator continuations as its fulfill handler.
    if (IsBuiltinAsyncFulfillHandler(isolate,
                                     promise_reaction_job_task->handler()) ||
        IsBuiltinAsyncRejectHandler(isolate,
                                    promise_reaction_job_task->handler())) {
      // Now peek into the handlers' AwaitContext to get to
      // the JSGeneratorObject for the async function.
      DirectHandle<Context> context(
          Cast<JSFunction>(promise_reaction_job_task->handler())->context(),
          isolate);
      Handle<JSGeneratorObject> generator_object(
          Cast<JSGeneratorObject>(context->extension()), isolate);
      if (generator_object->is_executing()) {
        if (IsJSAsyncFunctionObject(*generator_object)) {
          auto async_function_object =
              Cast<JSAsyncFunctionObject>(generator_object);
          Handle<JSPromise> promise(async_function_object->promise(), isolate);
          return promise;
        } else {
          auto async_generator_object =
              Cast<JSAsyncGeneratorObject>(generator_object);
          DirectHandle<Object> queue(async_generator_object->queue(), isolate);
          if (!IsUndefined(*queue, isolate)) {
            auto async_generator_request = Cast<AsyncGeneratorRequest>(queue);
            Handle<JSPromise> promise(
                Cast<JSPromise>(async_generator_request->promise()), isolate);
            return promise;
          }
        }
      }
    } else {
#if V8_ENABLE_WEBASSEMBLY
      Handle<WasmSuspenderObject> suspender;
      if (TryGetWasmSuspender(isolate, promise_reaction_job_task->handler())
              .ToHandle(&suspender)) {
        // The {promise_reaction_job_task} belongs to a suspended Wasm stack
        return handle(suspender->promise(), isolate);
      }
#endif  // V8_ENABLE_WEBASSEMBLY

      // The {promise_reaction_job_task} doesn't belong to an await (or
      // yield inside an async generator) or a suspended Wasm stack,
      // but we might still be able to find an async frame if we follow
      // along the chain of promises on the {promise_reaction_job_task}.
      Handle<HeapObject> promise_or_capability(
          promise_reaction_job_task->promise_or_capability(), isolate);
      if (IsJSPromise(*promise_or_capability)) {
        Handle<JSPromise> promise = Cast<JSPromise>(promise_or_capability);
        return promise;
      }
    }
  }
  return MaybeHandle<JSPromise>();
}

void Isolate::DfxSetPromiseId(DirectHandle<JSPromise> promise, uint64_t id) {
  int hash_id = Smi::ToInt(promise->GetOrCreateIdentityHash(this));
  auto result = promise_to_dfx_async_id_.try_emplace(hash_id, id);
  if (V8_UNLIKELY(!result.second)) {
    promise_to_dfx_async_id_.erase(hash_id);
  }
}

uint64_t Isolate::DfxGetPromiseId(DirectHandle<JSPromise> promise) {
  Tagged<Object> maybeHash = promise->GetIdentityHash();
  if (V8_LIKELY(IsSmi(maybeHash))) {
    int hash_id = Smi::ToInt(maybeHash);
    auto it = promise_to_dfx_async_id_.find(hash_id);
    if (it == promise_to_dfx_async_id_.end()) {
      return dfx::kInvalidStackId;
    } else {
      return it->second;
    }
  } else {
    return dfx::kInvalidStackId;
  }
}

bool Isolate::DfxClearPromiseId(DirectHandle<JSPromise> promise) {
  Tagged<Object> maybeHash = promise->GetIdentityHash();
  if (V8_LIKELY(IsSmi(maybeHash))) {
    int hash_id = Smi::ToInt(maybeHash);
    return static_cast<bool>(promise_to_dfx_async_id_.erase(hash_id));
  }
  return false;
}

}  // namespace internal
}  // namespace v8
#endif  // V8_ENABLE_OHOS_ASYNC_STACK