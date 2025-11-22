// Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef COMPONENTS_MEMORY_PRESSURE_SYSTEM_MEMORY_PRESSURE_EVALUATOR_OHOS_H_
#define COMPONENTS_MEMORY_PRESSURE_SYSTEM_MEMORY_PRESSURE_EVALUATOR_OHOS_H_

#include "base/process/process_metrics.h"
#include "components/memory_pressure/system_memory_pressure_evaluator.h"

namespace memory_pressure {
namespace ohos {

// FIXME: Specific functions will be adapted later.
// Ohos memory pressure voter. Because there is no OS provided signal this
// polls at a low frequency, and applies internal hysteresis.
class SystemMemoryPressureEvaluator
    : public memory_pressure::SystemMemoryPressureEvaluator {
 protected:
  // This is just a wrapper for base:: function;
  // declared as virtual for unit testing
  virtual bool GetSystemMemoryInfo(base::SystemMemoryInfoKB* mem_info);
};

}  // namespace ohos
}  // namespace memory_pressure

#endif  // COMPONENTS_MEMORY_PRESSURE_SYSTEM_MEMORY_PRESSURE_EVALUATOR_OHOS_H_
