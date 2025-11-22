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

#ifndef GPU_IPC_SERVICE_IMAGE_DECODE_ACCELERATOR_STUB_EXT_H_
#define GPU_IPC_SERVICE_IMAGE_DECODE_ACCELERATOR_STUB_EXT_H_

#include "gpu/ipc/service/image_decode_accelerator_worker.h"
#include "gpu/ipc/service/gpu_channel.h"
#include "gpu/ipc/service/image_decode_accelerator_stub.h"

namespace gpu {
class ImageDecodeAcceleratorStub;

class ImageDecodeAcceleratorStubExt : public ImageDecodeAcceleratorStub {
public:
  ImageDecodeAcceleratorStubExt(ImageDecodeAcceleratorWorker* worker,
                             GpuChannel* channel,
                             int32_t route_id);

  ~ImageDecodeAcceleratorStubExt() override;
#if BUILDFLAG(ARKWEB_HEIF_SUPPORT)
  bool ProcessCompletedDecodeExt(mojom::ScheduleImageDecodeParams& params,
                                 scoped_refptr<SharedContextState> shared_context_state,
                                 std::vector<sk_sp<SkImage>> plane_sk_images,
                                 std::optional<base::ScopedClosureRunner>& notify_gl_state_changed,
                                 std::unique_ptr<ImageDecodeAcceleratorWorker::DecodeResult>& completed_decode)
                                EXCLUSIVE_LOCKS_REQUIRED(lock_) override;

  void ReleasePixmapData(base::WaitableEvent* finish_event) override;
#endif
};

}
#endif  // GPU_IPC_SERVICE_IMAGE_DECODE_ACCELERATOR_STUB_EXT_H_