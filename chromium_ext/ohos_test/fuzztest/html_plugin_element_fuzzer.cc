/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "third_party/blink/renderer/core/html/html_plugin_element.h"

#include "fuzzer/FuzzedDataProvider.h"
#include "third_party/blink/public/platform/browser_interface_broker_proxy.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/document_init.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "arkweb/chromium_ext/third_party/blink/renderer/core/html/html_plugin_element_utils.h"

using namespace blink;
namespace blink {
class CORE_EXPORT FuzzHTMLPlugInElement final : public HTMLPlugInElement {
 public:
  FuzzHTMLPlugInElement(Document& document,
                        const CreateElementFlags flags = CreateElementFlags())
      : HTMLPlugInElement(html_names::kEmbedTag, document, flags) {}

  FrameOwnerElementType OwnerType() const override {
    return FrameOwnerElementType::kNone;
  }

  LayoutEmbeddedContent* ExistingLayoutEmbeddedContent() const override {
    return nullptr;
  }

  void UpdatePluginInternal() override {}
};

void HtmlPlugInElementFuzzTest(const uint8_t* data, size_t size) {
  DocumentInit init = DocumentInit::Create();
  if (init.GetExecutionContext() == nullptr) {
    return;
  }
  Document document(init);
  std::shared_ptr<HTMLPlugInElement> element =
      std::make_shared<FuzzHTMLPlugInElement>(document);
  const char* key = reinterpret_cast<const char*>(data);
  element->Utils()->CheckNativeType(key);
}
}  // namespace blink

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  HtmlPlugInElementFuzzTest(data, size);
  return 0;
}
 