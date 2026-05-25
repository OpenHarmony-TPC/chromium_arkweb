# chromium_ext 架构详解

本文记录 `chromium_ext/` 的设计意图和改动规则，不重复目录枚举。

## 为什么需要 chromium_ext

Chromium 是庞大的上游项目，ArkWeb 需要在其基础上做大量适配。直接修改 Chromium 源码会导致：

- 无法稳定同步上游更新。
- 合并冲突频繁且难解。
- 适配逻辑散落在上游目录，难以维护和审查。

`chromium_ext/` 的目标是：**将 ArkWeb 扩展代码隔离到独立目录**，Chromium 原始代码仅通过少量补丁接入这些扩展。

## 目录组织原则

`chromium_ext/` 通常按 Chromium 模块分目录，具体目录可直接 `find chromium_ext -maxdepth 1` 查看。AI 不应把目录清单当成知识；真正需要记住的是以下特例和规则：

- `content/` 往往涉及 renderer/browser/gpu/child 等多进程边界，改动前要先确认进程归属。
- `dfx/`、`ohos_test/`、`pdf/` 等目录不一定有完整的 Chromium 上游一一映射。
- `third_party/` 下的适配要区分是 ArkWeb 扩展还是第三方源码补丁。
- `cef/` 下多为 CEF 扩展接口，和 `ohos_nweb/src/cef_delegate/` 的 NWeb 实现不是同一层。
- `servieces/` 是历史目录名，新增代码前先确认是否应放入 `service/` 或 `services/`。

## 源文件注册

`chromium_ext/` 下新增源码后，必须注册到 `chromium_ext.gni` 对应的 `arkweb_*_sources` 变量，再确认 Chromium 对应 BUILD 目标是否通过补丁或现有 GN 逻辑引用该变量。

新增扩展文件时检查：

1. 所属 Chromium 模块是否明确。
2. 源文件是否放在 `chromium_ext/<module>/` 的对应子目录。
3. `chromium_ext.gni` 是否注册。
4. 是否需要特性开关。
5. 是否需要修改 Chromium 原始 BUILD.gn；如需要，应放入 `patch/` 且保持最小化。

## 特性开关

ArkWeb 特性开关的稳定链路是：

```text
build/features/features.gni
  arkweb_<feature>
        ↓
build/features/BUILD.gn
  ARKWEB_<FEATURE>
        ↓
arkweb/build/features/features.h
        ↓
BUILDFLAG(ARKWEB_<FEATURE>)
```

新增开关时不要只改 C++ 宏，也不要只改 GN 条件。应同时检查声明、buildflag 导出、源码注册和使用点。

## NWeb 接口实现层

`ohos_nweb/src/cef_delegate/` 是 ArkWebCore 侧承接 NWeb 接口的重要实现目录，按功能命名实现 delegate。它不是“内核”，不要使用“NWeb 内核”这类表述。

数据流简化为：

```text
web_webview 系统侧
  ohos_interface
        ↓ C ABI / glue
arkweb/ohos_nweb
        ↓ cef_delegate
CEF / Chromium
```

如果改动涉及 NWeb 接口实现，优先检查 `ohos_nweb/src/nweb_impl.cc`、`ohos_nweb/src/nweb_delegate_adapter.cc` 以及 `cef_delegate/` 中对应功能文件。

## 补丁原则

`patch/` 只放无法通过 `chromium_ext/` 解耦的必要修改，例如 BUILD.gn 接入、include 路径或必须触达的上游逻辑。

- 新功能优先放在 `chromium_ext/`。
- 补丁按模块归档并使用编号前缀保持应用顺序。
- 每个补丁应尽量小，避免把 ArkWeb 业务逻辑直接写进 Chromium 原始源码。

## 新增扩展文件检查清单

- [ ] 确定所属 Chromium 模块，在 `chromium_ext/<module>/` 下创建文件。
- [ ] 在 `chromium_ext.gni` 中注册到对应 sources 变量。
- [ ] 需要特性开关时，在 `features.gni` 和 `build/features/BUILD.gn` 中同步声明。
- [ ] 需要修改 Chromium 原始 BUILD.gn 时，创建最小补丁放入 `patch/`。
- [ ] 涉及 NWeb 接口实现时，在 `ohos_nweb/src/cef_delegate/` 或对应 NWeb 实现文件中处理。
- [ ] 涉及系统服务调用时，在 `ohos_adapter_ndk/` 对应适配器中处理。
- [ ] 添加对应单元测试，文件名遵循 `_unittest.cc` 约定。

## 相关文档

- [module-map.md](module-map.md)
- [build-system.md](build-system.md)
- [interface-boundary.md](interface-boundary.md)
- [ohos-adapter-ndk.md](ohos-adapter-ndk.md)
- [patch-and-test-workflow.md](patch-and-test-workflow.md)
