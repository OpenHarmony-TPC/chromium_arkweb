#!/usr/bin/env python3
# coding=utf-8
# Copyright (c) 2025 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import json
import xml.etree.ElementTree as ET

pr_list = os.environ.get("PR_FILE_PATHS")
data = json.loads(pr_list)

tree = ET.parse(".repo/manifests/chromium.xml")
root = tree.getroot()

matched_paths = []

for project in root.findall("project"):
    name = project.get("name")
    path = project.get("path")
    if name in data:
        for file_path in data[name]:
            matched_path = f"{path}/{file_path}"
            matched_paths.append(matched_path)
print(matched_paths)

check_list = ['system/app/ArkWebCore','system/app/ArkWebCoreLegacy','ArkWebCore.hap','ArkWebCoreLegacy.hap','com.huawei.hmos.arkwebcore','com.huawei.hmos.arkwebcorelegacy','ArkWebCore','ArkWebCoreLegacy']
def check_paths_in_files(file_paths):
    result = 0
    for file_path in file_paths:
        with open(file_path, 'r',encoding='utf-8',errors='ignore') as file:
            for line in file:
                for item in check_list:
                    if item in line:
                        print(f"文件 {file_path} 中含有违规字段{item}，请修改,代码中不能含有{check_list}")
                        result = 1
                        break
    return result

result = check_paths_in_files(matched_paths)
print(f"检查结果: {result}")
exit(1 if result else 0)
    