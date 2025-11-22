// Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "content/renderer/renderer_main_platform_delegate.h"

#include "base/check_op.h"
#include "base/command_line.h"
#include "sandbox/policy/sandbox.h"
#include "sandbox/policy/sandbox_type.h"

namespace content {

RendererMainPlatformDelegate::RendererMainPlatformDelegate(
    const MainFunctionParams& parameters) {}

RendererMainPlatformDelegate::~RendererMainPlatformDelegate() {
}

void RendererMainPlatformDelegate::PlatformInitialize() {
}

void RendererMainPlatformDelegate::PlatformUninitialize() {
}

bool RendererMainPlatformDelegate::EnableSandbox() {
  sandbox::policy::SandboxLinux::Options options;
  sandbox::policy::Sandbox::Initialize(
      sandbox::policy::SandboxTypeFromCommandLine(
          *base::CommandLine::ForCurrentProcess()),
      sandbox::policy::SandboxLinux::PreSandboxHook(), options);

  // about:sandbox uses a value returned from SandboxLinux::GetStatus() before
  // any renderer has been started.
  // Here, we test that the status of SeccompBpf in the renderer is consistent
  // with what SandboxLinux::GetStatus() said we would do.
  auto* ohos_sandbox = sandbox::policy::SandboxLinux::GetInstance();
  if (ohos_sandbox->GetStatus() & sandbox::policy::SandboxLinux::kSeccompBPF) {
    CHECK(ohos_sandbox->seccomp_bpf_started());
  }

  return true;
}

}  // namespace content
