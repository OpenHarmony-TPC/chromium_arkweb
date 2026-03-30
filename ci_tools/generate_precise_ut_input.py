#!/usr/bin/env python
# -*- coding: utf-8 -*-
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

import json
import os
import stat
import subprocess

from common import copy_file


def process_change_json(file_path):
    with open(file_path, 'r') as f:
        data = json.load(f)
        result = []
        for path_node, node_data in data.items():
            changed_files = node_data["changed_file_list"]
            for changed_type in ["added", "modified", "deleted"]:
                for file_path in changed_files[changed_type]:
                    result.append(f"{path_node}/{file_path}")
            for old_name, new_name in changed_files["rename"]:
                result.append(f"{path_node}/{new_name}")
    process = []
    for path in result:
        if path.startswith("src/"):
            process.append(f"//{path[4:]}")
        else:
            process.append(f"//{path}")
    return process


def categorize_files(paths):
    categorized = {
        "h_file": [],
        "c_file":[],
        "gn_file":[],
        "gn_module":[]
    }
    for path in paths:
        if path.endswith('.h'):
            categorized["h_file"].append(path)
        if path.endswith('.cc'):
            categorized["c_file"].append(path)
    return categorized


def save_to_json(data, output_files):
    try:
        subprocess.run(
            ["rm", "-rf", output_files],
            check=True,
            stderr=subprocess.PIPE,
            text=True
        )
    except subprocess.CalledProcessError as e:
        print(e.stderr)   
    flags = os.O_WRONLY | os.O_CREAT | os.O_EXCL
    modes = stat.S_IWGRP | stat.S_IRUSR
    with os.fdopen(os.open(output_files, flags, modes), 'w') as f:
        json.dump(data, f, indent=2)


def format_files(paths, output_path):
    filtered = []
    try:
        subprocess.run(
            ["rm", "-rf", output_path],
            check=True,
            stderr=subprocess.PIPE,
            text=True
        )
    except subprocess.CalledProcessError as e:
        print(e.stderr)
    for path in paths:
        if path.endswith(('.h', '.cc')):
            filtered.append(f"../../{path[2:]}")
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    flags = os.O_WRONLY | os.O_CREAT | os.O_EXCL
    modes = stat.S_IWGRP | stat.S_IRUSR
    with os.fdopen(os.open(output_path, flags, modes), 'w') as f:
        for line in filtered:
            f.write(f"{line}\n")


if __name__ == "__main__":
    try:
        files_path = "change_info.json"
        out_path = "src/modify_files.json"
        coverage_path = "src/out/musl_64/coverage_instrumentation_input.txt"
        copy_file('src/arkweb/ci_tools/gn', 'src/buildtools/linux64/gn')
        precess_paths = process_change_json(files_path)
        categorize_data = categorize_files(precess_paths)
        save_to_json(categorize_data, out_path)
        format_files(precess_paths, coverage_path)
        print("*****************************")
        with open("src/modify_files.json",'r') as file:
            print(file.read())
        with open("src/out/musl_64/coverage_instrumentation_input.txt",'r') as file:
            print(file.read())
        print("*****************************")
    except Exception as e:
        print("*****************************")
        print("not found")
        print("*****************************")
        out_exe = "src/modify_files.json"
        coverage_exe = "src/out/musl_64/coverage_instrumentation_input.txt"
        categorized = {
        "h_file": [],
        "c_file":[],
        "gn_file":[],
        "gn_module":[]
        }
        save_to_json(categorized, out_exe)
        subprocess.run(
            ["rm", "-rf", coverage_exe],
            check=True,
            stderr=subprocess.PIPE,
            text=True
        )
        os.makedirs(os.path.dirname(coverage_exe), exist_ok=True)
        flags = os.O_WRONLY | os.O_CREAT | os.O_EXCL
        modes = stat.S_IWGRP | stat.S_IRUSR
        with os.fdopen(os.open(coverage_exe, flags, modes), 'w') as f:
            pass
    print("Generate precise ut input end.")