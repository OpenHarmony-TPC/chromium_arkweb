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

#ifndef MEDIA_MOJO_SERVICES_OHOS_MOJO_MEDIA_CLIENT_H_
#define MEDIA_MOJO_SERVICES_OHOS_MOJO_MEDIA_CLIENT_H_

#include <memory>

#include "base/task/sequenced_task_runner.h"
#include "media/mojo/services/mojo_media_client.h"

namespace media {

class OHOSMojoMediaClient final : public MojoMediaClient {
 public:
  OHOSMojoMediaClient();

  OHOSMojoMediaClient(const OHOSMojoMediaClient&) = delete;
  OHOSMojoMediaClient& operator=(const OHOSMojoMediaClient&) = delete;

  ~OHOSMojoMediaClient() override;

  std::unique_ptr<AudioDecoder> CreateAudioDecoder(
      scoped_refptr<base::SequencedTaskRunner> task_runner,
      std::unique_ptr<MediaLog> media_log) override;

  std::unique_ptr<CdmFactory> CreateCdmFactory(
      mojom::FrameInterfaceFactory* frame_interfaces) override;
};

}  // namespace media

#endif  // MEDIA_MOJO_SERVICES_OHOS_MOJO_MEDIA_CLIENT_H_
