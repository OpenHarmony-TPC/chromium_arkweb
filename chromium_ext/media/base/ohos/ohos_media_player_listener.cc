// Copyright 2022 Huawei Device Co., Ltd.
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

#include "media/base/ohos/ohos_media_player_listener.h"

namespace media {

OHOSMediaPlayerListener::OHOSMediaPlayerListener(
    const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
    base::WeakPtr<OHOSMediaPlayerBridge> media_player)
    : task_runner_(task_runner), media_player_(media_player) {
  DCHECK(task_runner_.get());
  DCHECK(media_player_);
}

void OHOSMediaPlayerListener::OnBufferAvailable(
    std::shared_ptr<OHOS::NWeb::SurfaceBufferAdapter> buffer) {
  task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(&OHOSMediaPlayerBridge::OnVideoSizeChanged, media_player_,
                     buffer->GetWidth(), buffer->GetHeight()));
  task_runner_->PostTask(
      FROM_HERE, base::BindOnce(&OHOSMediaPlayerBridge::OnBufferAvailable,
                                media_player_, std::move(buffer)));
}

OHOSMediaPlayerListener::~OHOSMediaPlayerListener() {}

}  // namespace media
