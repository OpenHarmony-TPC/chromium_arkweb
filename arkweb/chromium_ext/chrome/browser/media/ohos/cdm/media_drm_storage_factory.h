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

#ifndef CHROME_BROWSER_MEDIA_OHOS_CDM_MEDIA_DRM_STORAGE_FACTORY_H_
#define CHROME_BROWSER_MEDIA_OHOS_CDM_MEDIA_DRM_STORAGE_FACTORY_H_

#include "media/mojo/mojom/media_drm_storage.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace content {
class RenderFrameHost;
}

void CreateMediaDrmStorage(
    content::RenderFrameHost* render_frame_host,
    mojo::PendingReceiver<media::mojom::MediaDrmStorage> receiver);

#endif  // CHROME_BROWSER_MEDIA_OHOS_CDM_MEDIA_DRM_STORAGE_FACTORY_H_
