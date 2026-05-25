# 接口边界

本文用于判断改动应该落在哪一层，避免把接口、桥接和实现混在一起。

## 分层关系

```text
web_webview 系统侧
  ohos_nweb / ohos_interface
        ↓ C ABI
arkweb/glue
        ↓ cpptoc / ctocpp
arkweb/ohos_nweb
        ↓ CEF delegate
CEF / Chromium
```

`glue/` 是桥接契约，不是业务行为的归属层。`ohos_nweb/` 是 ArkWebCore 侧的 NWeb 接口实现层，不要称为 NWeb 内核。

## 放置规则

- WebView 对外 API 或接口契约变化，先找接口定义来源，再同步桥接层。
- 已有 NWeb 接口的 ArkWebCore 侧实现，优先放在 `ohos_nweb/src/` 或 `ohos_nweb/src/cef_delegate/`。
- 调 OpenHarmony 系统服务，放在 `ohos_adapter_ndk/`，不要直接塞进 NWeb 或 Chromium 扩展逻辑。
- 改 Chromium 行为，优先使用 `chromium_ext/`；只有无法解耦时才加 `patch/`。
- 生成的 cpptoc/ctocpp 文件不要手改，先找到生成输入。

## 常见映射

| 场景 | 常见落点 |
|---|---|
| `NWeb` 主流程 | `nweb_impl.cc`、`nweb_delegate_adapter.cc` |
| 引擎初始化/管理 | `nweb_engine_impl.cc` |
| Cookie、下载、WebStorage | `ohos_nweb/src/cef_delegate/` 对应 delegate |
| NDK/C API 表面 | `ohos_nweb/src/ndk/`、`ohos_nweb/src/capi/` |
| 系统能力适配 | `ohos_adapter_ndk/` |
