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

#include "base/notreached.h"
#include "chrome/browser/extensions/api/image_writer_private/removable_storage_provider.h"

namespace {
using StorageDeviceListPtr = scoped_refptr<extensions::StorageDeviceList>;
}

namespace extensions {

// static
StorageDeviceListPtr RemovableStorageProvider::PopulateDeviceList() {
  // TODO(crbug.com/1233550): Integrate once platform APIs exist.
  // Fix Me
  NOTIMPLEMENTED_LOG_ONCE();
  return {};
}

}  // namespace extensions
