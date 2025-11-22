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

#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_VIDEO_CAPTURE_CONTROLLER_H_
#error \
    "must be in include form CONTENT_BROWSER_RENDERER_HOST_MEDIA_VIDEO_CAPTURE_CONTROLLER_H_"
#endif

namespace content {
#if BUILDFLAG(ARKWEB_WEBRTC)
void VideoCaptureController::PauseClientBySessionId(
    const base::UnguessableToken& session_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  ControllerClient* client = FindClient(session_id, controller_clients_);
  if (!client) {
    DVLOG(1) << "Client not found";
    return;
  }

  if (client->paused) {
    DVLOG(1) << "Calling pause on paused client";
    return;
  }

  client->paused = true;
}

void VideoCaptureController::ResumeClientBySessionId(
    const base::UnguessableToken& session_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  ControllerClient* client = FindClient(session_id, controller_clients_);
  if (!client) {
    DVLOG(1) << "Client not found";
    return;
  }

  if (!client->paused) {
    DVLOG(1) << "Calling resume on unpaused client";
    return;
  }

  client->paused = false;
}
#endif  // BUILDFLAG(ARKWEB_WEBRTC)

#if BUILDFLAG(ARKWEB_EX_SCREEN_CAPTURE)
void VideoCaptureController::SetScreenCaptureListener(
    VideoCaptureManager* video_capture_manager) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  video_capture_manager_ = video_capture_manager;
}
#endif  // defined(ARKWEB_EX_SCREEN_CAPTURE)
}  // namespace content