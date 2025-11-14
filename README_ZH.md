# ArkWeb 项目

## 1. 概述

ArkWeb 项目是一个全面的解决方案，旨在将 Chromium Web 引擎集成到 OpenHarmony (OHOS) 操作系统中。它作为系统 `Web` 组件的基础，为 OHOS 应用程序提供强大的 Web 渲染能力。

本项目是对 Chromium 源代码的扩展和增强，以使其适应 OHOS 架构和 API，并在原有功能的基础上，基于Openharmoy平台扩展了很多新性，如广告拦截，任务下载，输入框填充等。它包括一个API接口实现层、对核心 Chromium 模块的扩展，以及OS适配层。

## 2. 架构

项目遵循分层架构，图中Arkweb模块即本仓内容：

![image.png](https://raw.gitcode.com/user-images/assets/4769982/f0474dbd-355e-4f6d-ae2d-2658515187e0/image.png 'image.png')
1.  **API接口实现层 (`ohos_nweb`)**：Web相关的API在web内核侧的最上层的实现，该实现层依赖cef、chromium，以及libs通用库。通过调用cef和chromium中content层提供的接口，实现了web的功能，并扩展了如广告拦截，任务下载，输入框填充等openharmoy特有的功能。
2.  **CEF，Chromium扩展层 (`ohos_cef_ext、chromium_ext`)**：对原生CEF和Chromium的模块（例如 `base`、`blink`、`content`、`net`）进行的定制和平台特定实现的扩展。
3.  **OS适配层 (`ohos_adapter_ndk`)**：对 OpenHarmony 原生 NDK 和系统服务（例如网络、图形、输入和窗口管理）的调用的封装层

## 3. 目录结构

```
├── arkweb
│   ├── chromium_ext               # 对chromium解耦出的文件放到此目录，内部子目录与chromium仓目录一一对应
│   │  ├── build                                       
│   │  ├── components                            
│   │  ├── content                                 
│   │  ├── gpu    
│   │  └── net
│   ├── ohos_cef_ext               # 对cef解耦出的文件放到此目录，内部子目录与cef仓目录一一对应
│   ├── build                      # 编译arkweb相关目录
│   ├── glue                       # 胶水层代码，适配系统组件
│   ├── ohos_nweb                  # 向 OHOS 开发者的公共 API的实现，用于在他们的应用程序中嵌入 Webview
│   ├── ohos_autolayout            # 自动布局功能的资源和逻辑
│   ├── ohos_adapter_ndk           # 对 OpenHarmony 原生 NDK 和系统服务（例如网络、图形、输入和窗口管理）的调用的封装层
│   ├── code_version_update_tools  # 内核升级工具相关代码
│   ├── patch                      # 相关代码
│   ├── test                       # 测试相关代码

```


## 4.使用说明
1. 下载代码：以132_trunk分支为例，要下载其他分支代码请替换-b 后带的manifest分支参数，参数列表详见7。
    ```
    repo init -u https://gitcode.com/openharmony-tpc/manifest -b 132_trunk -m developer.xml --no-repo-verify
    repo sync -c
    repo forall -c 'git lfs pull'
    ```

2. 编译
   
    编译同时构建未签名Hap包：
	
	形态：rk3568
	```
	./build.sh  -t w -A rk3568
    ```
    仅编译so库：
	```
	./build.sh -A rk3568
    ```
	
	形态：rk3568_64
	```
	./build.sh  -t w -A rk3568_64
    ```
    仅编译so库：
	```
	./build.sh -A rk3568_64
    ```

3. 签名

    形态：rk3568
    ```
    ./sign.sh rk3568
    ```
    形态：rk3568_64
    ```
    ./sign.sh rk3568_64
    ```

4. 调试方法

    方法一：替换so库

    编译完成后，在out目录下找到对应so库产物，将它们推送到设备中
    ```
    hdc shell "mount -o remount,rw /"
    hdc file send libnweb_render.so /data/app/el1/bundle/public/com.ohos.nweb/libs/arm
    hdc file send libweb_engine.so /data/app/el1/bundle/public/com.ohos.nweb/libs/arm
    pause
    hdc shell reboot
    pause
    ```

    方法二：替换hap包
    
    编译完成后，在out目录下找到NWeb-rk3568.hap或者NWeb-rk3568_64.hap, 将它推送到设备中。

    ```
    hdc shell "mount -o remount,rw /"
    hdc file send NWeb-rk3568.hap /system/app/com.ohos.nweb/NWeb.hap
    hdc shell "rm /data/* -rf"
    hdc shell reboot
    ```
5. 所有Chromium仓对应目录映射关系

    https://gitcode.com/openharmony-tpc/manifest/blob/chromium/chromium.xml

6. 上库指导

    6.1 将chromium_src 仓 fork到自己的私仓

    6.2 下载全量代码

    6.3 修改调试代码

    6.4 将文件添加到暂存区

    使用git add将修改后的文件添加到暂存区

    6.5 显示工作区和暂存区的状态

    使用git status查看自己的修改是否放到暂存区，查看项目历史信息使用git log。

    6.6 将工作区内容或暂存区内容提交到版本库

    使用git commit -sm”提交信息描述” 将修改后的文件进行提交，***注意-s一定不能漏，这个是签名，否则提的PR会报DCO错误***。

    DCO签署链接：***https://dco.openharmony.cn/sign-dco***

    6.7 将代码提交到对应fork出来的私仓地址上

    如：git push ***https://gitcode.com/[gitcodeUserName]/chromium_src***

    6.8 新建PR

    6.9 如果涉及联合构建，建立ISSUE，并在需要联合构建的PR中都绑定该ISSUE

    6.10 在PR下面评论start build开始构建

    6.11 联系committer加分

7. chromium各版manifest分支名

    99分支：chromium

    114分支：114_trunk
    
    132分支：132_trunk

    配套OpenHarmony 3.2Release分支：3.2_Release

    配套OpenHarmony 4.0Release分支：4.0_Release

    配套OpenHarmony 4.1 Beta1 分支：master114_20231218

## 其他相关代码仓地址：

[架构图中的Webview ArkTS仓
](https://gitcode.com/openharmony/interface_sdk-js/tree/master/api)

[架构图中的Webview NDK仓
](https://gitcode.com/openharmony/interface_sdk_c/tree/master/web)

[架构图中的Web Component仓
](https://gitcode.com/openharmony/arkui_ace_engine/tree/master/frameworks/core/components/web)

[架构图中的web_webview仓
](https://gitcode.com/openharmony/web_webview)

[架构图中的Chromium仓](https://gitcode.com/openharmony-tpc/chromium_src)

[架构图中的CEF仓](https://gitcode.com/openharmony-tpc/chromium_cef)

