#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
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

import shutil
import os


def copy_file(source_path, target_path):
    folder_path = target_path[0:target_path.rfind("/")]
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
    try:
        shutil.copy(source_path, target_path)
    except FileNotFoundError:
        print("FileNotFoundError: " + source_path)
    except IsADirectoryError:
        copy_folder(source_path, target_path)


def copy_folder(source_folder, destination_folder):
    if not os.path.exists(destination_folder):
        os.makedirs(destination_folder)
 
    for item in os.listdir(source_folder):
        source = os.path.join(source_folder, item)
        destination = os.path.join(destination_folder, item)
 
        if os.path.isdir(source):
            try:
                copy_folder(source, destination)
            except Exception as e:
                print("permission denied")
        else:
            try:
                shutil.copy(source, destination)
            except Exception as e:
                print("permission denied")