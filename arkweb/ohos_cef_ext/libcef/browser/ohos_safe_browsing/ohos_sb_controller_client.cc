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

#include "libcef/browser/ohos_safe_browsing/ohos_sb_controller_client.h"

#include "components/prefs/scoped_user_pref_update.h"
#include "components/safe_browsing/core/common/safe_browsing_prefs.h"
#include "components/security_interstitials/content/settings_page_helper.h"
#include "components/security_interstitials/core/metrics_helper.h"
#include "content/browser/renderer_host/navigation_controller_impl.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/referrer.h"
#include "libcef/browser/ohos_safe_browsing/ohos_sb_malicious_allowlist.h"
#include "libcef/browser/ohos_safe_browsing/ohos_sb_prefs.h"

constexpr char kDefaultPageUrl[] = "about:blank";

SbControllerClient::SbControllerClient(content::WebContents* web_contents,
                                       PrefService* prefs,
                                       const GURL& url,
                                       const std::string& app_locale,
                                       bool incognito_mode)
    : SecurityInterstitialControllerClient(web_contents,
                                           GetMetricsHelper(url),
                                           prefs,
                                           app_locale,
                                           GURL(kDefaultPageUrl),
                                           /*settings_page_helper=*/nullptr),
      web_contents_{web_contents},
      prefs_(prefs),
      app_locale_{app_locale},
      url_(url),
      incognito_mode_(incognito_mode) {}

SbControllerClient::~SbControllerClient() {}

// static
std::unique_ptr<MetricsHelper> SbControllerClient::GetMetricsHelper(
    const GURL& url) {
  MetricsHelper::ReportDetails settings;
  settings.metric_prefix = "oh.safe_browsing";

  return std::make_unique<MetricsHelper>(url, settings, nullptr);
}

void SbControllerClient::GoBack() {
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kEnableNwebEx) &&
      !SecurityInterstitialControllerClient::CanGoBack()) {
    LOG(INFO) << "SbControllerClient::GoBack Close";
    web_contents_->Close();
    return;
  }

  SecurityInterstitialControllerClient::GoBackAfterNavigationCommitted();
  return;
}

void SbControllerClient::Proceed() {
  // With committed interstitials the site has already
  // been added to the allowlist, so reload will proceed.
  Reload();
  return;
}

void SbControllerClient::Reload() {
  if (!web_contents_) {
    return;
  }

  ohos_safe_browsing::MaliciousAllowlist::GetInstance().AddToAllowlist(
      url_.has_host() ? url_.host() : url_.spec(), incognito_mode_);
  web_contents_->GetController().Reload(content::ReloadType::NORMAL, true);
}

PrefService* SbControllerClient::GetPrefService() {
  return prefs_;
}

const std::string& SbControllerClient::GetApplicationLocale() const {
  return app_locale_;
}

const std::string SbControllerClient::GetExtendedReportingPrefName() const {
  return std::string();
}
