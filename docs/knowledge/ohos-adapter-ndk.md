# OHOS NDK 适配层

`ohos_adapter_ndk/` 是 ArkWebCore 调 OpenHarmony 系统服务的适配层。它的价值是把平台 API、数据转换、mock/stub 和上层浏览行为隔离开。

## 使用时机

以下改动优先看 `ohos_adapter_ndk/`：

- 网络、代理、网络状态。
- 剪贴板、输入法、窗口、显示、图形 buffer。
- 媒体、音频、DRM、录屏。
- 定位、传感器、电量、系统属性。
- DFX、HiLog、HiTrace、HiSysEvent。
- 安全、权限、证书、密钥。

## 修改规则

- 新增系统能力时，先确认 `interfaces/` 是否已有抽象，不要重复造接口。
- 具体实现放在对应 `*_adapter/` 目录，并注册到 `ohos_adapter_ndk/BUILD.gn`。
- 如果依赖 OHOS SDK 动态库，确认不同 `target_cpu` 分支都补齐。
- 可测试路径要补 `mock_ndk_api/` 或 stub，避免单测只能在真机环境跑。
- adapter 只做平台调用和数据转换，不承载 Web 行为决策。

## 检查清单

- 源文件已进 GN。
- include/lib 路径覆盖目标架构。
- mock/stub 与真实实现的返回语义一致。
- 上层代码依赖接口抽象，而不是直接依赖平台 NDK 细节。
