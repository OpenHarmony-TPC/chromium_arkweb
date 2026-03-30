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
#include "arkweb/chromium_ext/content/browser/dfx/memory_monitor_render_impl.h"
#include "arkweb/chromium_ext/content/browser/dfx/mojom/dfx_reporting.mojom.h"

#include "base/at_exit.h"
#include "base/functional/bind.h"
#include "base/task/single_thread_task_executor.h"
#include "mojo/core/embedder/embedder.h"

namespace content {
namespace {

class MockDfxReporter : public dfx::mojom::DfxReporter {
 public:
  MockDfxReporter() = default;
  ~MockDfxReporter() override = default;

  void ReportMemInfo(const std::string& sysEventInfoJson) override {
    // Do nothing for fuzzing
  }

  void ReportHiSysEvent(const std::string& eventName, const std::string& sysEventInfoJson) override {
    // Do nothing for fuzzing
  }

  void ReportMemoryLeak(const std::string& type) {
    // Do nothing for fuzzing
  }

  void AddReceiver(mojo::PendingReceiver<dfx::mojom::DfxReporter> receiver) {
    receivers_ = std::move(receiver);
  }

 private:
  mojo::PendingReceiver<dfx::mojom::DfxReporter> receivers_;
};

class MemoryMonitorFuzzer {
 public:
  MemoryMonitorFuzzer(const uint8_t* data, size_t size)
      : data_(data, data + size),
        data_provider_(std::make_unique<FuzzedDataProvider>(data, size)) {}

  void FuzzMemoryMonitor() {
    // Get MemoryMonitorImpl instance
    auto instance = MemoryMonitorImpl::GetInstance();

    // Test IsInitialized before Init
    bool initialized = instance->IsInitialized();

    // Test GetPendingReceiver
    auto& receiver = instance->GetPendingReceiver();
    
    // Bind the receiver to our mock reporter
    mock_reporter_.AddReceiver(std::move(receiver));

    // Test Trigger with random URL
    std::string url = data_provider_->ConsumeRandomLengthString(255);
    instance->Trigger(url);

    // Test IsInitialized after Trigger
    initialized = instance->IsInitialized();

    // Test multiple Trigger calls with different URLs
    for (int i = 0; i < 5; i++) {
      std::string new_url = data_provider_->ConsumeRandomLengthString(255);
      instance->Trigger(new_url);
    }

    // Test multiple GetInstance calls to ensure singleton behavior
    auto instance2 = MemoryMonitorImpl::GetInstance();
    auto instance3 = MemoryMonitorImpl::GetInstance();
    bool same_instances = (instance.get() == instance2.get()) && (instance2.get() == instance3.get());
  }

  std::vector<uint8_t> data_;
  std::unique_ptr<FuzzedDataProvider> data_provider_;
  MockDfxReporter mock_reporter_;
};

struct Environment {
  Environment() {
    mojo::core::Init();
  }

  base::AtExitManager at_exit_manager;
  base::SingleThreadTaskExecutor task_executor;
};

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static Environment* env = new Environment();

  MemoryMonitorFuzzer fuzzer(data, size);
  fuzzer.FuzzMemoryMonitor();

  return 0;
}

}   // namespace content