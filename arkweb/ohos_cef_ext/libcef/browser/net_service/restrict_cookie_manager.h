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

#ifndef CEF_LIBCEF_BROWSER_NET_SERVICE_RESTRICT_COOKIE_MANAGER_H_
#define CEF_LIBCEF_BROWSER_NET_SERVICE_RESTRICT_COOKIE_MANAGER_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "include/cef_cookie.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "services/network/public/mojom/restricted_cookie_manager.mojom.h"

class GURL;

// A RestrictedCookieManager which conditionally proxies to an underlying
// RestrictedCookieManager, first consulting WebView's cookie settings.
class ProxyingRestrictedCookieManager
    : public network::mojom::RestrictedCookieManager {
 public:
  // Creates a ProxyingRestrictedCookieManager that lives on IO thread,
  // binding it to handle communications from |receiver|. The requests will be
  // delegated to |underlying_rcm|. The resulting object will be owned by the
  // pipe corresponding to |request| and will in turn own |underlying_rcm|.
  //
  // Expects to be called on the UI thread.
  static void CreateAndBind(
      mojo::PendingRemote<network::mojom::RestrictedCookieManager>
          underlying_rcm,
      bool is_service_worker,
      int process_id,
      int frame_id,
      mojo::PendingReceiver<network::mojom::RestrictedCookieManager> receiver);

  ~ProxyingRestrictedCookieManager() override;

  // network::mojom::RestrictedCookieManager interface:
  void GetAllForUrl(const GURL& url,
                    const net::SiteForCookies& site_for_cookies,
                    const url::Origin& top_frame_origin,
                    bool has_storage_access,
                    network::mojom::CookieManagerGetOptionsPtr options,
                    GetAllForUrlCallback callback) override;
  void SetCanonicalCookie(const net::CanonicalCookie& cookie,
                          const GURL& url,
                          const net::SiteForCookies& site_for_cookies,
                          const url::Origin& top_frame_origin,
                          bool has_storage_access,
                          net::CookieInclusionStatus status,
                          SetCanonicalCookieCallback callback) override;
#if BUILDFLAG(IS_ARKWEB)
  void RegisterCookieChangeObserver(
      const GURL& url,
      const net::SiteForCookies& site_for_cookies,
      const url::Origin& top_frame_origin,
      bool has_storage_access,
      mojo::ScopedSharedBufferHandle buffer,
      RegisterCookieChangeObserverCallback callback) override;
#endif
  void AddChangeListener(
      const GURL& url,
      const net::SiteForCookies& site_for_cookies,
      const url::Origin& top_frame_origin,
      bool has_storage_access,
      mojo::PendingRemote<network::mojom::CookieChangeListener> listener,
      AddChangeListenerCallback callback) override;

  void SetCookieFromString(const GURL& url,
                           const net::SiteForCookies& site_for_cookies,
                           const url::Origin& top_frame_origin,
                           bool has_storage_access,
                           const std::string& cookie,
                           SetCookieFromStringCallback callback) override;

  void GetCookiesString(const GURL& url,
                        const net::SiteForCookies& site_for_cookies,
                        const url::Origin& top_frame_origin,
                        bool has_storage_access,
                        GetCookiesStringCallback callback) override;

#if BUILDFLAG(IS_ARKWEB)
  void GetCookiesStringAndExpiryDate(
      const GURL& url,
      const net::SiteForCookies& site_for_cookies,
      const url::Origin& top_frame_origin,
      bool has_storage_access,
      GetCookiesStringAndExpiryDateCallback callback) override;
#endif

  void CookiesEnabledFor(const GURL& url,
                         const net::SiteForCookies& site_for_cookies,
                         const url::Origin& top_frame_origin,
                         bool has_storage_access,
                         CookiesEnabledForCallback callback) override;

  bool AllowCookies(const GURL& url,
                    const net::SiteForCookies& site_for_cookies) const;

 private:
  ProxyingRestrictedCookieManager(
      mojo::PendingRemote<network::mojom::RestrictedCookieManager>
          underlying_restricted_cookie_manager,
      bool is_service_worker,
      int process_id,
      int frame_id);

  static void CreateAndBindOnIoThread(
      mojo::PendingRemote<network::mojom::RestrictedCookieManager>
          underlying_rcm,
      bool is_service_worker,
      int process_id,
      int frame_id,
      mojo::PendingReceiver<network::mojom::RestrictedCookieManager> receiver);

  mojo::Remote<network::mojom::RestrictedCookieManager>
      underlying_restricted_cookie_manager_;
  base::WeakPtrFactory<ProxyingRestrictedCookieManager> weak_factory_{this};
};

#endif  // CEF_LIBCEF_BROWSER_NET_SERVICE_RESTRICT_COOKIE_MANAGER_H_
