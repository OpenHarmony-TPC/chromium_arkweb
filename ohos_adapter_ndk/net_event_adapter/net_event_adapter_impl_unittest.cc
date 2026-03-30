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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "arkweb/ohos_adapter_ndk/mock_ndk_api/include/mock_ndk_api.h"
#define private public
#include "arkweb/ohos_adapter_ndk/net_event_adapter/net_event_adapter_impl.h"
#undef private

using namespace MockNdkApi;
using namespace OHOS::NWeb;
using ::testing::_;
using ::testing::Return;
using ::testing::Test;
namespace {
const int32_t DEFAULT_VALUE = -1;
static const char* COMMON_EVENT_KEY_NET_TYPE = "NetType";
}  // namespace

struct CArrParameters {
  int32_t netType;
};

typedef struct CommonEvent_RcvData {
  std::string event;
  std::string bundleName;
  int32_t code;
  std::string data;
  CArrParameters* parameters = nullptr;
} CommonEvent_RcvData;

class MockNetCommonEventListener : public NetCommonEventListener {
 public:
  MOCK_METHOD(void,
              OnConnectivityChanged,
              (NetBearType, NetConnState),
              (override));
};

class NetEventAdapterImplTest : public Test {
 protected:
  void SetUp() override { NetEventAdapterImpl::commonEventListener_ = nullptr; }

  void TearDown() override {
    NetEventAdapterImpl::commonEventListener_ = nullptr;
    g_mock_OH_CommonEvent_GetEventFromRcvData = nullptr;
    g_mock_OH_CommonEvent_CreateSubscribeInfo = nullptr;
    g_mock_OH_CommonEvent_CreateSubscriber = nullptr;
    g_mock_OH_CommonEvent_Subscribe = nullptr;
  }
  void SetType(bool type) {
    MockNetCommonEventSupport::bGetParameters = true;
    MockNetCommonEventSupport::bHasKey = true;
    MockNetCommonEventSupport::bGetInt = true;
    MockNetCommonEventSupport::bGetCode = true;
    MockNetCommonEventSupport::bGetCapacity = true;
    MockNetCommonEventSupport::bGetPluggedType = true;
  }
  std::shared_ptr<MockNetCommonEventListener> g_mockListener;
};

TEST_F(NetEventAdapterImplTest, OnReceiveEvent_001) {
  CommonEvent_RcvData data;

  g_mock_OH_CommonEvent_GetEventFromRcvData =
      [](const CommonEvent_RcvData* rcvData) { return nullptr; };

  ASSERT_NO_FATAL_FAILURE(NetEventAdapterImpl::OnReceiveEvent(&data));
}

TEST_F(NetEventAdapterImplTest, OnReceiveEvent_002) {
  SetType(true);
  CommonEvent_RcvData data;

  g_mock_OH_CommonEvent_GetEventFromRcvData =
      [](const CommonEvent_RcvData* rcvData) { return "OTHER_EVENT"; };

  ASSERT_NO_FATAL_FAILURE(NetEventAdapterImpl::OnReceiveEvent(&data));
}

TEST_F(NetEventAdapterImplTest, OnReceiveEvent_003) {
  SetType(true);
  CommonEvent_RcvData data;
  g_mock_OH_CommonEvent_GetEventFromRcvData =
      [](const CommonEvent_RcvData* rcvData) {
        return COMMON_EVENT_CONNECTIVITY_CHANGE;
      };
  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetParametersFromRcvData(&data))
      .WillOnce(Return(nullptr));

  ASSERT_NO_FATAL_FAILURE(NetEventAdapterImpl::OnReceiveEvent(&data));
}

TEST_F(NetEventAdapterImplTest, OnReceiveEvent_004) {
  SetType(true);
  CommonEvent_RcvData data;
  g_mock_OH_CommonEvent_GetEventFromRcvData =
      [](const CommonEvent_RcvData* rcvData) {
        return COMMON_EVENT_CONNECTIVITY_CHANGE;
      };
  static int dummyParam;
  CommonEvent_Parameters* mockPara =
      reinterpret_cast<CommonEvent_Parameters*>(&dummyParam);
  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetParametersFromRcvData(&data))
      .WillOnce(Return(mockPara));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_HasKeyInParameters(_, COMMON_EVENT_KEY_NET_TYPE))
      .WillOnce(Return(false));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetCodeFromRcvData(&data))
      .WillOnce(Return(1));

  ASSERT_NO_FATAL_FAILURE(NetEventAdapterImpl::OnReceiveEvent(&data));
}

TEST_F(NetEventAdapterImplTest, OnReceiveEvent_005) {
  SetType(true);
  CommonEvent_RcvData data;
  g_mock_OH_CommonEvent_GetEventFromRcvData =
      [](const CommonEvent_RcvData* rcvData) {
        return COMMON_EVENT_CONNECTIVITY_CHANGE;
      };
  static int dummyParam;
  CommonEvent_Parameters* mockPara =
      reinterpret_cast<CommonEvent_Parameters*>(&dummyParam);
  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetParametersFromRcvData(&data))
      .WillOnce(Return(mockPara));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_HasKeyInParameters(_, COMMON_EVENT_KEY_NET_TYPE))
      .WillOnce(Return(true));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetIntFromParameters(_, COMMON_EVENT_KEY_NET_TYPE, DEFAULT_VALUE))
      .WillOnce(Return(DEFAULT_VALUE));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetCodeFromRcvData(&data))
      .WillOnce(Return(1));

  g_mockListener = std::make_shared<MockNetCommonEventListener>();
  NetEventAdapterImpl::commonEventListener_ = g_mockListener;
  EXPECT_CALL(*g_mockListener, OnConnectivityChanged(_, _)).Times(0);

  ASSERT_NO_FATAL_FAILURE(NetEventAdapterImpl::OnReceiveEvent(&data));
}

TEST_F(NetEventAdapterImplTest, OnReceiveEvent_006) {
  SetType(true);
  CommonEvent_RcvData data;
  g_mock_OH_CommonEvent_GetEventFromRcvData =
      [](const CommonEvent_RcvData* rcvData) {
        return COMMON_EVENT_CONNECTIVITY_CHANGE;
      };
  static int dummyParam;
  CommonEvent_Parameters* mockPara =
      reinterpret_cast<CommonEvent_Parameters*>(&dummyParam);
  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetParametersFromRcvData(&data))
      .WillOnce(Return(mockPara));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_HasKeyInParameters(_, COMMON_EVENT_KEY_NET_TYPE))
      .WillOnce(Return(true));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetIntFromParameters(_, COMMON_EVENT_KEY_NET_TYPE, DEFAULT_VALUE))
      .WillOnce(Return(1));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetCodeFromRcvData(&data))
      .WillOnce(Return(2));

  NetEventAdapterImpl::commonEventListener_ = nullptr;
  ASSERT_NO_FATAL_FAILURE(NetEventAdapterImpl::OnReceiveEvent(&data));
}

TEST_F(NetEventAdapterImplTest, OnReceiveEvent_007) {
  SetType(true);
  CommonEvent_RcvData data;
  g_mock_OH_CommonEvent_GetEventFromRcvData =
      [](const CommonEvent_RcvData* rcvData) {
        return COMMON_EVENT_CONNECTIVITY_CHANGE;
      };
  static int dummyParam;
  CommonEvent_Parameters* mockPara =
      reinterpret_cast<CommonEvent_Parameters*>(&dummyParam);
  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetParametersFromRcvData(&data))
      .WillOnce(Return(mockPara));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_HasKeyInParameters(_, COMMON_EVENT_KEY_NET_TYPE))
      .WillOnce(Return(true));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetIntFromParameters(_, COMMON_EVENT_KEY_NET_TYPE,
                                                  DEFAULT_VALUE))
      .WillOnce(Return(1));

  EXPECT_CALL(MockNetCommonEventSupport::GetInstance(),
              OH_CommonEvent_GetCodeFromRcvData(&data))
      .WillOnce(Return(2));

  g_mockListener = std::make_shared<MockNetCommonEventListener>();
  NetEventAdapterImpl::commonEventListener_ = g_mockListener;

  EXPECT_CALL(*g_mockListener,
              OnConnectivityChanged(NetBearType(1), NetConnState(2)))
      .Times(1);

  ASSERT_NO_FATAL_FAILURE(NetEventAdapterImpl::OnReceiveEvent(&data));
}

TEST_F(NetEventAdapterImplTest, UnRegisterCommonEvent_001) {
  NetEventAdapterImpl::commonEventSubscriber_ = nullptr;

  EXPECT_FALSE(NetEventAdapterImpl::UnRegisterCommonEvent());
}

TEST_F(NetEventAdapterImplTest, UnRegisterCommonEvent_002) {
  static int dummySubscriber;
  CommonEvent_Subscriber* mockSubscriber =
      reinterpret_cast<CommonEvent_Subscriber*>(&dummySubscriber);

  NetEventAdapterImpl::commonEventSubscriber_ = mockSubscriber;

  g_mock_OH_CommonEvent_UnSubscribe =
      [](const CommonEvent_Subscriber* subscriber) {
        return COMMONEVENT_ERR_INVALID_PARAMETER;
      };

  EXPECT_FALSE(NetEventAdapterImpl::UnRegisterCommonEvent());
}

TEST_F(NetEventAdapterImplTest, UnRegisterCommonEvent_003) {
  static int dummySubscriber;
  CommonEvent_Subscriber* mockSubscriber =
      reinterpret_cast<CommonEvent_Subscriber*>(&dummySubscriber);

  NetEventAdapterImpl::commonEventSubscriber_ = mockSubscriber;

  g_mock_OH_CommonEvent_UnSubscribe =
      [](const CommonEvent_Subscriber* subscriber) {
        return COMMONEVENT_ERR_OK;
      };
  g_mock_OH_CommonEvent_DestroySubscribeInfo =
      [](CommonEvent_SubscribeInfo* info) {};
  g_mock_OH_CommonEvent_DestroySubscriber =
      [](CommonEvent_Subscriber* subscriber) {};
  EXPECT_TRUE(NetEventAdapterImpl::UnRegisterCommonEvent());
}

TEST_F(NetEventAdapterImplTest, RegisterCommonEventListener_001) {
  NetEventAdapterImpl adapter;

  std::shared_ptr<NetCommonEventListener> nullListener = nullptr;

  NetEventAdapterImpl::commonEventListener_ = nullptr;

  adapter.RegisterCommonEventListener(nullListener);

  EXPECT_EQ(NetEventAdapterImpl::commonEventListener_, nullptr);
}

TEST_F(NetEventAdapterImplTest, RegisterCommonEventListener_002) {
  NetEventAdapterImpl adapter;

  NetEventAdapterImpl::commonEventSubscriber_ = nullptr;
  NetEventAdapterImpl::commonEventListener_ = nullptr;

  auto mockListener = std::make_shared<MockNetCommonEventListener>();

  g_mock_OH_CommonEvent_CreateSubscribeInfo =
      [](const char*[], int32_t) -> CommonEvent_SubscribeInfo* {
    static int dummy;
    return reinterpret_cast<CommonEvent_SubscribeInfo*>(&dummy);
  };

  g_mock_OH_CommonEvent_CreateSubscriber =
      [](const CommonEvent_SubscribeInfo*,
         CommonEvent_ReceiveCallback) -> CommonEvent_Subscriber* {
    static int dummy;
    return reinterpret_cast<CommonEvent_Subscriber*>(&dummy);
  };

  g_mock_OH_CommonEvent_Subscribe = [](const CommonEvent_Subscriber*) {
    return COMMONEVENT_ERR_OK;
  };

  adapter.RegisterCommonEventListener(mockListener);

  EXPECT_EQ(NetEventAdapterImpl::commonEventListener_, mockListener);
  EXPECT_NE(NetEventAdapterImpl::commonEventSubscriber_, nullptr);
}

TEST_F(NetEventAdapterImplTest, RegisterCommonEventListener_003) {
  NetEventAdapterImpl adapter;

  NetEventAdapterImpl::commonEventSubscriber_ = nullptr;
  NetEventAdapterImpl::commonEventListener_ = nullptr;

  auto mockListener = std::make_shared<MockNetCommonEventListener>();

  g_mock_OH_CommonEvent_CreateSubscribeInfo =
      [](const char*[], int32_t) -> CommonEvent_SubscribeInfo* {
    return nullptr;
  };

  g_mock_OH_CommonEvent_CreateSubscriber = nullptr;
  g_mock_OH_CommonEvent_Subscribe = nullptr;

  adapter.RegisterCommonEventListener(mockListener);

  EXPECT_EQ(NetEventAdapterImpl::commonEventListener_, mockListener);
  EXPECT_EQ(NetEventAdapterImpl::commonEventSubscriber_, nullptr);
}

TEST_F(NetEventAdapterImplTest, RegisterCommonEventListener_004) {
  NetEventAdapterImpl adapter;

  static int dummySubscriber;
  NetEventAdapterImpl::commonEventSubscriber_ =
      reinterpret_cast<CommonEvent_Subscriber*>(&dummySubscriber);
  NetEventAdapterImpl::commonEventListener_ = nullptr;

  auto mockListener = std::make_shared<MockNetCommonEventListener>();

  g_mock_OH_CommonEvent_CreateSubscribeInfo = nullptr;
  g_mock_OH_CommonEvent_CreateSubscriber = nullptr;
  g_mock_OH_CommonEvent_Subscribe = nullptr;

  adapter.RegisterCommonEventListener(mockListener);

  EXPECT_EQ(NetEventAdapterImpl::commonEventListener_, mockListener);
  EXPECT_EQ(NetEventAdapterImpl::commonEventSubscriber_,
            reinterpret_cast<CommonEvent_Subscriber*>(&dummySubscriber));
}