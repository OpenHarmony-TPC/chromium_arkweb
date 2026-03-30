#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Copyright (c) 2022 Huawei Device Co., Ltd.
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
#

import os
import shutil
import argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('ut')
    args = parser.parse_args()
    print("start archiving")
    start_line = 0
    end_line = 0
    lines = []
    with open('arkweb/build/unittests/BUILD.gn', 'r', encoding='utf-8') as file:
        lines = file.readlines()
        for index, line in enumerate(lines):
            if args.ut == 'allut':
                if "oh_base_unittests" in line:
                    start_line = index
                    break
            if args.ut == 'coreut':
                if "oh_core_unittests" in line:
                    start_line = index
                    break
    for j in range(len(lines) - start_line):
        if "}" in lines[start_line + j]:
            end_line = start_line + j
            break

    deps_start = start_line
    deps_end = start_line

    for k in range(end_line - start_line):
        if "deps = [" in lines[start_line + k]:
            deps_start = start_line + k
            break

    for h in range(end_line - deps_start):
        if "]" in lines[deps_start + h]:
            deps_end = deps_start + h
            break

    deps_list = []
    if args.ut == 'coverage':
        deps_list = [
            '    "//base:base_unittests",\n',
            '    "//components:components_unittests",\n',
            '    "//cef:libcef_static_unittests",\n',
            '    "//components/viz:viz_unittests",\n',
            '    "//crypto:crypto_unittests",\n',  
            '    "//gin:gin_unittests",\n',
            '    "//gpu:gpu_unittests",\n',
            '    "//media:media_unittests",\n',
            '    "//ohos_nweb/test:ohos_nweb_unittests",\n',
            '    "//skia:skia_unittests",\n',
            '    "//third_party/blink/common:blink_common_unittests",\n',
            '    "//third_party/blink/renderer/platform:blink_platform_unittests",\n',
            '    "//ui/accessibility:accessibility_unittests",\n',
            '    "//ui/base:ui_base_unittests",\n',
            '    "//ui/compositor:compositor_unittests",\n',
            '    "//ui/gl:gl_unittests",\n',
            '    "//components/gwp_asan:gwp_asan_unittests",\n',
            '    "//components/services/filesystem:filesystem_service_unittests",\n',
            '    "//device:device_unittests",\n',
            '    "//media:audio_unittests",\n',
            '    "//media/cast:cast_unittests",\n',
            '    "//media/midi:midi_unittests",\n',
            '    "//media/mojo:media_mojo_unittests",\n',
            '    "//media/capture:capture_unittests",\n',
            '    "//media/learning/mojo:media_learning_mojo_unittests",\n',
            '    "//mojo:mojo_unittests",\n',
            '    "//third_party/blink/renderer/platform/heap:blink_heap_unittests",\n',
            '    "//third_party/catapult/tracing/tracing:histogram_unittests",\n',
            '    "//third_party/ced:ced_unittests",\n',
            '    "//third_party/liburlpattern:liburlpattern_unittests",\n',
            '    "//third_party/libjingle_xmpp:libjingle_xmpp_unittests",\n',
            '    "//third_party/libjpeg_turbo:libjpeg_turbo_unittests",\n',
            '    "//third_party/perfetto:perfetto_unittests",\n',
            '    "//third_party/zlib:zlib_unittests",\n',
            '    "//ui/color:color_unittests",\n',
            '    "//ui/display:display_unittests",\n',
            '    "//ui/gfx:gfx_unittests",\n',
            '    "//ui/latency:latency_unittests",\n',
            '    "//ui/native_theme:native_theme_unittests",\n',
            '    "//ui/shell_dialogs:shell_dialogs_unittests",\n',
            '    "//ui/touch_selection:ui_touch_selection_unittests",\n',
            '    "//url:url_unittests",\n',
            '    "//printing:printing_unittests",\n',
            '    "//services/service_manager/tests:service_manager_unittests",\n',
            '    "//storage:storage_unittests",\n',
            '    "//sql:sql_unittests",\n',
            '    "//cc:cc_unittests",\n',
            '    "//third_party/blink/renderer/controller:blink_unittests",\n']
    else:
        for h in range(deps_end - deps_start - 1):
            deps_list.append(lines[deps_start + h + 1])

    out_dir = "out/musl_64/"
    saved_dir = out_dir + "ut/"
    unstripped = out_dir + "exe.unstripped/"
    if not os.path.exists(saved_dir):
        os.makedirs(saved_dir)
    if not os.path.exists(saved_dir + out_dir):
        os.makedirs(saved_dir + out_dir)
    file_array = []
    for deps in deps_list:
        utpath = deps[deps.find(":")+1:deps.rfind("\"")]
        dep_path = utpath + ".runtime_deps"
        copy_file(out_dir + utpath, saved_dir + out_dir + utpath)
        if "GERRIT_CHANGE_URL" not in os.environ:
            copy_file(unstripped + "libarkweb_engine.so", saved_dir + unstripped + "libarkweb_engine.so")
            copy_file(unstripped + "libarkweb_render.so", saved_dir + unstripped + "libarkweb_render.so")
            copy_file(unstripped + "libarkweb_crashpad_handler.so", saved_dir + unstripped + "libarkweb_crashpad_handler.so")
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
    global count
    print("Path：" + saved_dir + "，Quantity：" + str(count))

count = 0


def copy_file(source_path, target_path):
    folder_path = target_path[0:target_path.rfind("/")]
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
    try:
        shutil.copy(source_path, target_path)
        global count
        count += 1
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
                global count
                count += 1
            except Exception as e:
                print("permission denied")

if __name__ == "__main__":
    main()