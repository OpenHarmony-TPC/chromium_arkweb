# ArkWeb 项目

## 1. 概述

ArkWeb 项目是一个全面的解决方案，旨在将 Chromium Web 引擎集成到 OpenHarmony (OHOS) 操作系统中。它作为系统 `Web` 组件的基础，为 OHOS 应用程序提供强大的 Web 渲染能力。

本项目是对 Chromium 源代码的扩展和增强，以使其适应 OHOS 架构和 API，并在原有功能的基础上，基于Openharmoy平台扩展了很多新性，如广告拦截，任务下载，输入框填充等。它包括一个API接口实现层、对核心 Chromium 模块的扩展，以及OS适配层。

## 2. 架构

项目遵循分层架构，图中Arkweb模块即本仓内容：

![image.png](https://raw.gitcode.com/user-images/assets/8261933/514ef0fc-bd3e-464b-b7a1-4e2149c1df34/image.png 'image.png')

架构图中CEF, Chromium和当前仓ArkWeb仓联合编译出Web内核，编译产物为NWeb.hap，通过二进制集成在openharmony系统中。

1.  **NWeb接口实现层 (`ohos_nweb`)**：Web API接口在webview层被转换为NWeb接口，并在本模块的进行了实现。ohos_nweb向上直接对接系统侧的webview和web组件，向下依赖cef和chromium的接口。NWeb接口隔离了系统侧的Web API和内核侧的CEF/Chromium接口， 支持同一系统运行不同版本的内核，实现了web内核hap包的独立升级。NWeb接口实现层通过调用cef和chromium中content层提供的接口，实现了web的核心功能。
       - WebEngineImpl: 管理整Web 引擎实例，负责创建新的 Web 实例，或根据 ID 获取已存在的 Web 实例。负责初始化所有核心组件。
      - WebStorageImpl： 管理 Web 应用的本地存储，包括 localStorage、sessionStorage 和密码管理。
      - CookieManager：管理 HTTP Cookie 的存储、访问和策略控制。
      - AdBlock：实现广告拦截功能，提供规则管理和域名白名单/黑名单功能。
      - AdvancedSecurity提供高级安全功能控制，管理各种Web安全特性的开关状态，如WebAssembly支持，JIT编译支持，WebGL支持，WebRTC支持。
      - NotificationManager管理 Web 通知功能，处理通知的显示、关闭和交互事件。
      - WebDataBaseImpl管理 Web 应用的数据库数据，包括 HTTP 认证信息和权限数据。
      - InputHandler处理用户输入事件，包括触摸、键盘、鼠标等输入设备的交互。


2.  **CEF扩展层 (`ohos_cef_ext`)**：对cef的接口进行扩展，通过继承和多重继承实现功能扩展，保持与CEF框架的兼容性，提供了远超标准CEF的丰富API，满足移动Web应用的各种需求，其中包括：URL信任列表管理，恶意软件白名单、儿童模式策略，第三方Cookie访问策略、智能跟踪防护，广告拦截系统，高级内容过滤。权限管理，自动填充功能扩展、网络和存储模块扩展、预取网络请求优化提升页面加载性能、集成安全浏览错误页面处理、帧内图像检测和提取、支持添加额外的HTTP头部、带持续时间的动画滚动效果、用户界面增强、密码和表单管理等。


3.  **Chromium扩展层 (`chromium_ext`)，扩展了chromium原生的如下功能**：
      - base基础库：调试功能扩展、文件系统操作扩展、国际化支持、内存管理扩展、消息循环扩展、性能指标收集。
      - components组件：自动填充功能、门户网站检测、内容解密模块、内容设置、崩溃处理、下载管理、JavaScript 注入、内存压力监控、密码管理器、PDF 处理、性能管理、权限管理、打印功能。
      - media媒体：音频处理、基础媒体功能、内容捕获、GPU 媒体加速、媒体渲染器。
      - net网络：证书管理、DNS 解析、HTTP 协议处理、代理解析、套接字处理、SSL/TLS 支持、URL 请求处理。


4.  **OS适配层 (`ohos_adapter`)**：对 OpenHarmony 原生 NDK 和系统服务的调用的封装层。
      - graphic_adapter：为Web引擎提供图形渲染和显示相关的底层系统适配，实现与OHOS图形系统的无缝集成。包括垂直同步，帧率同步管理，图形缓冲区buffer管理，色域像素的格式转换，图像数据的创建、处理和显示等。
      -  net_config_adapter：为 Web 引擎提供网络安全配置和策略管理，明文传输控制管理，确保网络请求符合系统安全策略。
      - sensor_adapter：为 Web 应用提供设备传感器访问能力，包括运动传感器、方向传感。支持网页与设备硬件的交互。
      - media_adapter: 为 Web 引擎提供完整的媒体编解码的底层系统适配。

## 3. 目录结构

```
├── arkweb
│   ├── build                      # 编译arkweb相关目录
│   ├── chromium_ext               # 对chromium解耦出的文件放到此目录，内部子目录与chromium仓目录一一对应
│   │  ├── base                    # 基础库扩展，包括调试功能扩展、文件系统操作扩展、国际化支持等   
│   │  ├── components              # components组件扩展，包括自动填充功能、门户网站检测、内容解密模块、内容设置、崩溃处理、下载管理等。
│   │  ├── content                                 
│   │  ├── media                   # 媒体扩展，包括音频处理、基础媒体功能、内容捕获、GPU 媒体加速等
│   │  └── net                     # 网络扩展，包括证书管理、DNS 解析、HTTP 协议处理、代理解析、套接字处理、SSL/TLS 支持、URL 请求处理等
│   ├── ohos_adapter               # 对 OpenHarmony 原生 NDK 和系统服务的调用的封装层
│   ├── ohos_cef_ext               # 对cef解耦出的文件放到此目录，内部子目录与cef仓目录一一对应
│   ├── ohos_nweb                  # 向 OHOS 开发者的公共 API的实现，用于在他们的应用程序中嵌入 Webview
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

