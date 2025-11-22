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

#ifndef MEDIA_GPU_OHOS_CODEC_SURFACE_BUNDLE_H_
#define MEDIA_GPU_OHOS_CODEC_SURFACE_BUNDLE_H_

#include "base/memory/ref_counted_delete_on_sequence.h"
#include "gpu/command_buffer/service/ohos/native_image_texture_owner.h"
#include "media/gpu/media_gpu_export.h"
#include "media/gpu/ohos/codec_buffer_wait_coordinator.h"

namespace gpu {
class RefCountedLock;
}  // namespace gpu

namespace media {
// using namespace OHOS::NWeb;
class MEDIA_GPU_EXPORT CodecSurfaceBundle
    : public base::RefCountedDeleteOnSequence<CodecSurfaceBundle> {
 public:
  CodecSurfaceBundle();
  explicit CodecSurfaceBundle(
      scoped_refptr<gpu::NativeImageTextureOwner> texture_owner,
      scoped_refptr<gpu::RefCountedLock> drdc_lock);

  CodecSurfaceBundle(const CodecSurfaceBundle&) = delete;
  CodecSurfaceBundle& operator=(const CodecSurfaceBundle&) = delete;

  void* GetOHOSNativeWindow() const;

  scoped_refptr<CodecBufferWaitCoordinator> codec_buffer_wait_coordinator()
      const {
    return codec_buffer_wait_coordinator_;
  }

 private:
  ~CodecSurfaceBundle();
  friend class base::RefCountedDeleteOnSequence<CodecSurfaceBundle>;
  friend class base::DeleteHelper<CodecSurfaceBundle>;

  scoped_refptr<CodecBufferWaitCoordinator> codec_buffer_wait_coordinator_;

  raw_ptr<void> ohos_native_window_ = nullptr;

  base::WeakPtrFactory<CodecSurfaceBundle> weak_factory_{this};
};

}  // namespace media

#endif  // MEDIA_GPU_OHOS_CODEC_SURFACE_BUNDLE_H_
