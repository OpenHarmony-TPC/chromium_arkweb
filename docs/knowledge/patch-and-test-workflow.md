# 补丁与测试

本文记录容易影响维护性的规则，具体 target 以对应 `BUILD.gn` 为准。

## 补丁策略

ArkWeb 优先把 Chromium 侧改动放到 `chromium_ext/`，`patch/` 只作为无法解耦时的兜底。

提交补丁前先判断：

- 是否能新增 `chromium_ext/<module>/` 文件解决。
- 是否只需要在 GN 中接入扩展源文件。
- 是否真的必须改 Chromium 原始源码。

如果必须加 `patch/`：

- 按上游模块放入 `patch/build/`、`patch/components/` 或 `patch/third_party/`。
- 保持补丁小而集中。
- 编号前缀要能表达应用顺序。
- 说明为什么不能通过 `chromium_ext/` 解耦。

## 生成代码

`build/build.sh` 会调用 `prepare.sh` 和 CEF translator。涉及 bridge、cpptoc、ctocpp 或 CEF 包装代码时，先找生成输入，避免手改生成物。

## 测试落点

- C++ 单测使用本仓已有 `_unittest.cc` 风格，并注册到最近的 `BUILD.gn`。
- 如果涉及 `ohos_adapter_ndk/`，同步考虑 mock/stub。
- 新增测试不要只挂在局部 target，确认能被聚合 UT target 覆盖。
- fuzzer 走 `-fuzzer` 相关构建路径，再用 GN 查询具体 fuzzer target。
