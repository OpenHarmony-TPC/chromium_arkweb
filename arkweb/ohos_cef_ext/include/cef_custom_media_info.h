
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

#ifndef CEF_INCLUDE_CEF_CUSTOM_MEDIA_INFO_H_
#define CEF_INCLUDE_CEF_CUSTOM_MEDIA_INFO_H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

struct CefMediaSourceInfo {
  uint32_t source_type = 0;
  std::string media_source;
  std::string media_format;
};

struct CefNativeMediaPlayerSurfaceInfo {
  std::string id;
  int32_t x = 0;
  int32_t y = 0;
  int32_t width = 0;
  int32_t height = 0;
};

struct CefCustomMediaInfo {
  std::string embed_id;
  uint32_t media_type = 0;
  std::vector<CefMediaSourceInfo> media_src_list;
  CefNativeMediaPlayerSurfaceInfo surface_info;
  bool controls = false;
  std::vector<std::string> controlslist;
  bool muted = false;
  std::string poster_url;
  uint32_t preload = 0;
  std::map<std::string, std::string> https_headers;
  std::map<std::string, std::string> attributes;
};

#endif  // CEF_INCLUDE_CEF_CUSTOM_MEDIA_INFO_H_
