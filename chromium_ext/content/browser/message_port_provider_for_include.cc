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

#if BUILDFLAG(IS_ARKWEB)
void MessagePortProvider::OhosPostMessageToFrame(
    Page& page,
    const std::u16string& source_origin,
    const std::u16string& target_origin,
    const std::u16string& data,
    std::vector<blink::WebMessagePort>& ports) {
  LOG(INFO) << "JSAPI OhosPostMessageToFrame";
  // Extract the underlying descriptors.
  std::vector<blink::MessagePortDescriptor> descriptors;
  for (size_t i = 0; i < ports.size(); ++i) {
    descriptors.push_back(ports[i].PassPort());
  }

  // Convert std::u16string origins to url::Origin pointers for Chromium 144
  std::optional<url::Origin> source;
  if (!source_origin.empty()) {
    source = url::Origin::Create(GURL(source_origin));
  }

  std::optional<url::Origin> target;
  if (!target_origin.empty()) {
    target = url::Origin::Create(GURL(target_origin));
  }

  PostMessageToFrameInternal(page,
                             source.has_value() ? &(*source) : nullptr,
                             target.has_value() ? &(*target) : nullptr,
                             data,
                             std::move(descriptors));
}
#endif