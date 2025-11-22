// Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "ohos_cef_ext/libcef/browser/predictors/loading_predictor_config.h"

namespace ohos_predictors {

// Returns whether the speculative preconnect feature is enabled.
bool IsPreconnectFeatureEnabled() {
  return true;
}

bool IsLoadingPredictorEnabled(content::BrowserContext* context) {
  return IsPreconnectFeatureEnabled();
}

bool IsPreconnectAllowed(content::BrowserContext* context) {
  if (!IsPreconnectFeatureEnabled()) {
    return false;
  }

  return true;
}

LoadingPredictorConfig::LoadingPredictorConfig()
    : max_navigation_lifetime_seconds(60),
      max_hosts_to_track(100),
      max_origins_per_entry(50),
      max_consecutive_misses(3),
      max_redirect_consecutive_misses(5),
      flush_data_to_disk_delay_seconds(30) {}

LoadingPredictorConfig::LoadingPredictorConfig(
    const LoadingPredictorConfig& other) = default;

LoadingPredictorConfig::~LoadingPredictorConfig() = default;

}  // namespace ohos_predictors
