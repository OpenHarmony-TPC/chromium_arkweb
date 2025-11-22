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

#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_VIDEO_CAPTURE_MANAGER_H_EXT_
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_VIDEO_CAPTURE_MANAGER_H_EXT_

#include "arkweb/build/features/features.h"
#include "content/browser/renderer_host/media/video_capture_manager.h"
#include "content/browser/renderer_host/media/video_capture_provider.h"

namespace content {

class VideoCaptureManager;

class VideoCaptureManagerExt : public VideoCaptureManager {
public:
  VideoCaptureManagerExt(
      std::unique_ptr<content::VideoCaptureProvider> video_capture_provider,
      base::RepeatingCallback<void(const std::string&)> emit_log_message_cb);

  VideoCaptureManagerExt* AsVideoCaptureManagerExt() {
    return this;
  }

#if BUILDFLAG(ARKWEB_WEBRTC)
  void StartCamera(int nWebId) const;
  void StopCamera(int nWebId) const;
  void CloseCamera(int nWebId) const;
  void BindSessionIdToNWebId(media::VideoCaptureSessionId sessionId, int nWebId);
#endif  // BUILDFLAG(ARKWEB_WEBRTC)

#if BUILDFLAG(ARKWEB_EX_SCREEN_CAPTURE)
  void StopScreenCapture(const std::string& session_id);
  void SetScreenCapturePickerShow();
  void DisableSessionReuse();
  void ScreenCaptureOpened(const std::string& session_id);
  void OnScreenCaptureOpened(const std::string& session_id);
#endif  // defined(ARKWEB_EX_SCREEN_CAPTURE)

  base::WeakPtrFactory<VideoCaptureManagerExt> weak_factory_{this};
};
}

#endif  // CONTENT_BROWSER_RENDERER_HOST_MEDIA_VIDEO_CAPTURE_MANAGER_H_EXT_