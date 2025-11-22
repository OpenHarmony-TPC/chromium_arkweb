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

#ifndef MEDIA_FILTERS_DECODER_STREAM_H_
#error "must be in include form MEDIA_FILTERS_DECODER_STREAM_H_"
#endif

namespace media {
#if BUILDFLAG(ARKWEB_VIDEO_ASSISTANT)
namespace {
template<typename T>
bool SupportVideoSurface(const T& decoder_type) {
  return false;
}
template<>
bool SupportVideoSurface(const VideoDecoderType& decoder_type) {
  return decoder_type == VideoDecoderType::kMediaCodec ||
         decoder_type == VideoDecoderType::kOHOS;
}
}
#endif // ARKWEB_VIDEO_ASSISTANT

#if BUILDFLAG(ARKWEB_VIDEO_ASSISTANT)
template <DemuxerStream::Type StreamType>
void DecoderStream<StreamType>::SetVideoSurface(int surface_id) {
  traits_->SetVideoSurface(decoder_.get(), surface_id);
}
#endif // ARKWEB_VIDEO_ASSISTANT

#if BUILDFLAG(ARKWEB_PIP)
template <DemuxerStream::Type StreamType>
void DecoderStream<StreamType>::PipEnable(bool enable) {
  traits_->PipEnable(decoder_.get(), enable);
}
#endif

#if BUILDFLAG(ARKWEB_MEDIA_DMABUF)
// LCOV_EXCL_START
template <DemuxerStream::Type StreamType>
void DecoderStream<StreamType>::RecycleDmaBuffer() {
  if (traits_) {
    LOG(INFO) << "DMABUF::DecoderStreamForInclude, RecycleDmaBuffer";
    traits_->RecycleDmaBuffer(decoder_.get());
  }
}

template <DemuxerStream::Type StreamType>
void DecoderStream<StreamType>::ResumeDmaBuffer() {
  if (traits_) {
    LOG(INFO) << "DMABUF::DecoderStreamForInclude, ResumeDmaBuffer";
    traits_->ResumeDmaBuffer(decoder_.get());
  }
}
// LCOV_EXCL_STOP
#endif  // ARKWEB_MEDIA_DMABUF
}