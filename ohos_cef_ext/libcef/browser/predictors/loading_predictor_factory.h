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

#ifndef CEF_LIBCEF_BROWSER_PREDICTORS_LOADING_PREDICTOR_FACTORY_H_
#define CEF_LIBCEF_BROWSER_PREDICTORS_LOADING_PREDICTOR_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace ohos_predictors {

class LoadingPredictor;

class LoadingPredictorFactory : public BrowserContextKeyedServiceFactory {
 public:
  static LoadingPredictor* GetForBrowserContext(
      content::BrowserContext* context);
  static LoadingPredictorFactory* GetInstance();

  LoadingPredictorFactory(const LoadingPredictorFactory&) = delete;
  LoadingPredictorFactory& operator=(const LoadingPredictorFactory&) = delete;

 private:
  friend struct base::DefaultSingletonTraits<LoadingPredictorFactory>;

  LoadingPredictorFactory();
  ~LoadingPredictorFactory() override;

  // BrowserContextKeyedServiceFactory:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;
};

}  // namespace ohos_predictors

#endif  // CEF_LIBCEF_BROWSER_PREDICTORS_LOADING_PREDICTOR_FACTORY_H_
