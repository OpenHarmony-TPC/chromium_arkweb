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
#ifndef BASE_TUPLE_ext_H_
#define BASE_TUPLE_ext_H_

#include <stddef.h>

#include <tuple>
#include <utility>

#include "arkweb/build/features/features.h"
#include "build/build_config.h"

namespace base {

#if BUILDFLAG(ARKWEB_JAVASCRIPT_BRIDGE)
template <typename ObjT,
          typename Method,
          typename InTuple,
          typename OutTuple,
          typename P,
          size_t... InNs,
          size_t... OutNs>
inline void DispatchToMethodImpl_Param(const ObjT& obj,
                                       Method method,
                                       InTuple&& in,
                                       OutTuple* out,
                                       P* parameter,
                                       std::index_sequence<InNs...>,
                                       std::index_sequence<OutNs...>)
{
    (obj->*method)(parameter, std::get<InNs>(std::forward<InTuple>(in))...,
                &std::get<OutNs>(*out)...);
}

template <typename ObjT,
          typename Method,
          typename InTuple,
          typename P,
          typename OutTuple>
inline void DispatchToMethod_Param(const ObjT& obj,
                                   Method method,
                                   InTuple&& in,
                                   P* parameter,
                                   OutTuple* out)
{
    constexpr size_t in_size = std::tuple_size<std::decay_t<InTuple>>::value;
    constexpr size_t out_size = std::tuple_size<OutTuple>::value;
    DispatchToMethodImpl_Param(obj, method, std::forward<InTuple>(in), out,
                               parameter, std::make_index_sequence<in_size>(),
                               std::make_index_sequence<out_size>());
}
#endif

} // namespace base
#endif  // BASE_TUPLE_EXT_H_