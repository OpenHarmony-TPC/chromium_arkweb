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

#include "dfx.h"
#include "../v8/parse-jitcode.h"
#include "securec.h"
#include <cstring>
#include <cerrno>

/*
input : "<functionName> [url]:[line]:[column]"
if name is functionName, return false directly
case 1:
 input name is like "JS:foo https://www.example.com/bar.js:100:200" 
 output 
    functionName : "JS:foo"
    url : "https://www.example.com/bar.js" 
    line : 100
    column : 200

case 2:
 input name is like "BytecodeHandler:SwitchOnGeneratorState.ExtraWide"
 output 
    name : "BytecodeHandler:SwitchOnGeneratorState.ExtraWide"
*/
static bool DecodeName(const std::string& name, std::string& functionName, std::string& url,
                                                    int32_t& line, int32_t& column) {
  size_t pos = 0;
  for (; pos < name.size(); ++pos) {
    if (name[pos] == ' ') {
      break;
    }
  }
  if (pos == name.size() || pos + 1 == name.size()) {
    return false; // case 2
  }
  functionName = name.substr(0, pos);
  url = name.substr(pos + 1);
  int32_t line_ = 0;
  int32_t column_ = 0;
  auto it = url.rbegin();
  if (it == url.rend()) { return false; }
  auto CharIsNumber = [](char c) -> bool {
    return c >= '0' && c <= '9';
  };
  if (CharIsNumber(*it)) {
    int base = 1;
    do {
      column_ += base * reinterpret_cast<int32_t>(*it - '0');
      base *= 10;
      if (++it == url.rend()) { return false; }
    } while (CharIsNumber(*it));
    if (*it == ':' && ++it != url.rend() && CharIsNumber(*it)) {
      base = 1;
      do {
        line_ += base * reinterpret_cast<int32_t>(*it - '0');
        base *= 10;
        if (++it == url.rend()) { return false; }
      } while (CharIsNumber(*it));
      if (*it == ':') {
        // complete get location
        line = line_;
        column = column_;
        ++it;
        url.erase(it.base(), url.end());
        return true;
      }
    }
  }
  return false;
}

__attribute__((visibility("default"))) int step_webjs(void *ctx, ReadMemFunc readMem, JsStepParam *frame)
{
    if (frame == nullptr || frame->fp == nullptr) {
        return -1; // Invaild input
    }
    uintptr_t preFp = 0;
    readMem(ctx, *(frame->fp), &preFp);
    uintptr_t prePc = 0;
    readMem(ctx, *(frame->fp) + sizeof(void*), &prePc);

    *(frame->fp) = preFp;
    *(frame->pc) = prePc;
    *(frame->sp) = preFp;
    return 0;
}

__attribute__((visibility("default"))) int create_webjs_extractor(uintptr_t* extractorPtr, uint32_t pid)
{
    v8::jitparse::JsSymbolExtractor* exactor_ =
        new v8::jitparse::JsSymbolExtractor(pid);
    if (exactor_->GetParser()) {
        *extractorPtr = reinterpret_cast<uintptr_t>(exactor_);
        return 0;
    } else {
        delete exactor_;
        return -1;
    }
}

__attribute__((visibility("default"))) int destroy_webjs_extractor(uintptr_t extractor)
{
    delete reinterpret_cast<v8::jitparse::JsSymbolExtractor*>(extractor);
    return 0;
}

__attribute__((visibility("default"))) int web_parse_js_frame_info(uintptr_t pc,
                                                               uintptr_t webjsExtractor,
                                                               WebjsFunction* webjsFunction)
{
    if (webjsExtractor == 0) {
        return -1;
    }
    std::string codeName;
    v8::jitparse::JsSymbolExtractor* extractor_ =
        reinterpret_cast<v8::jitparse::JsSymbolExtractor*>(webjsExtractor);

    if (extractor_->GetInstruction(pc, codeName, webjsFunction->offsetInFunction)) {
        std::string functionName;
        std::string url;
        int32_t line;
        int32_t column;
        if (DecodeName(codeName, functionName, url, line, column)) {
            if (strcpy_s(webjsFunction->functionName, FUNCTIONNAME_MAX, functionName.c_str()) != EOK) {
                return -1;
            }
            if (strcpy_s(webjsFunction->url, URL_MAX, url.c_str()) != EOK) {
                return -1;
            }
            webjsFunction->line = line;
            webjsFunction->column = column;
        } else {
            if (strcpy_s(webjsFunction->functionName, FUNCTIONNAME_MAX, codeName.c_str()) != EOK) {
                return -1;
            }
        }
        return 0;
    } else {
        return -1;
    }
}
