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

#include "arkweb/chromium_ext/media/base/ohos_media_player_demuxer.h"
#include "base/logging.h"

namespace media {

OhosMediaPlayerDemuxer::MockDemuxerStream::MockDemuxerStream(Type type)
    : type_(type) {
  if (type_ == AUDIO) {
    AudioCodec audio_codec = AudioCodec::kAAC;
    SampleFormat sample_format = SampleFormat::kSampleFormatPlanarF32;
    ChannelLayout channel_layout = ChannelLayout::CHANNEL_LAYOUT_STEREO;
    int sample_rate = 48000;

    audio_config_.Initialize(audio_codec, sample_format, channel_layout,
                            sample_rate, std::vector<uint8_t>{},
                            EncryptionScheme::kUnencrypted,
                            base::TimeDelta(), {});
  } else if (type_ == VIDEO) {
    VideoCodec video_codec = VideoCodec::kH264;
    gfx::Size coded_size(1280, 720);
    gfx::Rect visible_rect(1280, 720);
    gfx::Size natural_size(1280, 720);

    video_config_.Initialize(video_codec, VIDEO_CODEC_PROFILE_UNKNOWN,
                            VideoDecoderConfig::AlphaMode::kIsOpaque,
                            VideoColorSpace(), VideoTransformation(), coded_size, visible_rect,
                            natural_size, std::vector<uint8_t>{},
                            EncryptionScheme::kUnencrypted);
  }
}

OhosMediaPlayerDemuxer::MockDemuxerStream::~MockDemuxerStream() = default;

void OhosMediaPlayerDemuxer::MockDemuxerStream::Read(
    uint32_t count,
    ReadCB read_cb) {
  std::move(read_cb).Run(Status::kOk, {DecoderBuffer::CreateEOSBuffer()});
}

AudioDecoderConfig OhosMediaPlayerDemuxer::MockDemuxerStream::audio_decoder_config() {
  return audio_config_;
}

VideoDecoderConfig OhosMediaPlayerDemuxer::MockDemuxerStream::video_decoder_config() {
  return video_config_;
}

DemuxerStream::Type OhosMediaPlayerDemuxer::MockDemuxerStream::type() const {
  return type_;
}

bool OhosMediaPlayerDemuxer::MockDemuxerStream::SupportsConfigChanges() {
  return false;
}


OhosMediaPlayerDemuxer::OhosMediaPlayerDemuxer(const scoped_refptr<base::SequencedTaskRunner>& task_runner)
    : host_(nullptr), stopped_(false), task_runner_(task_runner) {
  audio_stream_ = std::make_unique<MockDemuxerStream>(DemuxerStream::AUDIO);
  video_stream_ = std::make_unique<MockDemuxerStream>(DemuxerStream::VIDEO);
}

OhosMediaPlayerDemuxer::~OhosMediaPlayerDemuxer() {
  audio_stream_.reset();
  video_stream_.reset();
}

std::string OhosMediaPlayerDemuxer::GetDisplayName() const {
  return "OhosMediaPlayerDemuxer";
}

DemuxerType OhosMediaPlayerDemuxer::GetDemuxerType() const {
  return DemuxerType::kOhosMediaPlayerDemuxer;
}

void OhosMediaPlayerDemuxer::Initialize(DemuxerHost* host,
                                              PipelineStatusCallback status_cb) {
  DCHECK(host);
  host_ = host;
  // For now, just report success.
  task_runner_->PostTask(FROM_HERE,
                         base::BindOnce(std::move(status_cb), PIPELINE_OK));
}

void OhosMediaPlayerDemuxer::ForwardBufferedEndTimeChangeToDemuxerHost(
    base::TimeDelta buffered_time) {
  DCHECK(host_);
  DCHECK(task_runner_->RunsTasksInCurrentSequence());
  Ranges<base::TimeDelta> buffered;
  buffered.Add(base::TimeDelta(), buffered_time);
  host_->OnBufferedTimeRangesChanged(buffered);
}

void OhosMediaPlayerDemuxer::ForwardDurationChangeToDemuxerHost(base::TimeDelta duration) {
  DCHECK(host_);
  DCHECK(task_runner_->RunsTasksInCurrentSequence());
  host_->SetDuration(duration);
}

void OhosMediaPlayerDemuxer::AbortPendingReads() {
}

void OhosMediaPlayerDemuxer::StartWaitingForSeek(base::TimeDelta seek_time) {
}

void OhosMediaPlayerDemuxer::CancelPendingSeek(base::TimeDelta seek_time) {
}

void OhosMediaPlayerDemuxer::Seek(base::TimeDelta time,
                                        PipelineStatusCallback status_cb) {
  task_runner_->PostTask(FROM_HERE,
                         base::BindOnce(std::move(status_cb), PIPELINE_OK));
}

bool OhosMediaPlayerDemuxer::IsSeekable() const {
  return true;
}

void OhosMediaPlayerDemuxer::Stop() {
  stopped_ = true;
}

base::TimeDelta OhosMediaPlayerDemuxer::GetStartTime() const {
  return base::TimeDelta();
}

base::Time OhosMediaPlayerDemuxer::GetTimelineOffset() const {
  return base::Time();
}

int64_t OhosMediaPlayerDemuxer::GetMemoryUsage() const {
  return 0;
}

std::optional<container_names::MediaContainerName>
OhosMediaPlayerDemuxer::GetContainerForMetrics() const {
  return std::nullopt;
}

void OhosMediaPlayerDemuxer::OnTracksChanged(
    DemuxerStream::Type track_type,
    std::optional<MediaTrack::Id> track_id,
    base::TimeDelta curr_time,
    TrackChangeCB change_completed_cb) {
  std::move(change_completed_cb).Run(nullptr);
}

void OhosMediaPlayerDemuxer::SetPlaybackRate(double rate) {
}

std::vector<DemuxerStream*> OhosMediaPlayerDemuxer::GetAllStreams() {
  std::vector<DemuxerStream*> streams;
  streams.push_back(audio_stream_.get());
  streams.push_back(video_stream_.get());
  return streams;
}


}  // namespace media