// Copyright (c) Huawei Technologies Co., Ltd. 2025. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ARKWEB_CHROMIUM_EXT_COMPONENTS_CAPTIVE_PORTAL_CORE_CAPTIVE_PORTAL_TYPES_OHOS_H_
#define ARKWEB_CHROMIUM_EXT_COMPONENTS_CAPTIVE_PORTAL_CORE_CAPTIVE_PORTAL_TYPES_OHOS_H_

#include "net/traffic_annotation/network_traffic_annotation.h"

namespace captive_portal {

constexpr net::NetworkTrafficAnnotationTag kTrafficAnnotation =
    net::DefineNetworkTrafficAnnotation("captive_portal_service", R"(
        semantics {
          sender: "Captive Portal Service"
          description:
            "Checks if the system is behind a captive portal. To do so, makes"
            "an unlogged, dataless connection to a Google server and checks"
            "the response."
          trigger:
            "It is triggered on multiple cases: It is run on certain SSL "
            "errors (ERR_CONNECTION_TIMED_OUT, ERR_SSL_PROTOCOL_ERROR, and all "
            "SSL interstitials)."
          data: "None."
          destination: GOOGLE_OWNED_SERVICE
        }
        policy {
          cookies_allowed: NO
          setting:
            "Users can enable/disable this feature by toggling 'Use a web "
            "service to resolve network errors' in Chromium settings under "
            "Privacy. This feature is enabled by default."
          chrome_policy {
            AlternateErrorPagesEnabled {
              policy_options {mode: MANDATORY}
              AlternateErrorPagesEnabled: false
            }
          }
        })");

}
#endif  // ARKWEB_CHROMIUM_EXT_COMPONENTS_CAPTIVE_PORTAL_CORE_CAPTIVE_PORTAL_TYPES_OHOS_H_
