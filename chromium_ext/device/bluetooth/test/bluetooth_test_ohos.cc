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

#include "device/bluetooth/test/bluetooth_test_ohos.h"
#include "device/bluetooth/ohos/bluetooth_adapter_ohos.h"

namespace device {

class BluetoothAdapterOhosTest final : public BluetoothAdapterOhos {
 public:
  BluetoothAdapterOhosTest(
      scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner)
      : BluetoothAdapterOhos() {
    ui_task_runner_ = ui_task_runner;
  }
  ~BluetoothAdapterOhosTest() override {}
  bool IsPowered() const override { return is_powered_; }

  void SetPowered(bool powered,
                  base::OnceClosure callback,
                  ErrorCallback error_callback) override {
    is_powered_ = powered;
    NotifyAdapterPoweredChanged(is_powered_);
    std::move(callback).Run();
  }

 private:
  bool is_powered_{false};
};

BluetoothTestOhos::BluetoothTestOhos() = default;

BluetoothTestOhos::~BluetoothTestOhos() = default;

bool BluetoothTestOhos::PlatformSupportsLowEnergy() {
  return true;
}

void BluetoothTestOhos::InitWithFakeAdapter() {
  auto adapter = base::WrapRefCounted(new BluetoothAdapterOhosTest(
      task_environment_.GetMainThreadTaskRunner()));
  adapter_ = std::move(adapter);
  adapter_->SetPowered(true, base::DoNothing(), base::DoNothing());
}

BluetoothDevice* BluetoothTestOhos::SimulateLowEnergyDevice(
    int device_ordinal) {
  LowEnergyDeviceData data = GetLowEnergyDeviceData(device_ordinal);
  ohos::adapter::device::ScanResult scan_result;
  scan_result.device_name = data.name.value();
  scan_result.device_id = data.address;
  scan_result.rssi = data.rssi;
  scan_result.data = nullptr;
  scan_result.data_length = 0;
  scan_result.connectable = false;
  static_cast<BluetoothLowEnergyAdapterOhos*>(adapter_.get())
      ->LowEnergyDeviceUpdated(scan_result);
  BluetoothDevice* device_ptr = adapter_->GetDevice(data.address);
  device_ptr->UpdateAdvertisementData(
      data.rssi, data.flags, data.advertised_uuids, data.tx_power,
      data.service_data, data.manufacturer_data);
  return device_ptr;
}

}  // namespace device