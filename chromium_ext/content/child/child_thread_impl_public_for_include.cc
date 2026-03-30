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

#if BUILDFLAG(ARKWEB_RENDERER_ANR_DUMP)
  void dumpCurrentJavaScriptStackInMainThread(
      dumpCurrentJavaScriptStackInMainThreadCallback callback) override {
    if (!webkit_inited_) {
      std::move(callback).Run("");
      return;
    }
#if !defined(COMPONENT_BUILD) // FIXME
    AnrDumper::GetInstance()->DumpCurrentJavaScriptStack(std::move(callback));
#endif
  }

  void InvokeRenderCrashDump() override {
    static int once_flag = true;
    if (once_flag) {
      LOG(INFO) << "dump render stack for input jank";
      kill(getpid(), SIGINT);
      once_flag = false;
    } else {
      LOG(INFO) << "only get stack once";
    }
  }

  void GetUid(GetUidCallback callback) override {
    std::move(callback).Run(static_cast<int32_t>(getuid()));
  }

#if defined(OS_OHOS)
  void ReportHicollie() override {
    HicollieReporter::SetFreezeMessage("render js freeze");
    HicollieReporter::ReportFreezeToHicollie();
  }
#endif
#endif

#if BUILDFLAG(ARKWEB_RENDERER_ANR_DUMP)
  bool webkit_inited_ = false;
#endif

#if BUILDFLAG(ARKWEB_LOGGER_REPORT)
void SetStrictLogMode(bool is_strict_log_mode) override {
  main_thread_task_runner_->PostTask(
      FROM_HERE, base::BindOnce(
                     [](bool is_strict_log_mode) {
                       blink::WebView::SetStrictLogMode(is_strict_log_mode);
                     },
                     is_strict_log_mode));
}
#endif
