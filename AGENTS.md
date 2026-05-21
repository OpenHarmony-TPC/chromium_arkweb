# ArkWeb Chromium 适配层指引

## 项目定位

本仓库是 ArkWeb 对 Chromium 原生代码的解耦和适配层，对应 OpenHarmony 中的 Chromium 引擎部分。核心职责是将 Chromium 的侵入式修改隔离到独立目录，保持上游代码可同步更新。

仓库内的代码最终编译为 **ArkWebCore.hap**（Chromium 引擎预编译包，包名 `com.ohos.arkwebcore`），被 `openharmony/web_webview` 的 `ohos_nweb/` 加载使用。

主要关注以下目录：

- `chromium_ext/`：Chromium 侵入式修改的解耦层，按 Chromium 模块组织扩展代码
- `ohos_nweb/`：nweb 内核侧实现，通过 CEF delegate 将 Chromium 能力暴露给系统侧
- `ohos_adapter_ndk/`：系统适配层 NDK 封装，40 适配器对接 OpenHarmony 系统服务
- `build/`：构建系统，含特性开关（features.gni）、构建脚本、工具链配置
- `patch/`：对上游 Chromium 源码的补丁，最小化侵入
- `glue/`：胶水层接口定义（从 web_webview 的 ohos_interface 同步）
- `ohos_autolayout/`：ArkTS 自动布局引擎（独立模块）
- `ohos_browser_shell/`：测试用浏览器 Shell（HarmonyOS 应用）
- `ohos_nweb_turbo/`：DFX 工具（URL 加载耗时统计、trace 解析）

## 构建和验证

构建命令在配置好 OpenHarmony 源码环境后执行：

```sh
# 完整构建 ArkWebCore.hap
./build/build.sh --product-name rk3568

# 构建特定模块
./build/build.sh --product-name rk3568 --build-target arkweb_nweb
./build/build.sh --product-name rk3568 --build-target arkweb_adapter_ndk

# 单元测试
./build/build.sh --product-name rk3568 --build-target arkweb_unittest
```

编译产出：
- `libarkweb_engine.so` — Chromium 内核 + CEF 框架实现
- `libarkweb_renderer` — render 子进程入口

提交使用 `git commit -s`（DCO 签名）。

## 知识索引

稳定背景知识放在 `docs/knowledge/`。改动前按场景读取对应文件：

| 场景 | 先读 |
|------|------|
| chromium_ext 目录组织、侵入式修改规范、新增扩展文件 | `docs/knowledge/chromium-ext-architecture.md` |
| 特性开关（features.gni）、条件编译、新增特性 | `docs/knowledge/chromium-ext-architecture.md` 的"特性开关"章节 |
| nweb 内核侧实现、CEF delegate、delegate 接口 | `docs/knowledge/chromium-ext-architecture.md` 的"nweb 内核侧"章节 |

## 核心架构

### chromium_ext：侵入式修改解耦

```
chromium_ext/
├── base/           ← base 模块扩展（系统信息、帧率、内存等）
├── blink/          ← Blink 渲染引擎扩展
├── cc/             ← 合成器扩展（input/layer/scheduler/trees）
├── cef/            ← CEF 接口扩展
├── chrome/         ← Chrome 模块扩展（企业策略、renderer 等）
├── components/     ← 组件扩展（40+ 子目录：crash、os_crypt、autofill、pdf 等）
├── content/        ← content 模块扩展（renderer/browser/gpu/child/common/public/shell）
├── device/         ← 设备相关扩展（bluetooth、fido）
├── dfx/            ← DFX（可观测性）扩展
├── extensions/     ← 扩展模块（browser/common/renderer）
├── gpu/            ← GPU 相关扩展（command_buffer/vulkan/ipc）
├── ipc/            ← IPC 扩展
├── media/          ← 媒体扩展（audio/capture/cdm/renderers/video 等）
├── mojo/           ← Mojo 扩展
├── net/            ← 网络扩展（dns/http/ssl/proxy_resolution/websockets 等）
├── ohos_test/      ← OH 测试（fuzztest/unittest）
├── pdf/            ← PDF 扩展
├── sandbox/        ← 沙箱扩展（seccomp-bpf）
├── service/        ← 服务扩展
├── services/       ← 服务扩展（device/network/shape_detection）
├── skia/           ← Skia 扩展
├── storage/        ← 存储扩展
├── third_party/    ← 第三方库适配（angle/blink/crashpad/skia/vulkan 等）
├── ui/             ← UI 扩展（events/gl/ozone/native_theme/touch_selection/views）
├── url/            ← URL 扩展
├── v8/             ← V8 引擎扩展（dfx/heap_dump/src）
├── chromium_ext.gni ← 源文件注册（~1500 行，所有扩展文件在此声明）
└── BUILD.gn
```

**设计原则**：所有对 Chromium 的侵入式扩展代码放在 `chromium_ext/` 下对应的模块子目录中，通过 `chromium_ext.gni` 统一注册源文件。Chromium 原始代码通过补丁（`patch/`）最小化修改，保持与上游的可同步性。

### ohos_nweb：内核侧 nweb 实现

```
ohos_nweb/
├── include/        ← 公共头文件（nweb_errors.h）
├── src/
│   ├── cef_delegate/  ← CEF delegate 实现（200+ 文件，核心）
│   ├── capi/          ← C API 接口
│   ├── ndk/           ← NDK 接口（common/scheme_handler）
│   ├── download/      ← 下载管理
│   ├── native_media_player/ ← 原生媒体播放器
│   ├── sysevent/      ← 系统事件
│   ├── video_assistant/ ← 视频辅助
│   ├── nweb_impl.cc/h  ← NWeb 核心实现
│   ├── nweb_engine_impl.cc/h ← 引擎实现
│   ├── nweb_delegate_adapter.cc/h ← delegate 适配
│   └── ...
├── browser/
│   └── performance_manager/ ← 性能管理（mechanisms/policies）
├── test/
├── config.gni       ← 包名配置（com.ohos.arkwebcore）
└── BUILD.gn
```

**核心机制**：`cef_delegate/` 下的文件实现了 `web_webview` 中 `ohos_interface/include/ohos_nweb/` 定义的接口，是胶水层 nweb 方向的"内核侧实现"。

### ohos_adapter_ndk：系统适配 NDK 封装

```
ohos_adapter_ndk/
├── graphic_adapter/          ← 图形显示
├── hiviewdfx_adapter/        ← DFX 适配
├── multimodalinputnew_adapter/ ← 输入适配
├── audio_capturer_adapter/   ← 音频采集
├── media_adapter/            ← 媒体
├── net_connect_adapter/      ← 网络连接
├── pasteboard_adapter/       ← 剪贴板
├── display_manager_adapter/  ← 显示管理
├── window_manager_adapter/   ← 窗口管理
├── inputmethodframework_adapter/ ← 输入法
├── interfaces/               ← 接口定义
├── mock_ndk_api/             ← Mock 实现（单元测试用）
├── stub/                     ← Stub 实现
└── ... (40 适配器)
```

**与 web_webview 的关系**：这里实现的是 `web_webview` 中 `ohos_interface/include/ohos_adapter/` 定义的接口，是胶水层 adapter 方向的"内核侧实现"（在 Chromium 进程内调用 OpenHarmony 系统服务）。

## 项目约束

- chromium_ext 中的代码按 Chromium 模块组织，每个子目录对应 Chromium 源码中的一个模块
- 新增扩展文件必须在 `chromium_ext.gni` 中注册，否则不会参与编译
- 补丁（patch/）应最小化，仅包含无法通过 chromium_ext 解耦的必要修改
- ohos_nweb/cef_delegate 中的 delegate 类实现 ohos_interface 定义的接口，新增功能需先在 ohos_interface 中定义
- 特性开关在 `build/features/features.gni` 中声明，通过 `arkweb_<feature>` 命名，构建时可通过 args.gn 覆盖
- 提交须带 DCO 签名（`git commit -s`）
- Code Owner：@ringking0
