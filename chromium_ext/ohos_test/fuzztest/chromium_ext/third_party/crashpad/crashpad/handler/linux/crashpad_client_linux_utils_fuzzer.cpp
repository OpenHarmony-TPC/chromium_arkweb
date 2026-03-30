/*
* Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <fuzzer/FuzzedDataProvider.h>
#include <vector>
#include <string>
#include "arkweb/chromium_ext/third_party/crashpad/crashpad/handler/linux/crashpad_client_linux_utils.h"

namespace OHOS::NWeb {
namespace {
    constexpr uint32_t MAX_UINT32_SIZE = 255;
    constexpr int32_t MAX_INT32_SIZE = 255;
    constexpr int32_t MIN_INT32_SIZE = -255;
    constexpr uint8_t MAX_STRING_LENGTH = 255;
}

void CrashpadClientLinuxUtilsFuzz001Test(const uint8_t* data, size_t size) {
    if ((data == nullptr) || (size == 0)) {
        return;
    }
    FuzzedDataProvider dataProvider(data, size);
    
    // Test AddCrashpadArguments
    std::vector<std::string> argv;
    std::string g_happen_time;
    
    // Add some initial arguments
    uint32_t initialArgCount = dataProvider.ConsumeIntegralInRange<uint32_t>(0, 10);
    for (uint32_t i = 0; i < initialArgCount; i++) {
        argv.push_back(dataProvider.ConsumeRandomLengthString(MAX_STRING_LENGTH));
    }
    
    crashpad::CrashpadClientUtils::AddCrashpadArguments(argv, g_happen_time);
    
    // Verify that arguments were added
    // After calling AddCrashpadArguments, argv should have at least 2 more elements
    // (--happen-time and --bundle-name)
}

void CrashpadClientLinuxUtilsFuzz002Test(const uint8_t* data, size_t size) {
    if ((data == nullptr) || (size == 0)) {
        return;
    }
    FuzzedDataProvider dataProvider(data, size);
    
    // Test multiple calls
    for (int i = 0; i < 5; i++) {
        std::vector<std::string> argv;
        std::string g_happen_time;
        
        crashpad::CrashpadClientUtils::AddCrashpadArguments(argv, g_happen_time);
    }
}

void CrashpadClientLinuxUtilsFuzz003Test(const uint8_t* data, size_t size) {
    if ((data == nullptr) || (size == 0)) {
        return;
    }
    
    // Test with empty argv
    std::vector<std::string> empty_argv;
    std::string g_happen_time;
    crashpad::CrashpadClientUtils::AddCrashpadArguments(empty_argv, g_happen_time);
    
    // Test with non-empty argv
    std::vector<std::string> non_empty_argv = {"--some-arg", "value"};
    std::string g_happen_time2;
    crashpad::CrashpadClientUtils::AddCrashpadArguments(non_empty_argv, g_happen_time2);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    CrashpadClientLinuxUtilsFuzz001Test(data, size);
    CrashpadClientLinuxUtilsFuzz002Test(data, size);
    CrashpadClientLinuxUtilsFuzz003Test(data, size);
    return 0;
}

}   // namespace OHOS::NWeb