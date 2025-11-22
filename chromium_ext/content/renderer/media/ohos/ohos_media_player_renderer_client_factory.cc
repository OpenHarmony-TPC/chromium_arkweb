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

#include "content/renderer/media/ohos/ohos_media_player_renderer_client_factory.h"

#include "content/renderer/media/ohos/ohos_media_player_renderer_client.h"
#include "media/mojo/clients/mojo_renderer.h"
#include "media/mojo/clients/mojo_renderer_factory.h"
#include "media/mojo/mojom/renderer_extensions.mojom.h"

namespace content {

OHOSMediaPlayerRendererClientFactory::OHOSMediaPlayerRendererClientFactory(
    scoped_refptr<base::SingleThreadTaskRunner> compositor_task_runner,
    std::unique_ptr<media::MojoRendererFactory> mojo_renderer_factory,
    const GetNativeTextureWrapperCB& get_native_texture_wrapper_cb)
    : get_native_texture_wrapper_cb_(get_native_texture_wrapper_cb),
      compositor_task_runner_(compositor_task_runner),
      mojo_renderer_factory_(std::move(mojo_renderer_factory)) {}

OHOSMediaPlayerRendererClientFactory::~OHOSMediaPlayerRendererClientFactory() {}

std::unique_ptr<media::Renderer>
OHOSMediaPlayerRendererClientFactory::CreateRenderer(
    const scoped_refptr<base::SequencedTaskRunner>& media_task_runner,
    const scoped_refptr<base::TaskRunner>& worker_task_runner,
    media::AudioRendererSink* audio_renderer_sink,
    media::VideoRendererSink* video_renderer_sink,
    media::RequestOverlayInfoCB request_surface_cb,
    const gfx::ColorSpace& target_color_space) {
  mojo::PendingRemote<media::mojom::MediaPlayerRendererExtension>
      renderer_extension_remote;
  auto renderer_extension_receiver =
      renderer_extension_remote.InitWithNewPipeAndPassReceiver();

  mojo::PendingRemote<media::mojom::MediaPlayerRendererClientExtension>
      client_extension_remote;
  auto client_extension_receiver =
      client_extension_remote.InitWithNewPipeAndPassReceiver();

  std::unique_ptr<media::MojoRenderer> mojo_renderer =
      mojo_renderer_factory_->CreateMediaPlayerRenderer(
          std::move(renderer_extension_receiver),
          std::move(client_extension_remote), media_task_runner,
          video_renderer_sink);

  media::ScopedNativeTextureWrapper native_texture_wrapper =
      get_native_texture_wrapper_cb_.Run();

  return std::make_unique<OHOSMediaPlayerRendererClient>(
      std::move(renderer_extension_remote),
      std::move(client_extension_receiver),
      media_task_runner, compositor_task_runner_,
      std::move(mojo_renderer),
      std::move(native_texture_wrapper),
      video_renderer_sink);
}

media::MediaResource::Type
OHOSMediaPlayerRendererClientFactory::GetRequiredMediaResourceType() {
  return media::MediaResource::Type::KUrl;
}

}  // namespace content
