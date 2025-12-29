# ArkWeb 项目

## 概述

ArkWeb 项目旨在将 Chromium Web 引擎集成到 OpenHarmony操作系统中，它对 Chromium 源代码进行了扩展和增强，以使其适应OpenHarmony架构和 API。ArkWeb在Chromium原有功能的基础上，基于OpenHarmony平台扩展了很多新特性，如广告拦截，网络加速，输入框填充等。它作为系统 Web 组件的基础，为OpenHarmony应用程序提供强大的 Web 渲染能力。

ArkWeb 项目主要包含一个NWeb接口实现层，对CEF/Chromium 模块的扩展层，以及OS适配层。

## 架构

项目遵循分层架构，图中Arkweb模块即本仓内容：

![image.png](https://raw.gitcode.com/user-images/assets/4769982/15cf1d22-9a68-47a9-88e0-6e7ef83ad479/image.png 'image.png')

架构图中CEF，Chromium和当前ArkWeb仓联合编译出Web内核，编译产物为NWeb.hap，通过二进制集成在OpenHarmony系统中。ArkWeb仓主要包含以下几个部分：

#### NWeb接口实现
该模块向上直接对接系统侧的Webview，向下依赖CEF和Chromium的接口。NWeb接口隔离了系统侧的Web API和内核侧的Chromium接口， 支持同一系统运行不同版本的内核，支持Web内核Hap包的独立升级。

#### CEF扩展
基于原生CEF在安全与隐私保护、用户交互体验、渲染显示等方面进行了扩展。在安全与隐私保护方面，新增了动态规则管理广告拦截，站点级别广告拦截，跟踪器检测等特性。在用户交互体验方面，支持智能填充，支持H5页面表单中的护照，发票抬头，车牌号，所在地区，航班号等类型的自动填充。在渲染显示方面，支持GPU 进行离屏渲染，支持智能帧率控制。

#### Chromium扩展
基于原生Chromium在基础库，基础组件，多媒体，网络和渲染等方面进行了扩展。新增性能监控特性，提供精确到 6 帧/12 帧/24 帧的微卡顿检测。重构了 Chromium 进程创建机制。支持HEIF/HEIC 硬件解码。支持IPv4/IPv6 并发连接和最优路径选择，提升网络的连接成功率，支持智能连接预加载机制，降低网络连接延迟。新增同层渲染技术，支持ArkUI组件与Web DOM元素混合在一起进行排版渲染，保证ArkUI组件和DOM元素交互一致。

#### OS适配层

该模块提供对OpenHarmony系统库进行了封装适配，使Chromium能够便利的对接到OpenHarmony系统库。包括图形系统适配，网络系统适配，多媒体适配，设备和服务适配，系统工具适配等。


## 3. 目录结构

```
├── arkweb
│   ├── build                      # 编译arkweb相关目录
│   ├── chromium_ext               # 对chromium解耦出的文件放到此目录，内部子目录与chromium仓目录一一对应
│   │  ├── base                    # 基础库扩展，包括调试功能扩展、文件系统操作扩展、国际化支持等   
│   │  ├── components              # components组件扩展，包括自动填充功能、门户网站检测、内容解密模块、     
                                     内容设置、崩溃处理、下载管理等。                           
│   │  ├── media                   # 媒体扩展，包括音频处理、基础媒体功能、内容捕获、GPU 媒体加速等
│   │  └── net                     # 网络扩展，包括证书管理、DNS 解析、HTTP 协议处理、代理解析、
                                     套接字处理、SSL/TLS 支持、URL 请求处理等
│   ├── ci_tools                   # 门禁工具
│   ├── ohos_adapter               # 对 OpenHarmony  NDK 和系统服务的调用的封装层
│   ├── ohos_cef_ext               # 对CEF解耦出的文件放到此目录，内部子目录与CEF仓目录一一对应
│   ├── ohos_nweb                  # Web API接口在webview层被转换为NWeb接口，并在本模块的进行了实现
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
    
    编译完成后，在out目录下找到NWeb-rk3568.hap或者NWeb-rk3568_64.hap， 将它推送到设备中。

    ```
    hdc shell "mount -o remount,rw /"
    hdc file send NWeb-rk3568.hap /system/app/com.ohos.nweb/NWeb.hap
    hdc shell "rm /data/* -rf"
    hdc shell reboot
    ```
5. 所有Chromium仓对应目录映射关系

    https://gitcode.com/openharmony-tpc/manifest/blob/chromium/chromium.xml


## 其他相关代码仓地址：

[架构图中的Webview ArkTS仓
](https://gitcode.com/openharmony/interface_sdk-js/tree/master/api)

[架构图中的Webview NDK仓
](https://gitcode.com/openharmony/interface_sdk_c/tree/master/web)

[架构图中的Web Component仓
](https://gitcode.com/openharmony/arkui_ace_engine/tree/master/frameworks/core/components/web)

[架构图中的Web Webview仓
](https://gitcode.com/openharmony/web_webview)

[架构图中的Chromium仓](https://gitcode.com/openharmony-tpc/chromium_src)

[架构图中的CEF仓](https://gitcode.com/openharmony-tpc/chromium_cef)

