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

#include <mutex>

#include "hicollie_freeze_reporter.h"
#include "base/logging.h"
#include "hicollie/hicollie.h"
#include "third_party/bounds_checking_function/include/securec.h"

namespace {

std::string g_freezeMsg = "arkweb freeze";
std::mutex g_msgMutex;

bool g_isCallbackRegistered = false;
bool g_isFreezeEvent = false;
std::mutex g_hicollieMutex;

size_t FreezeCallback(HiCollie_Freeze_Type type, void* buffer, size_t size) {
    if (!buffer || size == 0) {
        return 0;
    }

    std::string msg = HicollieReporter::GetFreezeMessage();
    size_t msgSize = msg.size() + 1;
    if (size < msgSize) {
        return 0;
    }

    errno_t err = memcpy_s(buffer, size, msg.c_str(), msgSize);
    if (err != 0) {
        LOG(ERROR) << "memcpy_s failed: " << err;
        return 0;
    }

    return msg.size();
}

} // anonymous namespace

namespace HicollieReporter {

void SetFreezeMessage(const std::string& msg) {
    std::lock_guard<std::mutex> lock(g_msgMutex);
    g_freezeMsg = msg;
}

std::string GetFreezeMessage() {
    std::lock_guard<std::mutex> lock(g_msgMutex);
    return g_freezeMsg;
}

void ReportFreezeToHicollie() {
    std::lock_guard<std::mutex> lock(g_hicollieMutex);

    if (!g_isCallbackRegistered) {
        OH_HiCollie_SetFreezeCallback(&FreezeCallback);
        g_isCallbackRegistered = true;
    }

    HiCollie_ErrorCode code = OH_HiCollie_AssociateProcessReport(g_isFreezeEvent);
    if (code != HICOLLIE_SUCCESS) {
        LOG(ERROR) << "HiCollie report failed, error: " << code;
    }

    g_isFreezeEvent = !g_isFreezeEvent;
}

} // namespace HicollieReporter