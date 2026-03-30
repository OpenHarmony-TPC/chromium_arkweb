/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "heif_image_decoder.h"

#include <stdint.h>

#include <algorithm>
#include <cstring>
#include <memory>

#include "base/bits.h"
#include "base/containers/adapters.h"
#include "base/logging.h"
#include "base/memory/scoped_refptr.h"
#include "base/numerics/safe_conversions.h"
#include "base/sys_byteorder.h"
#include "base/timer/elapsed_timer.h"
#include "build/build_config.h"
#include "media/video/half_float_maker.h"
#include "third_party/abseil-cpp/absl/types/optional.h"
#include "third_party/blink/renderer/platform/image-decoders/image_animation.h"
#include "third_party/blink/renderer/platform/image-decoders/image_decoder.h"
#include "third_party/bounds_checking_function/include/securec.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/ohos_adapter_helper.h"
#include "third_party/skia/include/codec/SkEncodedImageFormat.h"
#include "third_party/skia/include/core/SkColorSpace.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

#if defined(ARCH_CPU_BIG_ENDIAN)
#error Blink assumes a little-endian target.
#endif

namespace {

#define FOURCC(c1, c2, c3, c4) \
    ((c1) << 24 | (c2) << 16 | (c3) << 8 | (c4))

bool IsHeifFormatSupported(const void* buffer, size_t bytesRead,
                              SkEncodedImageFormat* format) {
    // Parse the ftyp box up to bytesRead to determine if this is HEIF or AVIF.
    // Any valid ftyp box should have at least 8 bytes.
    if (bytesRead < 8) {
        return false;
    }

    const uint32_t* ptr = static_cast<const uint32_t*>(buffer);
    uint64_t chunkSize = base::NetToHost32(ptr[0]);
    uint32_t chunkType = base::NetToHost32(ptr[1]);

    if (chunkType != FOURCC('f', 't', 'y', 'p')) {
        return false;
    }

    int64_t offset = 8;
    if (chunkSize == 1) {
        // This indicates that the next 8 bytes represent the chunk size,
        // and chunk data comes after that.
        if (bytesRead < 16) {
            return false;
        }
        const uint8_t* bytePtr = static_cast<const uint8_t*>(buffer) + offset;
        uint64_t chunkSizeValue;
        memcpy_s(&chunkSizeValue, sizeof(chunkSizeValue), bytePtr, sizeof(chunkSizeValue));
        chunkSize = base::NetToHost64(chunkSizeValue);
        if (chunkSize < 16) {
            // The smallest valid chunk is 16 bytes long in this case.
            return false;
        }
        offset += 8;
    } else if (chunkSize < 8) {
        // The smallest valid chunk is 8 bytes long.
        return false;
    }

    if (chunkSize > bytesRead) {
        chunkSize = bytesRead;
    }
    int64_t chunkDataSize = chunkSize - offset;
    // It should at least have major brand (4-byte) and minor version (4-bytes).
    // The rest of the chunk (if any) is a list of (4-byte) compatible brands.
    if (chunkDataSize < 8) {
        return false;
    }

    uint32_t numCompatibleBrands = (chunkDataSize - 8) / 4;
    bool isHeif = false;
    for (size_t i = 0; i < numCompatibleBrands + 2; ++i) {
        if (i == 1) {
            // Skip this index, it refers to the minorVersion,
            // not a brand.
            continue;
        }
        const uint8_t* bytePtr = static_cast<const uint8_t*>(buffer) + offset + 4 * i;
        uint32_t brandValue;
        memcpy_s(&brandValue, sizeof(brandValue), bytePtr, sizeof(brandValue));
        uint32_t brand = base::NetToHost32(brandValue);
        if (brand == FOURCC('m', 'i', 'f', '1') || brand == FOURCC('h', 'e', 'i', 'c')
          || brand == FOURCC('m', 's', 'f', '1') || brand == FOURCC('h', 'e', 'v', 'c')
          || brand == FOURCC('a', 'v', 'i', 'f') || brand == FOURCC('a', 'v', 'i', 's')) {
            // AVIF files could have "mif1" as the major brand. So we cannot
            // distinguish whether the image is AVIF or HEIC just based on the
            // "mif1" brand. So wait until we see a specific avif brand to
            // determine whether it is AVIF or HEIC.
            isHeif = true;
            if (brand == FOURCC('a', 'v', 'i', 'f')
              || brand == FOURCC('a', 'v', 'i', 's')) {
                if (format != nullptr) {
                    *format = SkEncodedImageFormat::kAVIF;
                }
                return true;
            }
        }
    }
    if (isHeif) {
        if (format != nullptr) {
            *format = SkEncodedImageFormat::kHEIF;
        }
        return true;
    }
    return false;
}

}  // namespace
namespace blink {

HEIFImageDecoder::HEIFImageDecoder(AlphaOption alpha_option,
                                   HighBitDepthDecodingOption hbd_option,
                                   const ColorBehavior& color_behavior,
                                   wtf_size_t max_decoded_bytes,
                                   AnimationOption animation_option)
    : ImageDecoder(alpha_option,
                   hbd_option,
                   color_behavior,
                   max_decoded_bytes) {}

HEIFImageDecoder::~HEIFImageDecoder() {
  decoder_adapter_.reset();
}

const AtomicString& HEIFImageDecoder::MimeType() const {
  DEFINE_STATIC_LOCAL(const AtomicString, heif_mime_type, ("image/heif"));
  return heif_mime_type;
}

bool HEIFImageDecoder::ImageIsHighBitDepth() {
  return bit_depth_ > 8;
}

void HEIFImageDecoder::OnSetData(scoped_refptr<SegmentReader> data) {
  OnSetData(data.get());
}

void HEIFImageDecoder::OnSetData(SegmentReader* data) {
  if (!IsAllDataReceived() || !data || data->size() == 0) {
    return;
  }
  LOG(INFO) << "[HeifSupport] HEIFImageDecoder::OnSetData parse image size "
            << data->size();
  auto sk_data = data->GetAsSkData();
  std::span<const uint8_t> encoded_data =
      std::span(sk_data->bytes(), sk_data->size());

  OHOS::NWeb::OhosImageDecoderAdapter* decoder_adapter = GetDecoderAdapter();
  if (decoder_adapter == nullptr) {
    LOG(ERROR) << "[HeifSupport] Fail to get decoder adapter.";
    SetFailed();
    return;
  }

  if (decoder_adapter->ParseImageInfo(encoded_data.data(),
                                      (uint32_t)encoded_data.size())) {
    LOG(INFO) << "[HeifSupport] HEIF image size "
              << decoder_adapter->GetImageWidth() << " * "
              << decoder_adapter->GetImageHeight();
    SetSize(decoder_adapter->GetImageWidth(),
            decoder_adapter->GetImageHeight());
    data_ = data;
    return;
  }
  LOG(ERROR) << "[HeifSupport] Fail to parsing image information. ";
  SetFailed();
}

cc::YUVSubsampling HEIFImageDecoder::GetYUVSubsampling() const {
  return cc::YUVSubsampling::k420;
}

gfx::Size HEIFImageDecoder::DecodedYUVSize(cc::YUVIndex index) const {
  DCHECK(IsDecodedSizeAvailable());
  return Size();
}

wtf_size_t HEIFImageDecoder::DecodedYUVWidthBytes(cc::YUVIndex index) const {
  return 0;
}

SkYUVColorSpace HEIFImageDecoder::GetYUVColorSpace() const {
  DCHECK(CanDecodeToYUV());
  DCHECK_NE(yuv_color_space_, SkYUVColorSpace::kIdentity_SkYUVColorSpace);
  return yuv_color_space_;
}

uint8_t HEIFImageDecoder::GetYUVBitDepth() const {
  DCHECK(CanDecodeToYUV());
  return bit_depth_;
}

absl::optional<gfx::HDRMetadata> HEIFImageDecoder::GetHDRMetadata() const {
  return hdr_metadata_;
}

void HEIFImageDecoder::DecodeToYUV() {}

int HEIFImageDecoder::RepetitionCount() const {
  return kAnimationNone;
}

bool HEIFImageDecoder::FrameIsReceivedAtIndex(wtf_size_t index) const {
  return true;
}

absl::optional<base::TimeDelta> HEIFImageDecoder::FrameTimestampAtIndex(
    wtf_size_t index) const {
  return index < frame_buffer_cache_.size()
             ? frame_buffer_cache_[index].Timestamp()
             : absl::nullopt;
}

base::TimeDelta HEIFImageDecoder::FrameDurationAtIndex(wtf_size_t index) const {
  return index < frame_buffer_cache_.size()
             ? frame_buffer_cache_[index].Duration()
             : base::TimeDelta();
}

bool HEIFImageDecoder::ImageHasBothStillAndAnimatedSubImages() const {
  return false;
}

void HEIFImageDecoder::DecodeSize() {}

wtf_size_t HEIFImageDecoder::DecodeFrameCount() {
  decoded_frame_count_ = 1;
  return IsDecodedSizeAvailable() ? decoded_frame_count_
                                  : frame_buffer_cache_.size();
}

void HEIFImageDecoder::InitializeNewFrame(wtf_size_t index) {}

void HEIFImageDecoder::Decode(wtf_size_t index) {
  if (frame_buffer_cache_.empty()) {
    LOG(ERROR) << "[HeifSupport] HEIFImageDecoder::Decode frame_buffer_cache "
                  "is empty.";
    SetFailed();
    return;
  }

  base::span<const uint8_t> segment = data_->GetSomeData(0);
  if (segment.empty()) {
    LOG(ERROR) << "[HeifSupport] HEIFImageDecoder::Decode GetSomeData failed.";
    SetFailed();
    return;
  }
  OHOS::NWeb::OhosImageDecoderAdapter* decoder_adapter = GetDecoderAdapter();
  if (decoder_adapter == nullptr) {
    LOG(ERROR) << "[HeifSupport] Fail to get decoder adapter.";
    SetFailed();
    return;
  }
  bool decode_rst = decoder_adapter->Decode(
      (const uint8_t*)segment.data(), (uint32_t)data_->size(),
      OHOS::NWeb::AllocatorType::kShareMemAlloc, false);
  if (!decode_rst) {
    LOG(ERROR) << "[HeifSupport] HEIFImageDecoder::Decode Decode failed.";
    SetFailed();
    return;
  }
  LOG(DEBUG) << "[HeifSupport] HEIFImageDecoder::Decode "
                "GetDecoderAdapter()->Decode succeed.";

  void* ptr = decoder_adapter->GetDecodeData();
  if (ptr == nullptr) {
    LOG(ERROR)
        << "[HeifSupport] HEIFImageDecoder::Decode GetDecodeData failed.";
    SetFailed();
    return;
  }

  if (!InitFrameBuffer(index)) {
    LOG(ERROR)
        << "[HeifSupport] HEIFImageDecoder::Decode InitFrameBuffer failed.";
    SetFailed();
    return;
  }

  ImageFrame& buffer = frame_buffer_cache_[index];
  ImageFrame::PixelData* pixel = buffer.GetAddr(0, 0);
  if (pixel == nullptr) {
    LOG(ERROR) << "[HeifSupport] HEIFImageDecoder::Decode GetAddr failed.";
    SetFailed();
    return;
  }

  int stride = decoder_adapter->GetStride();
  if (stride <= 0) {
    LOG(ERROR)
        << "[HeifSupport] HEIFImageDecoder::Decode stride error. stride = "
        << stride;
    SetFailed();
    return;
  }

  int width = buffer.Bitmap().width();
  int height = buffer.Bitmap().height();
  size_t rowBytes = buffer.Bitmap().rowBytes();
  int bytesPerPixel = buffer.Bitmap().bytesPerPixel();
  for (int i = 0; i < height; i++) {
    if (memcpy_s((uint8_t*)pixel + i * width * bytesPerPixel, rowBytes,
                 (uint8_t*)ptr + i * stride, width * bytesPerPixel) != EOK) {
      LOG(ERROR) << "[HeifSupport] HEIFImageDecoder::Decode memcpy failed."
                 << "width = " << width << ", height = " << height
                 << ", rowBytes = " << rowBytes
                 << ", bytesPerPixel = " << bytesPerPixel
                 << ", stride = " << stride;
      SetFailed();
      return;
    }
  }

  decoder_adapter->ReleasePixelMap();

  buffer.SetPixelsChanged(true);
  buffer.SetStatus(ImageFrame::kFrameComplete);
  LOG(DEBUG) << "[HeifSupport] HEIFImageDecoder::Decode decode complete.";
}

bool HEIFImageDecoder::CanReusePreviousFrameBuffer(wtf_size_t index) const {
  return true;
}

// Follow-up Processing
bool HEIFImageDecoder::MatchesHeifSignature(const sk_sp<SkData>& data) {
  std::span<const uint8_t> encoded_data =
      std::span(data->bytes(), data->size());
  if (!encoded_data.data()) {
    LOG(INFO) << "[HeifSupport] HEIFImageDecoder::MatchesHeifSignature, "
                 "encoded_data is null.";
    return false;
  }

  SkEncodedImageFormat format;
  if ((IsHeifFormatSupported(encoded_data.data(),
                                (size_t)encoded_data.size(), &format)) &&
      format == SkEncodedImageFormat::kHEIF) {
    LOG(INFO) << "[HeifSupport] HEIFImageDecoder::MatchesHeifSignature is heif "
                 "format.";
    return true;
  }

  LOG(INFO) << "[HeifSupport] Fail to parsing image information. ";
  return false;
}

OHOS::NWeb::OhosImageDecoderAdapter* HEIFImageDecoder::GetDecoderAdapter() {
  if (!decoder_adapter_) {
    decoder_adapter_ = OHOS::NWeb::OhosAdapterHelper::GetInstance()
                           .CreateOhosImageDecoderAdapter();
    if (!decoder_adapter_) {
      return nullptr;
    }
  }

  return decoder_adapter_.get();
}

}  // namespace blink
