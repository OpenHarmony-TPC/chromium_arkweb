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

import os
import shutil
import argparse

from common import copy_file


def main():
    out_dir = "out/musl_64/"
    saved_dir = out_dir + "ut/"
    unstripped = out_dir + "exe.unstripped/"
    unittests_name =[]
    for filename in os.listdir(unstripped):
        file_full = os.path.join(unstripped, filename)
        if os.path.isfile(file_full):
            name_with, _ = os.path.splitext(filename)
            if name_with.endswith('_unittests'):
                unittests_name.append(name_with)
    print("*****************")
    print(unittests_name)
    print("*****************")
    if not os.path.exists(saved_dir):
        os.makedirs(saved_dir)
    if not os.path.exists(saved_dir + out_dir):
        os.makedirs(saved_dir + out_dir)
    copy_file('ohos_browser_shell', saved_dir + 'ohos_browser_shell')
    copy_file('ohos_build', saved_dir + 'ohos_build')
    copy_file('ohos_glue', saved_dir + 'ohos_glue')
    copy_file('ohos_nweb', saved_dir + 'ohos_nweb')
    copy_file('ohos_nweb_ex', saved_dir + 'ohos_nweb_ex')
    copy_file('ohos_nweb_turbo', saved_dir + 'ohos_nweb_turbo')
    copy_file(out_dir + 'ut_precise', saved_dir + 'ut_precise')
    copy_file(out_dir + 'coverage_instrumentation_input.txt', saved_dir + 'coverage_instrumentation_input.txt')
    file_array = []
    for deps in unittests_name:
        utpath = deps
        dep_path = utpath + ".runtime_deps"
        copy_file(unstripped + utpath, saved_dir + unstripped + utpath)
        try:
            with open(out_dir + dep_path, 'r', encoding='utf-8') as out_file:
                for file_path in out_file.readlines():
                    file_path = file_path.replace("\n", "").replace("lib.unstripped/", "").replace("exe.unstripped/", "")
                    if file_path not in file_array:
                        file_array.append(file_path)
                        if file_path.startswith("../../"):
                            file_path = file_path.replace("../../", "")
                            try:
                                copy_file(file_path, saved_dir + file_path)
                            except Exception as e:
                                print("permission denied")
                        else:
                            file_path = file_path.replace("./", "")
                            copy_file(out_dir + file_path, saved_dir + out_dir + file_path)
        except Exception as e:
            print("file not found")
    print("Archive precise ut result end.")


if __name__ == "__main__":
    main()