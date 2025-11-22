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

#ifndef GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_GL_TEXTURE_PASSTHROUGH_OHOS_IMAGE_REPRESENTATION_H_
#define GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_GL_TEXTURE_PASSTHROUGH_OHOS_IMAGE_REPRESENTATION_H_

#include "gpu/command_buffer/service/shared_image/ohos_native_buffer_image_backing.h"
#include "gpu/command_buffer/service/shared_image/shared_image_representation.h"
#include "ui/gl/scoped_egl_image.h"

namespace gpu {
class OhosNativeBufferImageBacking;

class GLTexturePassthroughOhosImageRepresentation
    : public GLTexturePassthroughImageRepresentation {
 public:
  GLTexturePassthroughOhosImageRepresentation(
      SharedImageManager* manager,
      OhosNativeBufferImageBacking* backing,
      MemoryTypeTracker* tracker,
      gl::ScopedEGLImage egl_image,
      scoped_refptr<gles2::TexturePassthrough> texture);
  ~GLTexturePassthroughOhosImageRepresentation() override;

  GLTexturePassthroughOhosImageRepresentation(
      const GLTexturePassthroughOhosImageRepresentation&) = delete;
  GLTexturePassthroughOhosImageRepresentation& operator=(
      const GLTexturePassthroughOhosImageRepresentation&) = delete;

  const scoped_refptr<gles2::TexturePassthrough>& GetTexturePassthrough(
      int plane_index) override;

  bool BeginAccess(GLenum mode) override;
  void EndAccess() override;

 private:
  OhosNativeBufferImageBacking* ohos_backing() {
    return static_cast<OhosNativeBufferImageBacking*>(backing());
  }

  gl::ScopedEGLImage egl_image_;
  scoped_refptr<gles2::TexturePassthrough> texture_;
  RepresentationAccessMode mode_ = RepresentationAccessMode::kNone;
};

}  // namespace gpu

#endif  // GPU_COMMAND_BUFFER_SERVICE_SHARED_IMAGE_GL_TEXTURE_PASSTHROUGH_OHOS_IMAGE_REPRESENTATION_H_
