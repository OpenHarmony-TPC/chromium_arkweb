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

#include "media/base/ohos/ohos_media_player_callback.h"

namespace media {

OHOSMediaPlayerCallback::OHOSMediaPlayerCallback(
    const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
    base::WeakPtr<OHOSMediaPlayerBridge> media_player)
    : task_runner_(task_runner), media_player_(media_player) {
  DCHECK(task_runner_.get());
  DCHECK(media_player_);
}

OHOSMediaPlayerCallback::~OHOSMediaPlayerCallback() {}

void OHOSMediaPlayerCallback::OnError(
    OHOS::NWeb::PlayerAdapterErrorType errorType) {
  LOG(ERROR) << "media player error";
  int media_error_type =
      OHOSMediaPlayerBridge::MediaErrorType::MEDIA_ERROR_INVALID_CODE;
  if (errorType == OHOS::NWeb::PlayerAdapterErrorType::UNSUPPORT_TYPE) {
    media_error_type =
        OHOSMediaPlayerBridge::MediaErrorType::MEDIA_ERROR_FORMAT;
  } else if (errorType == OHOS::NWeb::PlayerAdapterErrorType::FATAL_ERROR) {
    media_error_type =
        OHOSMediaPlayerBridge::MediaErrorType::MEDIA_ERROR_DECODE;
  }
  if (media_player_ == nullptr) {
    LOG(ERROR) << "media_player_ is nullptr";
    return;
  }
  task_runner_->PostTask(
      FROM_HERE, base::BindOnce(&OHOSMediaPlayerBridge::OnError, media_player_,
                                media_error_type));
}

void OHOSMediaPlayerCallback::OnInfo(OHOS::NWeb::PlayerOnInfoType type,
                                     int32_t extra,
                                     int32_t value) {
  if (media_player_ == nullptr) {
    LOG(ERROR) << "media_player_ is nullptr";
    return;
  }
  switch (type) {
    case OHOS::NWeb::PlayerOnInfoType::INFO_TYPE_EOS:
      task_runner_->PostTask(
          FROM_HERE,
          base::BindOnce(&OHOSMediaPlayerBridge::OnEnd, media_player_));
      break;
    case OHOS::NWeb::PlayerOnInfoType::INFO_TYPE_STATE_CHANGE:
      task_runner_->PostTask(
          FROM_HERE,
          base::BindOnce(
              &OHOSMediaPlayerBridge::OnPlayerStateUpdate, media_player_,
              static_cast<OHOS::NWeb::PlayerAdapter::PlayerStates>(extra)));
      break;
    case OHOS::NWeb::PlayerOnInfoType::INFO_TYPE_POSITION_UPDATE:
      task_runner_->PostTask(
          FROM_HERE, base::BindOnce(&OHOSMediaPlayerBridge::OnSeekBack,
                                    media_player_, base::Milliseconds(extra)));
      break;
    case OHOS::NWeb::PlayerOnInfoType::INFO_TYPE_MESSAGE:
      break;
    case OHOS::NWeb::PlayerOnInfoType::INFO_TYPE_INTERRUPT_EVENT:
      task_runner_->PostTask(
          FROM_HERE,
          base::BindOnce(&OHOSMediaPlayerBridge::OnPlayerInterruptEvent,
                         media_player_, value));
      break;
    case OHOS::NWeb::PlayerOnInfoType::INFO_TYPE_SEEKDONE:
      task_runner_->PostTask(
          FROM_HERE,
          base::BindOnce(&OHOSMediaPlayerBridge::SeekDone, media_player_));
      break;
    case OHOS::NWeb::PlayerOnInfoType::INFO_TYPE_RESOLUTION_CHANGE:
      task_runner_->PostTask(
          FROM_HERE,
          base::BindOnce(&OHOSMediaPlayerBridge::OnVideoSizeChanged, media_player_, extra, value));
      break;
    default:
      break;
  }
}
}  // namespace media
