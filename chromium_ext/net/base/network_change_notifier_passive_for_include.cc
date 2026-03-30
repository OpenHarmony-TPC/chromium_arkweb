/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

namespace {

#if BUILDFLAG(ARKWEB_NETWORK_BASE)
net::NetworkChangeNotifier::ConnectionType ConvertOhosConnTypeToNetBaseConnType(
    const OHOS::NWeb::NetConnectType& netConnectType) {
  return static_cast<net::NetworkChangeNotifier::ConnectionType>(
      netConnectType);
}

net::NetworkChangeNotifier::ConnectionSubtype
ConvertOhosConnSubtypeToNetBaseConnSubtype(
    const OHOS::NWeb::NetConnectSubtype& subtype) {
  return static_cast<net::NetworkChangeNotifier::ConnectionSubtype>(subtype);
}

#if BUILDFLAG(IS_ARKWEB_EXT)
class VpnListenerImpl : public OHOS::NWeb::VpnListener {
 public:
  VpnListenerImpl(net::NetworkChangeNotifierPassive* network_change_notifier)
      : network_change_notifier_(network_change_notifier) {}
  virtual ~VpnListenerImpl() = default;
  void OnAvailable() override;
  void OnLost() override;

 private:
  raw_ptr<net::NetworkChangeNotifierPassive> network_change_notifier_ = nullptr;
};

void VpnListenerImpl::OnAvailable()
{
  LOG(INFO) << "ohos_network Vpn OnAvailable";
  network_change_notifier_->OnVpnAvailable();
}

void VpnListenerImpl::OnLost()
{
  LOG(INFO) << "ohos_network Vpn OnLost";
  network_change_notifier_->OnVpnLost();
}
#endif

class NetConnCallbackImpl : public OHOS::NWeb::NetConnCallback {
 public:
  NetConnCallbackImpl(
      net::NetworkChangeNotifierPassive* network_change_notifier_posix)
      : network_change_notifier_posix_(network_change_notifier_posix) {}
  virtual ~NetConnCallbackImpl() = default;
  int32_t NetAvailable() override;
  int32_t NetCapabilitiesChange(
      const OHOS::NWeb::NetConnectType& netConnectType,
      const OHOS::NWeb::NetConnectSubtype& netConnectSubtype) override;
  int32_t NetConnectionPropertiesChange() override;
  int32_t NetUnavailable() override;
  int32_t OnNetCapabilitiesChanged(
      const std::shared_ptr<OHOS::NWeb::NetCapabilitiesAdapter> capabilities)
      override;
  int32_t OnNetConnectionPropertiesChanged(
      const std::shared_ptr<OHOS::NWeb::NetConnectionPropertiesAdapter>
          properties) override;
  void BindDnsToNetwork(int32_t network_for_dns);

 private:
  void ConnectionTypeChangedTo(int32_t net_id,
                               OHOS::NWeb::NetConnectType type,
                               OHOS::NWeb::NetConnectSubtype subtype);

  raw_ptr<net::NetworkChangeNotifierPassive> network_change_notifier_posix_ = nullptr;
  std::shared_ptr<OHOS::NWeb::NetCapabilitiesAdapter> capabilities_ = nullptr;
  std::shared_ptr<OHOS::NWeb::NetConnectionPropertiesAdapter> properties_ =
      nullptr;
  int32_t net_id_ = -1;
  int32_t network_for_dns_ = -1;
  OHOS::NWeb::NetConnectType type_ =
      OHOS::NWeb::NetConnectType::CONNECTION_UNKNOWN;
  OHOS::NWeb::NetConnectSubtype subtype_ =
      OHOS::NWeb::NetConnectSubtype::SUBTYPE_UNKNOWN;
  bool IsSameAddrList(const std::vector<std::string>& newList,
                      const std::vector<std::string>& oldList);
};

int32_t NetConnCallbackImpl::NetAvailable() {
  LOG(INFO) << "ohos_network NetAvailable";
  capabilities_ = nullptr;
  properties_ = nullptr;
  return 0;
}

int32_t NetConnCallbackImpl::NetCapabilitiesChange(
    const OHOS::NWeb::NetConnectType& netConnectType,
    const OHOS::NWeb::NetConnectSubtype& netConnectSubtype) {
  LOG(INFO) << "ohos_network NetCapabilitiesChange "
            << static_cast<int>(netConnectType);
  if (network_change_notifier_posix_) {
    network_change_notifier_posix_->OnConnectionChanged(
        ConvertOhosConnTypeToNetBaseConnType(netConnectType));
    network_change_notifier_posix_->OnConnectionSubtypeChanged(
        ConvertOhosConnTypeToNetBaseConnType(netConnectType),
        ConvertOhosConnSubtypeToNetBaseConnSubtype(netConnectSubtype));
  }
  return 0;
}

int32_t NetConnCallbackImpl::NetConnectionPropertiesChange() {
  if (network_change_notifier_posix_) {
    network_change_notifier_posix_->OnDNSChanged();
    network_change_notifier_posix_->OnIPAddressChanged(
        net::NetworkChangeNotifier::IP_ADDRESS_CHANGE_NORMAL);
  }
  return 0;
}

int32_t NetConnCallbackImpl::NetUnavailable() {
  LOG(INFO) << "ohos_network NetUnavailable";
  capabilities_ = nullptr;
  properties_ = nullptr;
  if (network_change_notifier_posix_) {
    ConnectionTypeChangedTo(-1, OHOS::NWeb::NetConnectType::CONNECTION_NONE,
                            OHOS::NWeb::NetConnectSubtype::SUBTYPE_NONE);
  }
  return 0;
}

int32_t NetConnCallbackImpl::OnNetCapabilitiesChanged(
    const std::shared_ptr<OHOS::NWeb::NetCapabilitiesAdapter> capabilities) {
  capabilities_ = capabilities;
  if (capabilities_) {
    LOG(INFO) << "ohos_network NetCapabilitiesChange, net_id "
              << capabilities_->GetNetId() << ", connectType "
              << (int)capabilities_->GetConnectType() << ", subtype "
              << (int)capabilities_->GetConnectSubtype();
  }
  if (network_change_notifier_posix_ && capabilities_ && properties_) {
    ConnectionTypeChangedTo(capabilities_->GetNetId(),
                            capabilities_->GetConnectType(),
                            capabilities_->GetConnectSubtype());
  }
  return 0;
}

int32_t NetConnCallbackImpl::OnNetConnectionPropertiesChanged(
    const std::shared_ptr<OHOS::NWeb::NetConnectionPropertiesAdapter>
        properties) {
  properties_ = properties;
  if (properties_) {
    LOG(INFO) << "ohos_network NetConnectionPropertiesChange, net_id "
              << properties_->GetNetId();
  }
  if (network_change_notifier_posix_ && capabilities_ && properties_) {
    ConnectionTypeChangedTo(properties_->GetNetId(),
                            capabilities_->GetConnectType(),
                            capabilities_->GetConnectSubtype());
  }
  return 0;
}

void NetConnCallbackImpl::BindDnsToNetwork(int32_t network_for_dns) {
  LOG(INFO) << "NetConnCallbackImpl::BindDnsToNetwork, network_for_dns "
            << network_for_dns;
  network_for_dns_ = network_for_dns;
#if BUILDFLAG(IS_ARKWEB_EXT) && BUILDFLAG(ARKWEB_EXT_NETWORK_CONNECTION)
  if (!network_change_notifier_posix_) {
      return;
  }

  if (network_for_dns_ == - 1) {
    network_change_notifier_posix_->SetNetAddrList(std::vector<std::string>());
    return;
  }
  auto new_addr_list = network_change_notifier_posix_->GetNetAddrListByNetId(network_for_dns_);
  network_change_notifier_posix_->SetNetAddrList(new_addr_list);
#endif
}

bool NetConnCallbackImpl::IsSameAddrList(const std::vector<std::string>& newList,
                                         const std::vector<std::string>& oldList) {
  if (newList.size() != oldList.size()) {
    return false;
  }
  std::vector<std::string> sortedNewList = newList;
  std::vector<std::string> sortedOldList = oldList;
  std::sort(sortedNewList.begin(), sortedNewList.end());
  std::sort(sortedOldList.begin(), sortedOldList.end());
  return sortedNewList == sortedOldList;
}

void NetConnCallbackImpl::ConnectionTypeChangedTo(
    int32_t net_id,
    OHOS::NWeb::NetConnectType type,
    OHOS::NWeb::NetConnectSubtype subtype) {
  if (network_for_dns_ != -1 && net_id != network_for_dns_) {
    LOG(INFO) << "ohos_network ConnectionTypeChangedTo ret, net_id " << net_id
              << ", network_for_dns_ " << network_for_dns_;
    return;
  }

  if (!network_change_notifier_posix_) {
      return;
  }

  if (net_id_ != net_id || type_ != type) {
    LOG(INFO) << "ohos_network ConnectionTypeChangedTo, net_id_ " << net_id_
              << ", net_id " << net_id << ", type_ " << (int)type_ << ", type "
              << (int)type << ", network_for_dns_ " << network_for_dns_;
    net_id_ = net_id;
    type_ = type;
#if BUILDFLAG(IS_ARKWEB_EXT) && BUILDFLAG(ARKWEB_EXT_NETWORK_CONNECTION)
    if (network_for_dns_ != -1) {
      auto new_addr_list = network_change_notifier_posix_->GetNetAddrListByNetId(net_id_);
      auto cur_addr_list = network_change_notifier_posix_->GetCurrentNetAddrList();
      if (!IsSameAddrList(new_addr_list, cur_addr_list)) {
        LOG(INFO) << "The current net_addr_list is different from the new net_addr_list, "
                  << "which will trigger OnIPAddressChanged event.";
    network_change_notifier_posix_->OnIPAddressChanged(
        net::NetworkChangeNotifier::IP_ADDRESS_CHANGE_NORMAL);
      } else {
        LOG(INFO) << "The current net_addr_list is same with the new net_addr_list, "
                  << "which will not trigger OnIPAddressChanged event.";
      }
    } else {
      network_change_notifier_posix_->OnIPAddressChanged(net::NetworkChangeNotifier::IP_ADDRESS_CHANGE_NORMAL);
    }
    network_change_notifier_posix_->OnConnectionChanged(
        ConvertOhosConnTypeToNetBaseConnType(type));
#else
    network_change_notifier_posix_->OnIPAddressChanged(net::NetworkChangeNotifier::IP_ADDRESS_CHANGE_NORMAL);
    network_change_notifier_posix_->OnConnectionChanged(
                                    ConvertOhosConnTypeToNetBaseConnType(type));
#endif
  }

  if (subtype_ != subtype) {
    LOG(INFO) << "ohos_network ConnectionTypeChangedTo, net_id_ " << net_id_
              << ", subtype_ " << (int)subtype_ << ", subtype " << (int)subtype;
    subtype_ = subtype;
    network_change_notifier_posix_->OnConnectionSubtypeChanged(
        ConvertOhosConnTypeToNetBaseConnType(type),
        ConvertOhosConnSubtypeToNetBaseConnSubtype(subtype));
  }
}

base::NoDestructor<std::shared_ptr<NetConnCallbackImpl>> g_net_connect_callback(nullptr);
#if BUILDFLAG(IS_ARKWEB_EXT)
base::NoDestructor<std::shared_ptr<VpnListenerImpl>> g_vpn_listener(nullptr);
#endif
int32_t g_callback_id = -1;
#endif

}  // namespace

namespace net {

class NetworkChangeNotifierPassiveUtils {
 public:
#if BUILDFLAG(ARKWEB_NETWORK_BASE)
  static void RegisterOhosNetConnCallback(
      raw_ptr<NetworkChangeNotifierPassive> obj) {
    *g_net_connect_callback = std::make_shared<NetConnCallbackImpl>(obj);
#if BUILDFLAG(IS_ARKWEB_EXT)
    *g_vpn_listener = std::make_shared<VpnListenerImpl>(obj);
#endif
    if (obj->ohos_net_conn_adapter_) {
      g_callback_id = obj->ohos_net_conn_adapter_->RegisterNetConnCallback(
          *g_net_connect_callback);
      if (g_callback_id < 0) {
        LOG(ERROR) << "register ohos net connect callback failed.";
      }
#if BUILDFLAG(IS_ARKWEB_EXT)
      obj->ohos_net_conn_adapter_->RegisterVpnListener(*g_vpn_listener);
#endif
    }
  }

  static void UnRegisterOhosNetConnCallback(
      raw_ptr<NetworkChangeNotifierPassive> obj) {
    if (obj->ohos_net_conn_adapter_) {
      int32_t ret =
          obj->ohos_net_conn_adapter_->UnregisterNetConnCallback(g_callback_id);
      if (ret != 0) {
        LOG(ERROR) << "unregister ohos net connect callback failed.";
      }
      obj->ohos_net_conn_adapter_->UnRegisterVpnListener();
    }
  }
#endif

#if BUILDFLAG(ARKWEB_EXT_HTTP_DNS_FALLBACK)
  static void SetDnsServers(raw_ptr<NetworkChangeNotifierPassive> obj) {
    std::vector<std::string> dns_servers;
    if (base::CommandLine::ForCurrentProcess()->HasSwitch(
            switches::kEnableNwebExHttpDnsFallback)) {
      if (obj->ohos_net_conn_adapter_) {
        LOG(INFO) << "OnConnectionChanged, network_for_dns_ "
                  << obj->network_for_dns_;
        if (obj->vpn_in_place_) {
          dns_servers = obj->ohos_net_conn_adapter_->GetDnsServersForVpn();
        } else {
          dns_servers = obj->ohos_net_conn_adapter_->GetDnsServersByNetId(obj->network_for_dns_);
        }
      }
    }
    {
      base::AutoLock scoped_lock(obj->dns_server_lock_);
      if (!dns_servers.empty()) {
      obj->dns_servers_ = std::move(dns_servers);
      } else {
        LOG(ERROR) << "OnConnectionChanged, ohos_network dns server is empty.";
      }
    }
  }
#endif

#if BUILDFLAG(IS_ARKWEB_EXT) && BUILDFLAG(ARKWEB_EXT_NETWORK_CONNECTION)
  static std::vector<std::string> GetNetAddrListByNetId(raw_ptr<NetworkChangeNotifierPassive> obj, int32_t netId) {
    std::vector<std::string> net_addr_list;
      if (obj->ohos_net_conn_adapter_) {
        LOG(INFO) << "OnConnectionChanged, GetNetAddrListByNetId, netId "
                  << netId;
        net_addr_list = obj->ohos_net_conn_adapter_->GetNetAddrListByNetId(netId);
    }
   return net_addr_list;
  }
#endif
};

#ifndef BIND_DNS_TEST
#if BUILDFLAG(ARKWEB_EXT_HTTP_DNS_FALLBACK)
const std::vector<std::string>
NetworkChangeNotifierPassive::GetCurrentDnsServers() {
  base::AutoLock scoped_lock(dns_server_lock_);
  return dns_servers_;
}
#endif

#if BUILDFLAG(IS_ARKWEB_EXT) && BUILDFLAG(ARKWEB_NETWORK_BASE)
void NetworkChangeNotifierPassive::OnVpnAvailable()
{
  LOG(INFO) << "ohos_network on vpn available";
  vpn_in_place_ = true;
  OnIPAddressChanged(net::NetworkChangeNotifier::IP_ADDRESS_CHANGE_NORMAL);
  OnConnectionChanged(connection_type_);
}

void NetworkChangeNotifierPassive::OnVpnLost()
{
  LOG(INFO) << "ohos_network on vpn lost";
  vpn_in_place_ = false;
  OnIPAddressChanged(net::NetworkChangeNotifier::IP_ADDRESS_CHANGE_NORMAL);
  OnConnectionChanged(connection_type_);
}
#endif

#if BUILDFLAG(ARKWEB_EXT_NETWORK_CONNECTION)
void NetworkChangeNotifierPassive::BindDnsToNetwork(int32_t network_for_dns) {
  if (*g_net_connect_callback) {
    (*g_net_connect_callback)->BindDnsToNetwork(network_for_dns);
  }
#if BUILDFLAG(ARKWEB_EXT_HTTP_DNS_FALLBACK)
  network_for_dns_ = network_for_dns;
#endif
}

#if BUILDFLAG(IS_ARKWEB_EXT)
const std::vector<std::string> NetworkChangeNotifierPassive::GetNetAddrListByNetId(int32_t netId) {
  std::vector<std::string> net_addr_list = NetworkChangeNotifierPassiveUtils::GetNetAddrListByNetId(this, netId);
  if (net_addr_list.empty()) {
    LOG(INFO) << "Get net addrList by netId failed, net_addr_list is empty.";
  }
    return net_addr_list;
}
 
const std::vector<std::string>
NetworkChangeNotifierPassive::GetCurrentNetAddrList() {
  base::AutoLock scoped_lock(lock_);
  return net_addr_list_;
}
 
void NetworkChangeNotifierPassive::SetNetAddrList(std::vector<std::string> new_addr_list) {
  base::AutoLock scoped_lock(lock_);
  if (!new_addr_list.empty()) {
    net_addr_list_ = std::move(new_addr_list);
    LOG(INFO) << "set new NetAddrList, size is " << net_addr_list_.size();
  } else {
    net_addr_list_.clear();
    LOG(INFO) << "clear NetAddrList_";
  }
}
#endif
#endif
#endif // BIND_DNS_TEST
}  // namespace net
