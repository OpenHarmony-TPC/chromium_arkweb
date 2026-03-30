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
#include <string>
#include "arkweb/chromium_ext/content/browser/dfx/dfx_reporter_browser_impl.h"


namespace OHOS::NWeb {
namespace {
    constexpr uint32_t MAX_UINT32_SIZE = 255;
    constexpr int32_t MAX_INT32_SIZE = 255;
    constexpr int32_t MIN_INT32_SIZE = -255;
    constexpr uint8_t MAX_STRING_LENGTH = 255;
}

void DfxReporterBrowserImplFuzz001Test(const uint8_t* data, size_t size) {
    if ((data == nullptr) || (size == 0)) {
        return;
    }
    FuzzedDataProvider dataProvider(data, size);
    
    // Test ReportMemInfo with various JSON inputs
    uint8_t jsonSize = dataProvider.ConsumeIntegralInRange<uint8_t>(0, MAX_STRING_LENGTH);
    std::string jsonData = dataProvider.ConsumeRandomLengthString(jsonSize);
    
    DfxReporterImpl reporter;
    reporter.ReportMemInfo(jsonData);
}

void DfxReporterBrowserImplFuzz002Test(const uint8_t* data, size_t size) {
    if ((data == nullptr) || (size == 0)) {
        return;
    }
    FuzzedDataProvider dataProvider(data, size);
    
    // Test ReportHiSysEvent with various event names and JSON inputs
    uint8_t eventNameSize = dataProvider.ConsumeIntegralInRange<uint8_t>(0, MAX_STRING_LENGTH);
    std::string eventName = dataProvider.ConsumeRandomLengthString(eventNameSize);
    
    uint8_t jsonSize = dataProvider.ConsumeIntegralInRange<uint8_t>(0, MAX_STRING_LENGTH);
    std::string jsonData = dataProvider.ConsumeRandomLengthString(jsonSize);
    
    DfxReporterImpl reporter;
    reporter.ReportHiSysEvent(eventName, jsonData);
}

void DfxReporterBrowserImplFuzz003Test(const uint8_t* data, size_t size) {
    if ((data == nullptr) || (size == 0)) {
        return;
    }
    FuzzedDataProvider dataProvider(data, size);
    
    // Test ReportRendererInfo with various JSON inputs
    uint8_t jsonSize = dataProvider.ConsumeIntegralInRange<uint8_t>(0, MAX_STRING_LENGTH);
    std::string jsonData = dataProvider.ConsumeRandomLengthString(jsonSize);
    
    // Test both isSysEvent true and false
    ReportRendererInfo(jsonData, true);
    ReportRendererInfo(jsonData, false);
}

void DfxReporterBrowserImplFuzz004Test(const uint8_t* data, size_t size) {
    if ((data == nullptr) || (size == 0)) {
        return;
    }
    FuzzedDataProvider dataProvider(data, size);
    
    int32_t pid = dataProvider.ConsumeIntegral<int32_t>();
    int32_t uid = dataProvider.ConsumeIntegral<int32_t>();
    
    uint8_t processNameSize = dataProvider.ConsumeIntegralInRange<uint8_t>(0, MAX_STRING_LENGTH);
    std::string processName = dataProvider.ConsumeRandomLengthString(processNameSize);
    
    uint8_t freezeMsgSize = dataProvider.ConsumeIntegralInRange<uint8_t>(0, MAX_STRING_LENGTH);
    std::string freezeMsg = dataProvider.ConsumeRandomLengthString(freezeMsgSize);
    
    FreezeReporterImpl reporter;
    reporter.ReportRenderFreeze(pid, processName, freezeMsg, uid);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    DfxReporterBrowserImplFuzz001Test(data, size);
    DfxReporterBrowserImplFuzz002Test(data, size);
    DfxReporterBrowserImplFuzz003Test(data, size);
    DfxReporterBrowserImplFuzz004Test(data, size);
    return 0;
}

}   // namespace OHOS::NWeb
