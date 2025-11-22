// Copyright (c) 2023 Huawei Device Co., Ltd.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef COMPONENTS_POLICY_CORE_COMMON_POLICY_LOADER_OHOS_H_
#define COMPONENTS_POLICY_CORE_COMMON_POLICY_LOADER_OHOS_H_

#include "base/task/sequenced_task_runner.h"
#include "cef/ohos_cef_ext/libcef/browser/policy/browser_policy_handler.h"
#include "components/policy/core/common/async_policy_loader.h"
#include "components/policy/policy_export.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/enterprise_device_management_adapter.h"
#include "base/memory/raw_ptr.h"

namespace base {
class Value;
}

namespace policy {

class PolicyChangedEventCallback;

void RegisterBrowserPolicyProfilePrefs(PrefRegistrySimple* registry);

class POLICY_EXPORT PolicyLoaderOhos : public AsyncPolicyLoader {
 public:
  PolicyLoaderOhos(scoped_refptr<base::SequencedTaskRunner> task_runner);
  PolicyLoaderOhos(const PolicyLoaderOhos&) = delete;
  PolicyLoaderOhos& operator=(const PolicyLoaderOhos&) = delete;
  ~PolicyLoaderOhos() override;

  // AsyncPolicyLoader implementation.
  void InitOnBackgroundThread() override;
  PolicyBundle Load() override;

  void TryChoosePolicySource();
  static bool ParsePolicy(const std::string& json, PolicyBundle* bundle);
  static void ParseExtensionsPolicy(const base::Value* policies,
                                    PolicyBundle* bundle);

 private:
  friend class PolicyLoaderOhosTest;
  std::string ReadTestPolices();

  std::shared_ptr<PolicyChangedEventCallback> event_callback_;
  bool use_browser_policy_ = false;
  bool policy_source_choosed_ = false;
};

class PolicyChangedEventCallback
    : public policy::BrowserPolicyHandler::Observer,
      public OHOS::NWeb::EdmPolicyChangedEventCallbackAdapter {
 public:
  PolicyChangedEventCallback(PolicyLoaderOhos* loader);

  // policy::BrowserPolicyHandler::Observer overrides
  void OnPolicyChanged() override;

  // OHOS::NWeb::EdmPolicyChangedEventCallbackAdapter overrides
  void Changed() override;

 private:
  friend class PolicyChangedEventCallbackTest;
  void OnPolicyChangedImpl();
  raw_ptr<PolicyLoaderOhos> loader_;
};

}  // namespace policy

#endif  // COMPONENTS_POLICY_CORE_COMMON_POLICY_LOADER_OHOS_H_
