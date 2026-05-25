# ArkWeb Chromium 适配层指引

## 项目定位

本仓库是 ArkWeb 对 Chromium 原生代码的解耦和适配层，对应 OpenHarmony 中的 Chromium 引擎部分。核心职责是将 Chromium 的侵入式修改隔离到独立目录，保持上游代码可同步更新。

仓库内代码最终编译为 **ArkWebCore.hap**（包名 `com.ohos.arkwebcore`），由 `openharmony/web_webview` 的 `ohos_nweb/` 加载使用。

## 快速路由

- `chromium_ext/`：Chromium 侵入式修改的解耦层，按 Chromium 模块组织；核心注册文件是 `chromium_ext.gni`。
- `ohos_nweb/`：ArkWeb 侧 NWeb 接口实现层，通过 CEF delegate 将 Chromium 能力暴露给系统侧。
- `ohos_adapter_ndk/`：OpenHarmony 系统服务适配层，包含 adapter、mock 和 stub。
- `glue/`：从 WebView 侧同步的桥接契约，不承载业务行为。
- `build/`：构建脚本、GN 配置、特性开关和签名流程。
- `patch/`：对 Chromium 原始源码或第三方代码的最小化补丁。

构建入口是 `build/build.sh`。提交使用 `git commit -s`（DCO 签名）。

## 知识索引

稳定背景知识放在 `docs/knowledge/`。改动前先按目录定位，再读取对应文档：

| 场景 | 先读 |
|---|---|
| 顶层目录职责、模块边界、术语约定 | `docs/knowledge/module-map.md` |
| Chromium 扩展组织、源码注册、特性开关 | `docs/knowledge/chromium-ext-architecture.md` |
| 构建入口、GN args、`BUILDFLAG` 链路 | `docs/knowledge/build-system.md` |
| WebView/glue/NWeb/CEF 接口边界 | `docs/knowledge/interface-boundary.md` |
| OHOS 系统服务适配、mock/stub | `docs/knowledge/ohos-adapter-ndk.md` |
| Chromium 补丁、生成代码、UT/fuzzer | `docs/knowledge/patch-and-test-workflow.md` |

## 核心规则

- chromium_ext 中的代码按 Chromium 模块组织，每个子目录对应 Chromium 源码中的一个模块；目录结构可通过 `find chromium_ext -maxdepth 1` 获取。
- 新增扩展文件必须在 `chromium_ext.gni` 中注册，否则不会参与编译。
- 补丁（`patch/`）应最小化，仅包含无法通过 chromium_ext 解耦的必要修改。
- `ohos_nweb/cef_delegate` 中的 delegate 类实现 `ohos_interface` 定义的 NWeb 接口；新增接口能力需先确认接口定义归属。
- OpenHarmony 系统服务调用优先放入 `ohos_adapter_ndk/`，不要直接散落到 NWeb 或 Chromium 扩展逻辑中。
- 特性开关在 `build/features/features.gni` 中声明，通过 `arkweb_<feature>` 命名，并经 `BUILD.gn` 导出到 `BUILDFLAG(...)`。
- 不要手改 bridge、cpptoc、ctocpp 或 CEF wrapper 的生成物，先找生成输入。
- Code Owner：@ringking0
