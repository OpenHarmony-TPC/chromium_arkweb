# chromium_ext 架构详解

> 本文档说明 chromium_arkweb 仓库中 chromium_ext 的设计原理、目录组织和扩展规范。

## 为什么需要 chromium_ext？

Chromium 是一个庞大的上游项目，ArkWeb 需要在其基础上做大量适配。直接修改 Chromium 源码会导致：
- 无法同步上游更新
- 合并冲突频繁且难解
- 适配逻辑散落各处难以维护

chromium_ext 的设计目标：**将所有 ArkWeb 扩展代码隔离到独立目录**，Chromium 原始代码仅通过少量补丁（patch/）修改。

## 目录映射

chromium_ext 的子目录与 Chromium 源码一一对应：

| chromium_ext 目录 | Chromium 对应 | 主要扩展内容 |
|---|---|---|
| `base/` | `base/` | 系统信息（ohos/）、帧率上报、内存管理、日志扩展 |
| `blink/` | `third_party/blink/` | Blink 渲染引擎扩展 |
| `cc/` | `cc/` | 合成器扩展（input/layer/scheduler/trees） |
| `cef/` | `cef/` | CEF 接口定义 |
| `chrome/` | `chrome/` | Chrome 模块扩展（renderer、企业策略、browser） |
| `components/` | `components/` | 组件扩展（40+ 子目录：crashpad、os_crypt、autofill、pdf、permissions 等） |
| `content/` | `content/` | **最核心**：renderer/browser/gpu 进程、child/common/public/shell |
| `device/` | `device/` | 设备相关（bluetooth、fido） |
| `dfx/` | — | DFX 可观测性扩展 |
| `extensions/` | `extensions/` | 扩展模块（browser/common/renderer） |
| `gpu/` | `gpu/` | GPU 相关（command_buffer/vulkan/ipc/config） |
| `ipc/` | `ipc/` | IPC 扩展 |
| `media/` | `media/` | 媒体播放器适配（audio/capture/cdm/renderers/video/ffmpeg） |
| `mojo/` | `mojo/` | Mojo 扩展 |
| `net/` | `net/` | 网络层适配（dns/http/ssl/proxy_resolution/websockets/socket 等） |
| `ohos_test/` | — | OH 专项测试（fuzztest/unittest） |
| `pdf/` | — | PDF 扩展（pdfium） |
| `sandbox/` | `sandbox/` | 沙箱策略（seccomp-bpf-helpers） |
| `service/` | `services/` | 服务扩展（device） |
| `services/` | `services/` | 服务扩展（device/network/shape_detection） |
| `skia/` | `skia/` | Skia 扩展 |
| `storage/` | `storage/` | 存储扩展（browser） |
| `third_party/` | `third_party/` | 第三方库适配（angle/blink/crashpad/skia/vulkan-headers/webrtc 等） |
| `ui/` | `ui/` | UI 事件处理（events/gl/native_theme/ozone/touch_selection/views 等） |
| `url/` | `url/` | URL 扩展（ohos 适配） |
| `v8/` | `v8/` | V8 引擎扩展（dfx/heap_dump/src、性能 JIT、龙雀 builtins） |

## 源文件注册机制

所有 chromium_ext 下的源文件通过 `chromium_ext.gni` 注册为 GN 变量（约 1500 行）：

```gni
# chromium_ext/chromium_ext.gni
arkweb_content_renderer_sources = [
  "//arkweb/chromium_ext/content/renderer/host_proxy.cc",
  "//arkweb/chromium_ext/content/renderer/renderer_engine_event.cc",
  "//arkweb/chromium_ext/content/renderer/media/ohos/ohos_media_player_renderer_client.cc",
]

arkweb_base_ohos_sources = [
  "//arkweb/chromium_ext/base/ohos/sys_info_utils_ext.cc",
]
```

Chromium 原始 BUILD.gn 通过补丁引用这些变量，将扩展源文件加入对应编译目标。

**新增扩展文件时**，必须：
1. 在 `chromium_ext/` 对应模块下创建源文件
2. 在 `chromium_ext.gni` 中注册到对应的 `arkweb_*_sources` 变量
3. 确认 Chromium 对应 BUILD.gn 已通过补丁引用该变量

## 特性开关

`build/features/features.gni` 定义了 100+ 个 `arkweb_*` 特性开关：

```gni
declare_args() {
  arkweb_accessibility = true
  arkweb_ai = true
  arkweb_custom_video_player = true
  arkweb_darkmode = true
  arkweb_devtools = true
  arkweb_notification = true
  arkweb_dfx_tracing = true
  # ... 100+
}
```

### 使用方式

在 chromium_ext 代码中通过 GN 条件判断：

```gni
if (arkweb_custom_video_player) {
  sources += [ "media/ohos/ohos_media_player_renderer_client.cc" ]
}
```

在 C++ 代码中通过预处理宏：

```cpp
#if BUILDFLAG(ARKWEB_CUSTOM_VIDEO_PLAYER_ENABLED)
#include "media/ohos/ohos_media_player_renderer_client.h"
#endif
```

### 新增特性开关

1. 在 `features.gni` 的 `declare_args()` 中添加 `arkweb_<feature> = true/false`
2. 在 `build/features/BUILD.gn` 中添加对应的 `enable_<feature>` 定义
3. 在 chromium_ext.gni 中用条件包裹相关源文件

## NWeb 接口实现层

### CEF Delegate 模式

`ohos_nweb/src/cef_delegate/` 是 ArkWeb 侧承接 NWeb 接口的核心目录（200+ 文件），实现了 CEF（Chromium Embedded Framework）的 delegate 接口：

```
ohos_nweb/src/cef_delegate/
├── nweb_application.cc                    ← 应用生命周期
├── nweb_delegate_adapter.cc/h            ← 核心适配器
├── nweb_accessibility_*_delegate.cc/h    ← 无障碍 delegate
├── nweb_cookie_manager_delegate.cc/h     ← Cookie 管理 delegate
├── nweb_web_storage_delegate.cc/h        ← WebStorage delegate
├── nweb_download_manager_delegate.cc/h   ← 下载管理 delegate
├── custom_media_player_impl.cc/h         ← 自定义媒体播放器
├── ark_web_*_impl.cc/h                   ← 各种接口实现
├── nweb_autolayout.cc/h                  ← 自动布局
├── nweb_content_change_detection.cc/h    ← 内容变化检测
└── ... (200+ 文件)
```

**数据流**：
```
web_webview (系统侧)                    chromium_arkweb (ArkWebCore 侧)
  ohos_nweb/                              ohos_nweb/
    ↓ NWebHelper::CreateNWeb()              ↓ cef_delegate/
  ohos_interface/ ← C ABI → glue/         ← C ABI 桥接
    (纯虚接口)        (bridge/cpptoc/ctocpp)  (delegate 实现)
```

### delegate 接口映射

| ohos_interface 接口 | cef_delegate 实现 |
|---|---|
| `NWeb` | `nweb_impl.cc` + `nweb_delegate_adapter.cc` |
| `NWebEngine` | `nweb_engine_impl.cc` |
| `NWebCookieManager` | `nweb_cookie_manager_delegate.cc` |
| `NWebDownloadManager` | `nweb_download_manager_delegate.cc` |
| `NWebDataBase` | `nweb_data_base_impl.cc` |
| `NWebWebStorage` | `nweb_web_storage_delegate.cc` |

## 补丁管理

`patch/` 目录包含对 Chromium 原始源码的最小化补丁：

```
patch/
├── build/                  ← 构建系统补丁
│   ├── 001_build_ohos_new_folder.patch
│   ├── 002_build_adapt_arkweb_target.patch
│   ├── 003_build_config_declare_ohos_package_name.patch
│   └── 004_add_sanitizer_config.patch
├── components/             ← 组件补丁
│   ├── crash/
│   └── 001_add_ohos_crashpad.patch
└── third_party/            ← 第三方库补丁
    └── crashpad/
```

**补丁原则**：
- 编号前缀保证应用顺序
- 仅包含无法通过 chromium_ext 解耦的必要修改（如 BUILD.gn 引用、include 路径）
- 新增功能优先放在 chromium_ext 中，补丁作为最后手段

## 其他模块

### ohos_adapter_ndk（系统适配层）

40 个适配器子目录，每个适配器封装对特定 OpenHarmony 系统服务的调用。关键适配器：

| 适配器 | 对接的系统能力 |
|---|---|
| `graphic_adapter/` | 图形渲染 |
| `hiviewdfx_adapter/` | HiLog/HiSysEvent/HiTrace |
| `multimodalinputnew_adapter/` | 触摸/按键/鼠标输入 |
| `inputmethodframework_adapter/` | 输入法 |
| `pasteboard_adapter/` | 剪贴板 |
| `net_connect_adapter/` | 网络连接 |
| `display_manager_adapter/` | 屏幕显示 |
| `window_manager_adapter/` | 窗口管理 |
| `media_adapter/` | 媒体播放 |
| `audio_capturer_adapter/` | 音频采集 |

适配器提供三种实现：`mock_ndk_api/`（单元测试 Mock）、`stub/`（空实现）、实际适配实现。

### ohos_nweb_turbo（DFX 工具）

- `tools/dfx_url_loadTime_statistics/` — HarmonyOS 应用，统计 URL 加载耗时
- `tools/web_trace_parser_oh/` — Python 工具，解析 Chromium trace 数据

### ohos_autolayout（自动布局引擎）

ArkTS 实现的自动布局引擎（JavaScript/TypeScript），含 Alphabet 键盘布局等组件，独立于 Chromium 引擎。

### ohos_browser_shell（测试 Shell）

HarmonyOS 应用，作为 WebView 的测试容器，使用 hvigor 构建系统。

## 新增扩展文件检查清单

- [ ] 确定所属 Chromium 模块，在 `chromium_ext/<module>/` 下创建文件
- [ ] 在 `chromium_ext.gni` 中注册到对应的 sources 变量
- [ ] 是否需要特性开关？在 `features.gni` 中声明
- [ ] 是否需要修改 Chromium 原始 BUILD.gn？创建补丁放在 `patch/`
- [ ] 如果涉及 NWeb 接口实现，在 `ohos_nweb/src/cef_delegate/` 中创建 delegate
- [ ] 如果涉及系统服务调用，在 `ohos_adapter_ndk/` 对应适配器中添加
- [ ] 添加对应的单元测试（含 `_unittest.cc` 后缀）

## 相关文档

- [glue/README.md](../../glue/README.md) — 胶水层说明
- [ohos_nweb/README.md](../../ohos_nweb/README.md) — NWeb 编译和运行说明
- [AGENTS.md](../AGENTS.md) — 代码仓指引
