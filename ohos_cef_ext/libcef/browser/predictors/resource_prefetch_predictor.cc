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

#include "ohos_cef_ext/libcef/browser/predictors/resource_prefetch_predictor.h"

#include <map>
#include <set>
#include <utility>

#include "base/functional/bind.h"
#include "base/metrics/histogram_macros.h"
#include "base/rand_util.h"
#include "base/strings/string_number_conversions.h"
#include "base/time/time.h"
#include "base/trace_event/trace_event.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/web_contents.h"
#include "url/origin.h"

using content::BrowserThread;

namespace ohos_predictors {

PreconnectRequest::PreconnectRequest(
    const url::Origin& origin,
    int num_sockets,
    const net::NetworkAnonymizationKey& network_anonymization_key)
    : origin(origin),
      num_sockets(num_sockets),
      network_anonymization_key(network_anonymization_key) {
  DCHECK_GE(num_sockets, 0);
}

PreconnectPrediction::PreconnectPrediction() = default;
PreconnectPrediction::PreconnectPrediction(
    const PreconnectPrediction& prediction) = default;
PreconnectPrediction::~PreconnectPrediction() = default;

}  // namespace ohos_predictors
