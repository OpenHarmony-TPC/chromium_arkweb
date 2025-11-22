// Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef MEDIA_MOJO_SERVICES_OHOS_MOJO_UTIL_H_
#define MEDIA_MOJO_SERVICES_OHOS_MOJO_UTIL_H_

#include <memory>

#include "media/mojo/mojom/frame_interface_factory.mojom.h"
#include "media/mojo/services/mojo_media_drm_storage.h"
#include "media/mojo/services/mojo_provision_fetcher.h"

namespace media {
namespace ohos_mojo_util {

std::unique_ptr<ProvisionFetcher> CreateProvisionFetcher(
    media::mojom::FrameInterfaceFactory* frame_interfaces);

std::unique_ptr<MediaDrmStorage> CreateMediaDrmStorage(
    media::mojom::FrameInterfaceFactory* frame_interfaces);

}  // namespace ohos_mojo_util
}  // namespace media

#endif  // MEDIA_MOJO_SERVICES_OHOS_MOJO_UTIL_H_
