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

#ifdef USING_OHOS_WEB
#include "ohlog.h"
#ifdef OSOHOS
#undef LOG
#undef ALIGNAS
#include <cstdio>

#include "../../../base/logging.h"
#endif
#include <cstdarg>

void PrintHilog(const char* format, va_list args) {
#ifdef OSOHOS
  va_list args_copy;
  va_copy(args_copy, args);
  auto size = vsnprintf(nullptr, 0, format, args_copy) + 1;
  va_end(args_copy);
  auto* buffer = new char[size];
  vsnprintf(buffer, size, format, args);
  StreamHilog(std::string(buffer));
  delete[] buffer;
#endif
}

void StreamHilog(const std::string& string) {
#ifdef OSOHOS
  LOG(INFO) << "[V8 DEBUG LOG] : " << string;
#endif
}
#endif
