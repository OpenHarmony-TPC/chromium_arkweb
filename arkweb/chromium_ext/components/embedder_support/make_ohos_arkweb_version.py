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

import json
import optparse
import sys

def _ParseOptions():
    parser = optparse.OptionParser()
    parser.add_option('-i',
                      '--input_file',
                      help='input version json5')
    parser.add_option('-o',
                      '--output_file',
                      help='output version file')
    options, _ = parser.parse_args()
    return options

def ReadHeader(options):
    arkwebVersion = "4.1.6.1"
    with open(options.input_file, 'r') as f:
        data = json.load(f)
        if data is None:
            return arkwebVersion
        if "app" in data and "versionName" in data["app"]:
            arkwebVersion = data["app"]["versionName"].split("sp")[0]
    return arkwebVersion

def WriteHeader(options, version):
    header_macros = "ARKWEB_VERSION_H"
    with open(options.output_file, "w") as output_file:
        output_file.write('#ifndef %s\n' % header_macros)
        output_file.write('#define %s\n\n' % header_macros)
        output_file.write('\n#define ARKWEB_VERSION \"%s\"\n' % version)
        output_file.write('\n#endif  // %s\n' % header_macros)


if '__main__' == __name__:
    options = _ParseOptions()
    WriteHeader(options, ReadHeader(options))
    
