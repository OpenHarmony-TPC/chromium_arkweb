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

#ifndef NWEB_EXTENSION_DOWNLOADS_CEF_DELEGATE_H
#define NWEB_EXTENSION_DOWNLOADS_CEF_DELEGATE_H
#pragma once

#include "base/functional/callback.h"
#include "ohos_nweb/src/capi/browser_service/nweb_extension_downloads_types.h"
#include "arkweb/build/features/features.h"
#if BUILDFLAG(IS_ARKWEB_EXT)
#include "arkweb/ohos_nweb_ex/build/features/features.h"
#endif
#if BUILDFLAG(ARKWEB_NWEB_EX)
#include "ohos_nweb_ex/public/capi/nweb_extension_downloads_callbacks.h"
#endif

typedef base::OnceCallback<void(const FilenameSuggestion& suggestion)>
      FilenameChangedCallback;

using DownloadEraseCallback = base::RepeatingCallback<
    void(const std::optional<std::string>&, const std::vector<int32_t>&)>;

using DownloadsOpenCallback = base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadsRemoveFileCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadsPauseCallback = base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadsResumeCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadsCancelCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadsAcceptDangerCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadsSetUiOptionsCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadsShowCallback = base::RepeatingCallback<void(const std::optional<std::string>&)>;
using DownloadSearchCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&,
                                 const uint32_t,
                                 const std::vector<ExDownloadsItem>&)>;
using DownloadGetFileIconCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&,
                                 const std::string&)>;

using DownloadsIdCallback =
    base::RepeatingCallback<void(const std::optional<std::string>&, int downloadId)>;

namespace OHOS::NWeb {
class NWebExtensionDownloadCefDelegate {
 public:
  static NWebExtensionDownloadCefDelegate& GetInstance();

  // downloads.erase
  bool Erase(ExDownloadsQueryInfo& query, DownloadEraseCallback callback);
  void EraseCallback(int requestId,
                     const std::optional<std::string>& error,
                     const std::vector<int32_t>& eraseIds);

  // downloads.open
  bool Open(int downloadId,
            const std::optional<std::string>& contextType,
            const std::optional<bool>& includeIncognitoInfo,
            DownloadsOpenCallback callback);
  void OpenCallback(int requestId, const std::optional<std::string>& error);

  // downloads.removeFile
  bool RemoveFile(int downloadId,
                  const std::optional<std::string>& contextType,
                  const std::optional<bool>& includeIncognitoInfo,
                  DownloadsRemoveFileCallback callback);
  void RemoveFileCallback(int requestId, const std::optional<std::string>& error);

  // downloads.pause
  bool Pause(int downloadId,
             const std::optional<std::string>& contextType,
             const std::optional<bool>& includeIncognitoInfo,
             DownloadsPauseCallback callback);
  void PauseCallback(int requestId, const std::optional<std::string>& error);

  // downloads.resume
  bool Resume(int downloadId,
              const std::optional<std::string>& contextType,
              const std::optional<bool>& includeIncognitoInfo,
              DownloadsResumeCallback callback);
  void ResumeCallback(int requestId, const std::optional<std::string>& error);

  // downloads.cancel
  bool Cancel(int downloadId,
              const std::optional<std::string>& contextType,
              const std::optional<bool>& includeIncognitoInfo,
              DownloadsCancelCallback callback);
  void CancelCallback(int requestId, const std::optional<std::string>& error);

  // downloads.acceptDanger
  bool AcceptDanger(int downloadId,
                    const std::optional<std::string>& contextType,
                    const std::optional<bool>& includeIncognitoInfo,
                    DownloadsAcceptDangerCallback callback);
  void AcceptDangerCallback(int requestId, const std::optional<std::string>& error);

  // downloads.setUiOptions
  bool SetUiOptions(const ExDownloadsUiOptions& options,
                    DownloadsSetUiOptionsCallback callback);
  void SetUiOptionsCallback(int requestId, const std::optional<std::string>& error);

  // downloads.show
  bool Show(int downloadId,
            const std::optional<std::string>& contextType,
            const std::optional<bool>& includeIncognitoInfo,
            DownloadsShowCallback callback);
  void ShowCallback(int requestId, const std::optional<std::string>& error);

  // downloads.showDefaultFolder
  void ShowDefaultFolder();

  // downloads.search
  bool Search(ExDownloadsQueryInfo& query, DownloadSearchCallback callback);
  void SearchCallback(int requestId,
                      const std::optional<std::string>& error,
                      const uint32_t size,
                      const std::vector<ExDownloadsItem>& downloadItems);

  // downloads.download
  bool GetDownloadId(const std::string& guid, DownloadsIdCallback callback);
  void GetDownloadIdCallback(int requestId, const std::optional<std::string>& error, int downloadId);

  // downloads.getFileIcon
  bool GetFileIcon(ExDownloadsGetFileIconOptions& iconOption,
                   DownloadGetFileIconCallback callback);
  void GetFileIconCallback(int requestId,
                           const std::optional<std::string>& error,
                           const std::string& iconUrl);

  // getAllDownloadItem
  ExDownloadsItemVector GetAllDownloadItem();

  // downloads.OnCreated
  void OnCreated(ExDownloadsItem* item);

  // downloads.OnChanged
  void OnChanged(ExDownloadsItem* item);

  // downloads.OnErased
  void OnErased(int downloadId);

  // downloads.OnDeterminingFilename
  void OnDeterminingFilename(const ExDownloadsItem* item,
                             const char* suggestedPath,
                             FilenameChangedCallback callback);
};

}  // namespace OHOS::NWeb

#endif  // NWEB_EXTENSION_DOWNLOADS_CEF_DELEGATE_H