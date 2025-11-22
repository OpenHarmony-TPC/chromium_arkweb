// Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "media/gpu/ohos/codec_surface_bundle.h"

#include "base/functional/bind.h"
#include "base/task/sequenced_task_runner.h"
#include "media/base/ohos/ohos_media_decoder_bridge_impl.h"

namespace media {

CodecSurfaceBundle::CodecSurfaceBundle()
    : RefCountedDeleteOnSequence<CodecSurfaceBundle>(
          base::SequencedTaskRunner::GetCurrentDefault()) {}

CodecSurfaceBundle::CodecSurfaceBundle(
    scoped_refptr<gpu::NativeImageTextureOwner> texture_owner,
    scoped_refptr<gpu::RefCountedLock> drdc_lock)
    : RefCountedDeleteOnSequence<CodecSurfaceBundle>(
          base::SequencedTaskRunner::GetCurrentDefault()),
      codec_buffer_wait_coordinator_(
          base::MakeRefCounted<CodecBufferWaitCoordinator>(
              std::move(texture_owner),
              std::move(drdc_lock))),
      ohos_native_window_(codec_buffer_wait_coordinator_->texture_owner()
                              ->AquireOhosNativeWindow()) {}

CodecSurfaceBundle::~CodecSurfaceBundle() {
  if (!codec_buffer_wait_coordinator_) {
    return;
  }

  codec_buffer_wait_coordinator_->texture_owner()->ReleaseNativeImage();
}

void* CodecSurfaceBundle::GetOHOSNativeWindow() const {
  return ohos_native_window_.get();
}

}  // namespace media
                     