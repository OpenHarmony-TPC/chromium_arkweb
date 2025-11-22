#!/bin/bash
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

export NB_FILE_SERVER_IP=7.190.160.98:7.190.160.230:7.190.160.207:7.190.163.243:7.190.161.35
CUR_DIR=$PWD
ROOT_DIR="${CUR_DIR%/src*}""/src"

for arg in "$@"; do
        case $arg in
                -cfi)
                        echo "pc"
                        bash nextbuild.sh -t p musl_64 -G use_cfi=true
                        bash $ROOT_DIR/arkweb/build/upload.sh
                        ;;
                -watch)
                        echo "watch"
                        bash nextbuild.sh -t p musl_64 -G build_watch=true
                        bash $ROOT_DIR/arkweb/build/upload.sh
                        ;;
                -x86)
                        echo "x86"
                        bash nextbuild.sh -t p x86_64
                        bash $ROOT_DIR/arkweb/build/upload.sh
                        ;;
                -ut)
                        echo "ut"
                        bash nextbuild.sh  -A -t allut musl_64 -coverage -j 16
                        bash $ROOT_DIR/arkweb/build/upload.sh
                        cd $ROOT_DIR
                        zip -r ut.zip out/musl_64/ut
                        ;;
                -coreut)
                        echo "coreut"
                        bash nextbuild.sh -A -t coreut musl_64 -coverage
                        bash $ROOT_DIR/arkweb/build/upload.sh
                        cd $ROOT_DIR
                        zip -r report.zip out/musl_64/ut
                        ;;
                *)
                        echo"error:$arg"
                        exit 1
                        ;;
        esac
done

if [ $# -eq 0 ];then
        bash nextbuild.sh -t p musl_64
        bash $ROOT_DIR/arkweb/build/upload.sh
fi
