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

#include "ohos_cef_ext/libcef/browser/predictors/loading_predictor_factory.h"

#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "ohos_cef_ext/libcef/browser/predictors/loading_predictor.h"

namespace ohos_predictors {

// static
LoadingPredictor* LoadingPredictorFactory::GetForBrowserContext(
    content::BrowserContext* context) {
  return static_cast<LoadingPredictor*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
LoadingPredictorFactory* LoadingPredictorFactory::GetInstance() {
  return base::Singleton<LoadingPredictorFactory>::get();
}

LoadingPredictorFactory::LoadingPredictorFactory()
    : BrowserContextKeyedServiceFactory(
          "LoadingPredictor",
          BrowserContextDependencyManager::GetInstance()) {}

LoadingPredictorFactory::~LoadingPredictorFactory() {}

KeyedService* LoadingPredictorFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  if (!IsLoadingPredictorEnabled(context)) {
    return nullptr;
  }

  return new LoadingPredictor(LoadingPredictorConfig(), context);
}

}  // namespace ohos_predictors
