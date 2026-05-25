# 构建与特性开关

本文只记录 AI 容易误判的构建规则。具体参数以 `build/build.sh` 和 `build/features/` 为准。

## 入口选择

- 日常构建从 `build/build.sh` 进入，不要绕过 `prepare.sh` 和 `cef/tools/translator.sh`，否则 bridge/CEF 相关生成物可能不是最新。
- `ohos_nweb_hap` 不是普通单目标构建：脚本会先处理 ArkWeb prebuild，再重新生成 GN args。
- 单测目标会额外打开 `arkweb_test=true`，排查测试编译问题时要确认是否走了 `coreut`、`allut` 或 `smokeut` 路径。
- `-G` 只适合追加临时 GN args，不应把长期配置藏在命令行里。

## 特性开关规则

ArkWeb 特性开关一般走这条链路：

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

新增特性时需要同时检查：

- `features.gni` 是否声明了 `arkweb_<feature>`。
- `BUILD.gn` 是否导出了对应 `ARKWEB_<FEATURE>`。
- C++ 是否通过 `BUILDFLAG(...)` 判断，而不是散落自定义宏。
- 相关源文件是否在 GN 中按特性条件注册。

不要新增和现有 `arkweb_*` 语义重复的开关。先搜索相近功能名，再决定是否新增。
