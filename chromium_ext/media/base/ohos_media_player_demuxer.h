/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef MEDIA_FILTERS_OHOS_CUSTOM_MEDIA_PLAYER_DEMUXER_H_
#define MEDIA_FILTERS_OHOS_CUSTOM_MEDIA_PLAYER_DEMUXER_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "base/task/sequenced_task_runner.h"
#include "base/task/single_thread_task_runner.h"
#include "media/base/container_names.h"
#include "media/base/demuxer.h"
#include "media/base/demuxer_stream.h"
#include "media/base/media_track.h"
#include "media/base/pipeline_status.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/decoder_buffer.h"
#include "media/base/video_decoder_config.h"
#include "media/base/audio_codecs.h"
#include "media/base/sample_format.h"
#include "media/base/channel_layout.h"

namespace media {

// OhosMediaPlayerDemuxer is an empty demuxer implementation for
// OpenHarmony custom media player integration. This demuxer can be used
// as a placeholder or base for implementing custom demuxing logic
// specific to OpenHarmony platform.
class MEDIA_EXPORT OhosMediaPlayerDemuxer : public Demuxer {
 public:
  OhosMediaPlayerDemuxer(const scoped_refptr<base::SequencedTaskRunner>& task_runner);

  OhosMediaPlayerDemuxer(const OhosMediaPlayerDemuxer&) = delete;
  OhosMediaPlayerDemuxer& operator=(const OhosMediaPlayerDemuxer&) =
      delete;

  ~OhosMediaPlayerDemuxer() override;

  // Demuxer implementation
  void ForwardBufferedEndTimeChangeToDemuxerHost(base::TimeDelta buffered_time) override;
  void ForwardDurationChangeToDemuxerHost(base::TimeDelta duration) override;
  std::string GetDisplayName() const override;
  DemuxerType GetDemuxerType() const override;
  void Initialize(DemuxerHost* host, PipelineStatusCallback status_cb) override;
  void AbortPendingReads() override;
  void StartWaitingForSeek(base::TimeDelta seek_time) override;
  void CancelPendingSeek(base::TimeDelta seek_time) override;
  void Seek(base::TimeDelta time, PipelineStatusCallback status_cb) override;
  bool IsSeekable() const override;
  void Stop() override;
  base::TimeDelta GetStartTime() const override;
  base::Time GetTimelineOffset() const override;
  int64_t GetMemoryUsage() const override;
  std::optional<container_names::MediaContainerName> GetContainerForMetrics()
      const override;
  void OnTracksChanged(DemuxerStream::Type track_type,
                       std::optional<MediaTrack::Id> track_id,
                       base::TimeDelta curr_time,
                       TrackChangeCB change_completed_cb) override;
  void SetPlaybackRate(double rate) override;

  // MediaResource implementation
  std::vector<DemuxerStream*> GetAllStreams() override;

 private:
   // Simple mock DemuxerStream for returning valid streams.
  class MockDemuxerStream : public DemuxerStream {
   public:
    explicit MockDemuxerStream(Type type);
    ~MockDemuxerStream() override;

    // DemuxerStream implementation
    void Read(uint32_t count, ReadCB read_cb) override;
    AudioDecoderConfig audio_decoder_config() override;
    VideoDecoderConfig video_decoder_config() override;
    Type type() const override;
    bool SupportsConfigChanges() override;

   private:
    Type type_;
    AudioDecoderConfig audio_config_;
    VideoDecoderConfig video_config_;
  };
  // Host for reporting demuxer events (buffered ranges, duration, errors).
  raw_ptr<DemuxerHost> host_;

  // Flag indicating whether the demuxer has been stopped.
  bool stopped_;

  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  // Mock streams for audio and video
  std::unique_ptr<MockDemuxerStream> audio_stream_;
  std::unique_ptr<MockDemuxerStream> video_stream_;

  base::WeakPtrFactory<OhosMediaPlayerDemuxer> weak_factory_{this};
};

}  // namespace media

#endif  // MEDIA_FILTERS_OHOS_CUSTOM_MEDIA_PLAYER_DEMUXER_H_