#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <string>
#include <climits>
#include "base/trace_event/trace_event_ohos.h"

// Fuzz函数
void TraceEventFuzz(const uint8_t* data, size_t size) {
    if (data == nullptr || size == 0) {
        return;
    }

    FuzzedDataProvider dataProvider(data, size);

    // 生成随机字符串作为跟踪名称
    size_t nameLength = dataProvider.ConsumeIntegralInRange<size_t>(1, 256);
    std::string traceName = dataProvider.ConsumeRandomLengthString(nameLength);

    // 测试基本跟踪功能
    StartBytrace(traceName);
    FinishBytrace();

    // 测试异步跟踪功能
    int32_t taskId = dataProvider.ConsumeIntegral<int32_t>();
    StartAsyncBytrace(traceName, taskId);
    FinishAsyncBytrace(traceName, taskId);

    // 测试计数跟踪功能
    int64_t count = dataProvider.ConsumeIntegral<int64_t>();
    CountBytrace(traceName, count);

    // 测试ScopedBytrace
    {
        ScopedBytrace scopedTrace(traceName);
        scopedTrace.SendTraceEvent(traceName);
        // ScopedBytrace的析构函数会自动调用FinishTrace
    }

    // 如果定义了ARKWEB_DFX_TRACING，测试OHOS专用的跟踪功能
#if BUILDFLAG(ARKWEB_DFX_TRACING)
    StartOHOSBytrace(traceName);
    FinishOHOSBytrace();

    CountOHOSBytrace(traceName, count);

    {
        ScopedOHOSBytrace scopedOHOSTrace(traceName);
        scopedOHOSTrace.SendOHOSTraceEvent(traceName);
        // ScopedOHOSBytrace的析构函数会自动调用FinishOHOSBytrace
    }
#endif

    // 边界值测试
    {
        // 测试空字符串
        std::string emptyTraceName = "";
        StartBytrace(emptyTraceName);
        FinishBytrace();

        // 测试最大长度字符串
        std::string maxLengthTraceName = dataProvider.ConsumeRandomLengthString(256);
        StartBytrace(maxLengthTraceName);
        FinishBytrace();

        // 测试特殊字符
        std::string specialCharTraceName = "!@#$%^&*()";
        StartBytrace(specialCharTraceName);
        FinishBytrace();

        // 测试包含中文字符的字符串
        std::string chineseTraceName = "测试跟踪名称";
        StartBytrace(chineseTraceName);
        FinishBytrace();
    }

    // 异常情况测试
    {
        // 测试极小值的taskId
        int32_t minTaskId = INT32_MIN;
        StartAsyncBytrace(traceName, minTaskId);
        FinishAsyncBytrace(traceName, minTaskId);

        // 测试极大值的taskId
        int32_t maxTaskId = INT32_MAX;
        StartAsyncBytrace(traceName, maxTaskId);
        FinishAsyncBytrace(traceName, maxTaskId);

        // 测试极小值的count
        int64_t minCount = INT64_MIN;
        CountBytrace(traceName, minCount);

        // 测试极大值的count
        int64_t maxCount = INT64_MAX;
        CountBytrace(traceName, maxCount);

        // 测试负数count
        int64_t negativeCount = -1000;
        CountBytrace(traceName, negativeCount);
    }

    // 额外的边界测试
    {
        // 测试非常长的字符串
        std::string veryLongTraceName(1000, 'a');
        StartBytrace(veryLongTraceName);
        FinishBytrace();

        // 测试包含各种控制字符的字符串
        std::string controlCharTraceName = "\x01\x02\x03\x04\x05";
        StartBytrace(controlCharTraceName);
        FinishBytrace();
    }

    // 测试各种参数组合
    {
        // 测试不同的taskId组合
        int32_t testTaskIds[] = {0, 1, -1, 100, -100, 1000, -1000};
        for (int32_t testTaskId : testTaskIds) {
            StartAsyncBytrace(traceName, testTaskId);
            FinishAsyncBytrace(traceName, testTaskId);
        }

        // 测试不同的count组合
        int64_t testCounts[] = {0, 1, -1, 100, -100, 1000, -1000, INT64_MIN, INT64_MAX};
        for (int64_t testCount : testCounts) {
            CountBytrace(traceName, testCount);
        }
    }
}


// Fuzzer入口函数
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    TraceEventFuzz(data, size);
    return 0;
}