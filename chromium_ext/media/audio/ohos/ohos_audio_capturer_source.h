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

#ifndef MEDIA_OHOS_AUDIO_OHOS_AUDIO_CAPTURER_SOURCE_H_
#define MEDIA_OHOS_AUDIO_OHOS_AUDIO_CAPTURER_SOURCE_H_

#include "base/files/file_util.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "media/base/audio_capturer_source.h"
#include "media/base/media_export.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/audio_capturer_adapter.h"
#include "third_party/ohos_ndk/includes/ohos_adapter/audio_renderer_adapter.h"

namespace base {
class SingleThreadTaskRunner;
}  // namespace base

namespace media {
using namespace OHOS::NWeb;

using OnReadDataCallback = base::RepeatingCallback<void(void)>;

constexpr int kMaxNumOfBuffer = 2;

class AudioCapturerReadCallback : public AudioCapturerReadCallbackAdapter {
 public:
  AudioCapturerReadCallback(const OnReadDataCallback& readDataCallback);

  ~AudioCapturerReadCallback();

  void OnReadData(size_t length) override;

 private:
  OnReadDataCallback readDataCallback_;
};

class MEDIA_EXPORT OHOSAudioCapturerSource final : public AudioCapturerSource {
 public:
  OHOSAudioCapturerSource(
      scoped_refptr<base::SingleThreadTaskRunner> capturer_task_runner);
  OHOSAudioCapturerSource(const OHOSAudioCapturerSource&) = delete;
  OHOSAudioCapturerSource& operator=(const OHOSAudioCapturerSource&) = delete;

  // AudioCaptureSource implementation.
  void Initialize(const AudioParameters& params,
                  CaptureCallback* callback) override;
  void Start() override;
  void Stop() override;
  void SetVolume(double volume) override;
  void SetAutomaticGainControl(bool enable) override;
  void SetOutputDeviceForAec(const std::string& output_device_id) override;

 private:
  ~OHOSAudioCapturerSource() override;

  void ReadData();
  void NotifyCaptureError(const std::string& error);
  void NotifyCaptureStarted();
  void ReportError(const std::string& message);

  std::unique_ptr<AudioCapturerAdapter> capturer_;
  uint32_t frameCount_ = 0;
  scoped_refptr<base::SingleThreadTaskRunner> capturer_task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;
  AudioParameters params_;
  raw_ptr<CaptureCallback> callback_ = nullptr;
  base::Lock callback_lock_;
  std::shared_ptr<AudioCapturerReadCallback> audioCapturerReadCallback_ =
      nullptr;
  raw_ptr<FILE> dumpFile_ = nullptr;
  std::atomic<bool> is_stopped_{false};
  base::WeakPtrFactory<OHOSAudioCapturerSource> weak_factory_{this};
};

}  // namespace media

#endif  // MEDIA_OHOS_AUDIO_OHOS_AUDIO_CAPTURER_SOURCE_H_
