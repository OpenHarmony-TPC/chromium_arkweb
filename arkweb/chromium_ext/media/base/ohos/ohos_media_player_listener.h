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

#ifndef MEDIA_BASE_OHOS_MEDIA_PLAYER_LISTENER_H_
#define MEDIA_BASE_OHOS_MEDIA_PLAYER_LISTENER_H_

#include "base/logging.h"
#include "base/task/single_thread_task_runner.h"
#include "media/base/ohos/ohos_media_player_bridge.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class OHOSMediaPlayerBridge;

class OHOSMediaPlayerListener
    : public OHOS::NWeb::IBufferConsumerListenerAdapter {
 public:
  OHOSMediaPlayerListener(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      base::WeakPtr<OHOSMediaPlayerBridge> media_player);

  OHOSMediaPlayerListener(const OHOSMediaPlayerListener&) = delete;
  OHOSMediaPlayerListener& operator=(const OHOSMediaPlayerListener&) = delete;

  virtual ~OHOSMediaPlayerListener();
  void OnBufferAvailable(
      std::shared_ptr<OHOS::NWeb::SurfaceBufferAdapter> buffer) override;

 private:
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::WeakPtr<OHOSMediaPlayerBridge> media_player_;
};

}  // namespace media

#endif  // MEDIA_BASE_OHOS_MEDIA_PLAYER_LISTENER_H_
