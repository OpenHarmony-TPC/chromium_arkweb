/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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


#include <atomic>
#include <gtest/gtest.h>
#include <map>
#include <mutex>
#include <string>
#include <string>

#include "base/logging.h"
#include "arkweb/build/features/features.h"
#include "ohos_nweb/src/capi/browser_service/nweb_extension_content_settings_types.h"
#include "nweb_extension_content_settings_cef_delegate.h"
#if BUILDFLAG(IS_ARKWEB_EXT)
#include "arkweb/ohos_nweb_ex/build/features/features.h"
#endif

#if BUILDFLAG(ARKWEB_NWEB_EX)
#include "ohos_nweb_ex/core/extension/nweb_extension_content_settings_dispatcher.h"
#endif


using namespace std;

namespace OHOS::NWeb {

std::map<int, ContentSettingsGetCallback> g_content_settings_get_callback_map_;
std::mutex g_content_settings_get_callback_map_mutex;
std::map<int, ContentSettingsSetCallback> g_content_settings_set_callback_map_;
std::mutex g_content_settings_set_callback_map_mutex;
std::map<int, ContentSettingsClearCallback> g_content_settings_clear_callback_map_;
std::mutex g_content_settings_clear_callback_map_mutex;


class NWebExtensionContentSettingsCefDelegateTest : public testing::Test {
protected:
    void SetUp() override {
        delegate = &NWebExtensionContentSettingsCefDelegate::GetInstance();
        {
            lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
            g_content_settings_get_callback_map_.clear();
        }
    }

    void TearDown() override {
        {
            lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
            g_content_settings_get_callback_map_.clear();
        }
    }

    NWebExtensionContentSettingsCefDelegate *delegate;
};

TEST_F(NWebExtensionContentSettingsCefDelegateTest, TestGetInstance) {
    auto &instance1 = NWebExtensionContentSettingsCefDelegate::GetInstance();
    auto &instance2 = NWebExtensionContentSettingsCefDelegate::GetInstance();
    EXPECT_EQ(&instance1, &instance2);
}

TEST_F(NWebExtensionContentSettingsCefDelegateTest, TestOnGetSuccess) {
    NWebExtensionContentSettingsGetParam param = {0};
    param.primaryUrl = strdup("https://example.com");
    param.secondaryUrl = strdup("https://sub.example.com");
    param.type = strdup("cookies");
    param.extensionId = strdup("12345");
    NWebExtensionContentSettingsCallbackResult resultParam = {0};
    resultParam.requestId = 0;
    resultParam.detailParam = new NWebExtensionContentSettingsDetail();
    resultParam.detailParam->contentSetting = strdup("allow");
    ContentSettingsGetCallback callback;
    {
        std::lock_guard<std::mutex> lock(g_content_settings_get_callback_map_mutex);
        auto it = g_content_settings_get_callback_map_.find(resultParam.requestId);
        if (it == g_content_settings_get_callback_map_.end()) {
            LOG(ERROR) << "OnGetCallback requestId not found: " << resultParam.requestId;
            return;
        }

        callback = std::move(it->second);
        g_content_settings_get_callback_map_.erase(it);
    }

    bool result = delegate->OnGet(&param, callback);
    EXPECT_TRUE(result);

    int requestId = 0;
    {
        lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
        EXPECT_FALSE(g_content_settings_get_callback_map_.empty());
        requestId = g_content_settings_get_callback_map_.begin()->first;
    }
    delegate->OnGetCallback(&resultParam);

    {
        lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
        EXPECT_FALSE(g_content_settings_get_callback_map_.count(requestId));
    }
    NWebExtensionContentSettingsCallbackResult nullParam = {};
    delegate->OnGetCallback(&nullParam);
    NWebExtensionContentSettingsCallbackSetResult clearResultParam = {};
    delegate->OnClearCallback(&clearResultParam);
}

TEST_F(NWebExtensionContentSettingsCefDelegateTest, TestOnGetFailure) {
    NWebExtensionContentSettingsGetParam param = {0};
    param.primaryUrl = nullptr;
    NWebExtensionContentSettingsCallbackResult resultParam = {0};
    resultParam.requestId = 0;
    resultParam.detailParam = new NWebExtensionContentSettingsDetail();
    resultParam.detailParam->contentSetting = strdup("allow");
    ContentSettingsGetCallback callback;
    {
        std::lock_guard<std::mutex> lock(g_content_settings_get_callback_map_mutex);
        auto it = g_content_settings_get_callback_map_.find(resultParam.requestId);
        if (it == g_content_settings_get_callback_map_.end()) {
            LOG(ERROR) << "OnGetCallback requestId not found: " << resultParam.requestId;
            return;
        }

        callback = std::move(it->second);
        g_content_settings_get_callback_map_.erase(it);
    }
    bool result = delegate->OnGet(&param, callback);
    EXPECT_FALSE(result);

    {
        lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
        EXPECT_TRUE(g_content_settings_get_callback_map_.empty());
    }
}

TEST_F(NWebExtensionContentSettingsCefDelegateTest, TestOnGetWithNullParam) {
    NWebExtensionContentSettingsCallbackResult resultParam = {0};
    resultParam.requestId = 0;
    resultParam.detailParam = new NWebExtensionContentSettingsDetail();
    resultParam.detailParam->contentSetting = strdup("allow");
    ContentSettingsGetCallback callback;
    {
        std::lock_guard<std::mutex> lock(g_content_settings_get_callback_map_mutex);
        auto it = g_content_settings_get_callback_map_.find(resultParam.requestId);
        if (it == g_content_settings_get_callback_map_.end()) {
            LOG(ERROR) << "OnGetCallback requestId not found: " << resultParam.requestId;
            return;
        }

        callback = std::move(it->second);
        g_content_settings_get_callback_map_.erase(it);
    }
    bool result = delegate->OnGet(nullptr, callback);
    EXPECT_FALSE(result);

    {
        lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
        EXPECT_TRUE(g_content_settings_get_callback_map_.empty());
    }
}

TEST_F(NWebExtensionContentSettingsCefDelegateTest, TestOnGetMultipleCalls) {
    NWebExtensionContentSettingsCallbackResult resultParam = {0};
    NWebExtensionContentSettingsGetParam param = {0};
    param.primaryUrl = strdup("https://example.com");
    param.secondaryUrl = strdup("https://sub.example.com");
    param.type = strdup("cookies");
    param.extensionId = strdup("12345");
    resultParam.requestId = 0;
    resultParam.detailParam = new NWebExtensionContentSettingsDetail();
    resultParam.detailParam->contentSetting = strdup("allow");
    ContentSettingsGetCallback callback;
    {
        std::lock_guard<std::mutex> lock(g_content_settings_get_callback_map_mutex);
        auto it = g_content_settings_get_callback_map_.find(resultParam.requestId);
        if (it == g_content_settings_get_callback_map_.end()) {
            LOG(ERROR) << "OnGetCallback requestId not found: " << resultParam.requestId;
            return;
        }

        callback = std::move(it->second);
        g_content_settings_get_callback_map_.erase(it);
    }
    bool result1 = delegate->OnGet(&param, callback);
    EXPECT_TRUE(result1);

    bool result2 = delegate->OnGet(&param, callback);
    EXPECT_TRUE(result2);

    int requestId1 = 0;
    int requestId2 = 0;
    {
        lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
        auto it = g_content_settings_get_callback_map_.begin();
        requestId1 = it->first;
        ++it;
        requestId2 = it->first;
    }

    EXPECT_NE(requestId1, requestId2);
}

TEST_F(NWebExtensionContentSettingsCefDelegateTest, TestOnGetCallbackStorage) {
    NWebExtensionContentSettingsCallbackResult resultParam = {0};
    NWebExtensionContentSettingsGetParam param = {0};
    param.primaryUrl = strdup("https://example.com");
    param.secondaryUrl = strdup("https://sub.example.com");
    param.type = strdup("cookies");
    param.extensionId = strdup("12345");
    resultParam.requestId = 0;
    resultParam.detailParam = new NWebExtensionContentSettingsDetail();
    resultParam.detailParam->contentSetting = strdup("allow");
    ContentSettingsGetCallback callback;
    {
        std::lock_guard<std::mutex> lock(g_content_settings_get_callback_map_mutex);
        auto it = g_content_settings_get_callback_map_.find(resultParam.requestId);
        if (it == g_content_settings_get_callback_map_.end()) {
            LOG(ERROR) << "OnGetCallback requestId not found: " << resultParam.requestId;
            return;
        }

        callback = std::move(it->second);
        g_content_settings_get_callback_map_.erase(it);
    }
    bool result = delegate->OnGet(&param, callback);
    EXPECT_TRUE(result);
    int requestId = 0;
    {
        lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
        EXPECT_FALSE(g_content_settings_get_callback_map_.empty());
        requestId = g_content_settings_get_callback_map_.begin()->first;
    }
    delegate->OnGetCallback(&resultParam);
    {
        lock_guard<mutex> lock(g_content_settings_get_callback_map_mutex);
        EXPECT_FALSE(g_content_settings_get_callback_map_.count(requestId));
    }
    NWebExtensionContentSettingsCallbackSetResult onSetParam = {};
    delegate->OnSetCallback(&onSetParam);
    onSetParam.error = strdup("error");
    onSetParam.requestId = 0;
    delegate->OnSetCallback(&onSetParam);
    NWebExtensionContentSettingsCallbackSetResult clearResultParam = {};
    clearResultParam.error =  strdup("error");
    clearResultParam.requestId = 0;
    delegate->OnClearCallback(&clearResultParam);
    free(onSetParam.error);
    free(clearResultParam.error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
}  // namespace