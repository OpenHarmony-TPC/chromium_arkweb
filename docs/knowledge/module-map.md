# 模块路由

本文是改动归属速查。目录里能直接看出来的文件清单不在这里重复。

| 要改什么 | 优先看哪里 |
|---|---|
| Chromium 模块行为扩展 | `chromium_ext/` |
| NWeb 接口实现、CEF delegate、WebView 面向能力 | `ohos_nweb/` |
| OpenHarmony 系统服务调用 | `ohos_adapter_ndk/` |
| WebView 与 ArkWebCore 桥接契约 | `glue/` |
| 构建参数、GN args、特性开关 | `build/` |
| 必须修改 Chromium 原始源码 | `patch/` |
| 单测、fuzzer、过滤列表、设备数据 | `test/`、`ut_tools/` |
| 自动布局 ArkTS 逻辑 | `ohos_autolayout/` |
| 测试壳应用 | `ohos_browser_shell/` |
| DFX 分析工具 | `ohos_nweb_turbo/` |

## 容易放错的位置

- 平台服务调用不要直接写进 `chromium_ext/`，通常应先经过 `ohos_adapter_ndk/`。
- `ohos_nweb/` 不是内核层，而是 ArkWebCore 侧 NWeb 接口实现层。
- 能通过 `chromium_ext/` 解耦的，不要优先加 Chromium 原始源码补丁。
- 新增源码文件后必须检查所属 GN target 是否注册。
