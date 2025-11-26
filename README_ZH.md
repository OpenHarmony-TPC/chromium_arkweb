# ArkWeb 项目

## 1. 概述

ArkWeb 项目旨在将 Chromium Web 引擎集成到 OpenHarmony操作系统中，它对 Chromium 源代码进行了扩展和增强，以使其适应OpenHarmony架构和 API。Arkweb在Chromium原有功能的基础上，基于OpenHarmony平台扩展了很多新特性，如广告拦截，网络加速，输入框填充等。它作为系统 Web 组件的基础，为OpenHarmony应用程序提供强大的 Web 渲染能力。

ArkWeb 项目主要包含一个NWeb接口实现层，对CEF/Chromium 模块的扩展层，以及OS适配层。

## 2. 架构

项目遵循分层架构，图中Arkweb模块即本仓内容：

![image.png](https://raw.gitcode.com/user-images/assets/4769982/eef5ad27-5812-42ff-ad37-3bf7279eb243/image.png 'image.png')

架构图中CEF，Chromium和当前ArkWeb仓联合编译出Web内核，编译产物为NWeb.hap，通过二进制集成在OpenHarmony系统中。ArkWeb仓主要包含以下几个部分：

### 2.1   NWeb接口实现层 (`ohos_nweb`)
ohos_nweb向上直接对接系统侧的Webview，向下依赖CEF和Chromium的接口。Webview仓主要内容为对应用开放的Web API的实现，主要是通过调用NWeb提供的C++接口来实现，Webview仓只是定义了NWeb接口，NWeb的具体实现在本仓的ohos_nweb层。NWeb接口隔离了系统侧的Web API和内核侧的CEF/Chromium接口， 支持同一系统运行不同版本的内核，支持Web内核Hap包的独立升级。NWeb接口实现层通过调用CEF和Chromium的接口，实现了Web的核心功能。NWeb的主要实现包括：
 - WebEngineImpl：管理整Web 引擎实例，负责创建新的 Web 实例，或根据 ID 获取已存在的 Web 实例。负责初始化所有其他接口实现。
  - WebStorageImpl：管理 Web 应用的本地存储，包括 localStorage、sessionStorage 和密码管理。
  - CookieManager：管理 HTTP Cookie 的存储、访问和策略控制。
   - AdBlock：实现广告拦截功能，提供规则管理和域名白名单/黑名单功能。
   - AdvancedSecurity：提供高级安全功能控制，管理各种Web安全特性的开关状态，如WebAssembly支持，JIT编译支持，WebGL支持，WebRTC支持。


### 2.2 CEF扩展层 (`ohos_cef_ext`)
基于原生CEF扩展了如下功能：
   - **安全与隐私保护扩展：**
     - 动态规则管理广告拦截：支持实时更新拦截规则，无需重启浏览器
     - 广告拦截支持域名白名单/黑名单：支持用户自定义域名级别的拦截策略
     - 站点级别控制广告拦截：SetAdBlockEnabledForSite() 方法可为特定网站启用/禁用广告拦截
     - URL信任列表: 企业可配置允许访问的 URL 白名单
     - 恶意软件检测: 实时检测恶意网站和钓鱼攻击
     - 分级防护：支持严格模式和普通模式的安全防护
     - 第三方Cookie策略: 智能阻止第三方 Cookie
     - 跟踪器检测: 识别并阻止常见跟踪脚本
     -  隐私报告: 提供被阻止的跟踪器统计
   - **网络与存储增强：**
     - 动态代理配置: arkweb_proxy_config_monitor 支持运行时代理配置更新
     - Cookie 策略增强: cookie_manager_impl_ext 提供更细粒度的 Cookie 控制
     - DNS 预取: 智能域名预解析，提升页面加载速度
     - 隐私数据库: 隐私模式下的独立数据存储
     - 离线缓存: 增强的离线页面缓存机制
   - **用户交互体验增强：**
     - 智能表单识别: AI 驱动的表单字段类型识别
     - 跨设备同步: 支持多设备间的填充数据同步
     - 触摸优化: 多点触控、手势识别、触摸反馈
     - 传感器集成: 加速计、陀螺仪等传感器支持
   - **高级渲染与显示：**
     - 硬件加速: 利用 GPU 进行离屏渲染优化
     - 帧率控制: 智能帧率调节，平衡性能和功耗
### 2.3 Chromium扩展层 (`chromium_ext`)
基于原生Chromium扩展了如下功能：
   - **base基础库扩展：**
     - 路径系统集成：替换 Chromium 路径系统，完全遵循 OHOS 应用存储规范
     - 专业性能监控：相比 Chromium 基础监控，提供精确到 6 帧/12 帧/24 帧的微卡顿检测
     - LTPO 显示技术：支持 LTPO 动态帧率调整和分布式 VSync
     - 消息循环重构：重写事件循环，与 OHOS 原生事件处理机制深度集成
   - **render图形渲染扩展：**
     - 更多图像格式：原生 Chromium 仅支持基础图像格式，ArkWeb增加了HEIF/HEIC 硬件解码支持，支持 4K 实时解码
     - 智能渲染控制：新增 VideoFrameSubmitter 精确控制，相比原生Chromium的粗粒度控制，可实现帧级别的功耗优化
     - 原生解码集成：直接调用 OHOS 系统解码器， bypass Chromium软件解码路径
     - 智能滚动条：动画性能优化，快速滚动时自动跳过绘制，相比原生 Chromium 固定动画逻辑更加智能
     - 同层渲染技术：原生 Chromium 的视频播放需要多层合成，ArkWeb 实现与原生视频组件同层渲染
     - 原生缓冲区：直接使用 OHOS 原生图形缓冲区，OHOSNativeBufferImageBacking 实现零拷贝渲染
   - **content核心扩展：**
      - 进程启动重构：使用 OHOS 原生 ChildProcessStarter，相比原生 Chromium 的通用进程创建机制提供更好的性能和安全性
      - 无障碍深度集成：完整集成OHOS无障碍服务，相比原生Chromium的基础屏幕阅读器支持更加完善
   - **components组件扩展：**
       - 企业级 DRM：集成华为WisePlay DRM，支持硬件级内容保护，相比于原生的Widevine，ArkWeb提供更符合国内生态的DRM方案
      - 硬件加密： 集成HUKS（硬件通用密钥服务），相比原生Chromium的软件加密提供硬件级安全保障
       - JS 桥接增强：提供类似 Android WebView 的 JavaScript 桥接能力，相比原生 Chromium 的受限接口更加灵活
       -  广告拦截：基于 Trie 结构的域名过滤系统，相比原生 Chromium 的基本拦截规则，效率和准确度都大幅提升
   - **media媒体扩展：**
      - 硬件编解码：支持 4K@60fps 硬件编码，，相比原生 Chromium 的软件编解码性能提升显著
      - 现代格式支持：完整的 HEIF/HEIC 硬件解码支持，原生 Chromium 需要第三方插件
      - 智能桥接：OhosMediaCodecBridge 提供统一的软/硬件编解码器接口，相比原生 Chromium 的复杂选择逻辑更加智能
      - 帧工厂优化：多种视频帧提供策略，相比原生 Chromium 的单一模式提供更好的性能和兼容性
   - **net网络扩展：**
      - 智能连接：IPv4/IPv6 并发连接和最优路径选择，提升网络的连接成功率
      - 预加载优化：智能连接预加载机制，连接网络连接延迟
      - 移动网络优化：针对移动网络环境的特殊优化，相比原生 Chromium 的通用网络处理提供更好的弱网体验
      - 安全增强：集成 OHOS 证书系统和安全策略，相比原生 Chromium 的跨平台方案提供更强的安全保障

### 2.4 OS适配层 (`ohos_adapter`)
   - **图形系统适配:**
       - Native Window适配器，支持OpenHarmony的原生窗口系统，提供窗口创建、管理和操作功能
       - VSync适配器，支持垂直同步信号管理，确保图形渲染与显示器刷新率同步
       - Native Image适配器，支持图像数据创建、处理和显示，支持 GPU 纹理集成
       - Ashmem适配器，支持跨进程共享内存管理，为图形缓冲区提供高效的数据共享机制
   - **网络系统适配:**
       - 网连连接适配器，支持网络连接状态监控和管理，提供实时的网络连接信息
       - 网络配置适配器，支持网络安全配置和策略管理，确保网络请求符合系统安全策略
       - 网络事件适配器，支持网络事件处理和分发，为 Web 引擎提供网络层事件通知
       - 网络代理适配器，支持网络代理配置和管理，支持各种代理模式
   - **多媒体适配:**
       - 媒体解码器适配，支持媒体解码创建，配置、控制，缓冲区管理，异步回调
       - 音频解码器适配器，支持多种音频格式支持 (AAC, MP3, FLAC, Opus 等)，音频采样率和声道配置，音频质量优化，低延迟音频处理
       - DRM适配器，支持内容解密和管理，密钥获取和验证，安全会话建立，权限控制和许可证管理
       - 音频采集适配器，支持音频录制功能，音频流处理，录音质量控制
   - **设备和服务适配:**
       - 传感器适配器，为Web应用提供设备传感器访问能力，支持加速度计、陀螺仪、磁力计、光传感器、距离传感器、方向传感器等
       - 电池管理适配器，支持电池状态监控和电池信息获取，电池事件监听
       - 位置服务适配器，支持GPS 定位和位置信息获。支持不同场景、精度、优先级的定位配置，支持定位会话管理，能处理和转换位置数据格式
       - 认证令牌适配器，应用权限管理和访问令牌验证，确保 Web 应用的安全访问控制
   - **系统工具适配:**
       - 系统属性适配器，支持系统配置读取，属性键值对管理，系统信息获取
       - 事件处理适配器，支持异步事件处理，任务调度管理，线程池管理
       - 日期时间格式适配器，支持本地化日期时间格式，时区处理，日期时间解析和格式化
       - 数据共享适配器，支持跨应用数据共享，数据库访问封装，数据同步管理
       - 剪贴板适配器，支持系统剪贴板操作，数据格式转换，粘贴板内容管理

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
│   ├── ohos_adapter               # 对 OpenHarmony 原生 NDK 和系统服务的调用的封装层
│   ├── ohos_cef_ext               # 对cef解耦出的文件放到此目录，内部子目录与cef仓目录一一对应
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

