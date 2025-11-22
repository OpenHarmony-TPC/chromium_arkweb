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

#include "media/mojo/services/ohos_mojo_util.h"

#include "media/mojo/services/mojo_media_drm_storage.h"
#include "mojo/public/cpp/bindings/pending_remote.h"

namespace media {
namespace ohos_mojo_util {

std::unique_ptr<ProvisionFetcher> CreateProvisionFetcher(
    media::mojom::FrameInterfaceFactory* frame_interfaces) {
  LOG(INFO) << "[DRM]" << __func__;
  DCHECK(frame_interfaces);
  if (frame_interfaces == nullptr) {
    LOG(ERROR) << "[DRM]" << __func__ << "frame_interfaces is nullptr";
    return nullptr;
  }
  mojo::PendingRemote<mojom::ProvisionFetcher> provision_fetcher;
  frame_interfaces->CreateProvisionFetcher(
      provision_fetcher.InitWithNewPipeAndPassReceiver());
  LOG(INFO) << "[DRM]" << __func__;
  return std::make_unique<MojoProvisionFetcher>(std::move(provision_fetcher));
}

std::unique_ptr<MediaDrmStorage> CreateMediaDrmStorage(
    media::mojom::FrameInterfaceFactory* frame_interfaces) {
  LOG(INFO) << "[DRM]" << __func__;
  DCHECK(frame_interfaces);
  if (frame_interfaces == nullptr) {
    LOG(ERROR) << "[DRM]" << __func__ << "frame_interfaces is nullptr";
    return nullptr;
  }
  mojo::PendingRemote<mojom::MediaDrmStorage> media_drm_storage;
  frame_interfaces->BindEmbedderReceiver(mojo::GenericPendingReceiver(
      media_drm_storage.InitWithNewPipeAndPassReceiver()));
  LOG(INFO) << "[DRM]" << __func__;
  return std::make_unique<MojoMediaDrmStorage>(std::move(media_drm_storage));
}

}  // namespace ohos_mojo_util
}  // namespace media
