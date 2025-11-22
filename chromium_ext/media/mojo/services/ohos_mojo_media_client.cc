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

#include "media/mojo/services/ohos_mojo_media_client.h"

#include <utility>

#include <memory>
#include "base/logging.h"
#include "base/functional/bind.h"
#include "base/task/single_thread_task_runner.h"
#include "media/base/audio_decoder.h"
#include "media/base/cdm_factory.h"
#include "media/base/media_log.h"
#include "media/base/ohos/ohos_cdm_factory.h"
#include "media/mojo/mojom/media_drm_storage.mojom.h"
#include "media/mojo/mojom/provision_fetcher.mojom.h"
#include "media/mojo/services/ohos_mojo_util.h"
#include "media/filters/ohos/ohos_audio_decoder.h"
using media::ohos_mojo_util::CreateMediaDrmStorage;
using media::ohos_mojo_util::CreateProvisionFetcher;

namespace media {

OHOSMojoMediaClient::OHOSMojoMediaClient() {}

OHOSMojoMediaClient::~OHOSMojoMediaClient() {}

std::unique_ptr<AudioDecoder> OHOSMojoMediaClient::CreateAudioDecoder(
    scoped_refptr<base::SequencedTaskRunner> task_runner,
    std::unique_ptr<MediaLog> media_log) {
  LOG(INFO) << "OHOSMojoMediaClient::CreateAudioDecoder";
  return std::make_unique<OHOSAudioDecoder>(task_runner);
}

std::unique_ptr<CdmFactory> OHOSMojoMediaClient::CreateCdmFactory(
    mojom::FrameInterfaceFactory* frame_interfaces) {
  if (!frame_interfaces) {
    NOTREACHED() << "Host interfaces should be provided when using CDM with "
                 << "OHOSMojoMediaClient";
  }

  return std::make_unique<OHOSCdmFactory>(
      base::BindRepeating(&CreateProvisionFetcher, frame_interfaces),
      base::BindRepeating(&CreateMediaDrmStorage, frame_interfaces));
}

}  // namespace media
