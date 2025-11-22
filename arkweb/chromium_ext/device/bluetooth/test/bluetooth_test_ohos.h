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

#ifndef DEVICE_BLUETOOTH_TEST_BLUETOOTH_TEST_OHOS_H_
#define DEVICE_BLUETOOTH_TEST_BLUETOOTH_TEST_OHOS_H_

#include "device/bluetooth/test/bluetooth_test.h"

namespace device {

class BluetoothTestOhos : public BluetoothTestBase {
 public:
  BluetoothTestOhos();
  ~BluetoothTestOhos() override;

  bool PlatformSupportsLowEnergy() override;
  void InitWithFakeAdapter();
  BluetoothDevice* SimulateLowEnergyDevice(int device_ordinal);
};

// Defines common test fixture name. Use TEST_F(BluetoothTest, YourTestName).
using BluetoothTest = BluetoothTestOhos;

}  // namespace device

#endif  // DEVICE_BLUETOOTH_TEST_BLUETOOTH_TEST_OHOS_H_
