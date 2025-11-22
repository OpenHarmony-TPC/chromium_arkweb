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

  ///
  /// Clears the client authentication certificate Cache that were added
  /// as part of handling CefRequestHandler::OnSelectClientCertificate().
  /// If |callback| is non-NULL it will be executed on the UI thread after
  /// completion.
  ///
  /*--cef(optional_param=callback)--*/
#if BUILDFLAG(ARKWEB_CERT_AUTHENTICATION)
  virtual void ClearClientAuthenticationCache(
      CefRefPtr<CefCompletionCallback> callback) {};
#endif  // ARKWEB_CERT_AUTHENTICATION

  virtual CefRefPtr<CefWebStorage> GetWebStorage(
      CefRefPtr<CefCompletionCallback> callback) { return nullptr; };