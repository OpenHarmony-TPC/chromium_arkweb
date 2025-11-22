# ArkWeb Project

## 1. Overview

The ArkWeb project is a comprehensive solution designed to integrate the Chromium Web engine into the OpenHarmony (OHOS) operating system. It serves as the foundation for the system's `Web` component, providing powerful Web rendering capabilities for OHOS applications.

This project extends and enhances the Chromium source code to adapt it to the OHOS architecture and APIs. Based on the OpenHarmony platform, many new features have been added, such as ad blocking, task downloading, input box filling, and more. It includes an API interface implementation layer, extensions to core Chromium modules, and an OS adaptation layer.

## 2. Architecture

The project follows a layered architecture, where the ArkWeb module in the diagram represents the contents of this repository:

![image.png](https://raw.gitcode.com/user-images/assets/8261933/514ef0fc-bd3e-464b-b7a1-4e2149c1df34/image.png 'image.png')

In the architecture diagram, CEF, Chromium, and the current ArkWeb repository are compiled together to produce the Web kernel, with the compilation output being NWeb.hap, which is integrated into the OpenHarmony system through binary integration.

1. **NWeb Interface Implementation Layer (`ohos_nweb`)**: Web API interfaces are converted to NWeb interfaces at the webview layer and implemented in this module. ohos_nweb directly interfaces with the system-side webview and web components on the upper layer, and depends on CEF and Chromium interfaces on the lower layer. NWeb interfaces isolate the system-side Web API from the kernel-side CEF/Chromium interfaces, supporting the operation of different kernel versions on the same system and enabling independent upgrade of the Web kernel HAP package. The NWeb interface implementation layer implements core Web functionality by calling interfaces provided by the content layer of CEF and Chromium.
   - **WebEngineImpl**: Manages the entire Web engine instance, responsible for creating new Web instances or retrieving existing Web instances by ID. Responsible for initializing all core components.
   - **WebStorageImpl**: Manages local storage for Web applications, including localStorage, sessionStorage, and password management.
   - **CookieManager**: Manages HTTP Cookie storage, access, and policy control.
   - **AdBlock**: Implements ad blocking functionality, providing rule management and domain whitelist/blacklist functionality.
   - **AdvancedSecurity**: Provides advanced security feature control, managing the on/off status of various Web security features such as WebAssembly support, JIT compilation support, WebGL support, and WebRTC support.
   - **NotificationManager**: Manages Web notification functionality, handling notification display, closing, and interaction events.
   - **WebDataBaseImpl**: Manages database data for Web applications, including HTTP authentication information and permission data.
   - **InputHandler**: Handles user input events, including interactions with input devices such as touch, keyboard, and mouse.

2. **CEF Extension Layer (`ohos_cef_ext`)**: Extends CEF interfaces through inheritance and multiple inheritance to implement feature extensions while maintaining compatibility with the CEF framework. It provides a rich API that far exceeds standard CEF to meet various needs of mobile Web applications, including: URL trust list management, malware whitelist, child mode policies, third-party cookie access policies, intelligent tracking protection, ad blocking systems, advanced content filtering, permission management, autofill function extensions, network and storage module extensions, prefetch network request optimization to improve page loading performance, integrated safe browsing error page handling, in-frame image detection and extraction, support for adding additional HTTP headers, animated scrolling effects with duration, user interface enhancements, password and form management, and more.

3. **Chromium Extension Layer (`chromium_ext`)**: Extends the following native Chromium functionality:
   - **base library**: Debug functionality extensions, file system operation extensions, internationalization support, memory management extensions, message loop extensions, performance metrics collection.
   - **components**: Autofill functionality, portal detection, content decryption module, content settings, crash handling, download management, JavaScript injection, memory pressure monitoring, password manager, PDF processing, performance management, permission management, printing functionality.
   - **media**: Audio processing, basic media functionality, content capture, GPU media acceleration, media renderer.
   - **net**: Certificate management, DNS resolution, HTTP protocol handling, proxy resolution, socket handling, SSL/TLS support, URL request handling.

4. **OS Adaptation Layer (`ohos_adapter`)**: A wrapper layer for calls to OpenHarmony native NDK and system services.
   - **graphic_adapter**: Provides underlying system adaptation for graphics rendering and display-related functions for the Web engine, achieving seamless integration with the OHOS graphics system. Includes vertical synchronization, frame rate synchronization management, graphics buffer management, color gamut pixel format conversion, image data creation, processing, and display.
   - **net_config_adapter**: Provides network security configuration and policy management for the Web engine, managing plaintext transmission control to ensure network requests comply with system security policies.
   - **sensor_adapter**: Provides device sensor access capabilities for Web applications, including motion sensors and orientation sensors, supporting interaction between web pages and device hardware.
   - **media_adapter**: Provides complete underlying system adaptation for media encoding and decoding for the Web engine.

## 3. Directory Structure

```
├── arkweb
│   ├── chromium_ext               # Decoupled chromium files placed in this directory, with internal subdirectories corresponding one-to-one to the chromium repository directories
│   │  ├── base
│   │  ├── components
│   │  ├── content
│   │  ├── media
│   │  └── net
│   ├── ohos_cef_ext               # Decoupled CEF files placed in this directory, with internal subdirectories corresponding one-to-one to the CEF repository directories
│   ├── build                      # Arkweb compilation-related directories
│   ├── glue                       # Glue layer code, adapting system components
│   ├── ohos_nweb                  # Public API implementation for OHOS developers, used for embedding Webview in their applications
│   ├── ohos_autolayout            # Resources and logic for automatic layout functionality
│   ├── ohos_adapter_ndk           # Wrapper layer for calls to OpenHarmony native NDK and system services (e.g., network, graphics, input, and window management)
│   ├── code_version_update_tools  # Kernel upgrade tool-related code
│   ├── patch                      # Related code
│   ├── test                       # Test-related code

```

## 4. Usage Instructions

1. **Download Code**: Using the 132_trunk branch as an example, to download code from other branches, replace the manifest branch parameter after -b. For the parameter list, see section 7.
    ```
    repo init -u https://gitcode.com/openharmony-tpc/manifest -b 132_trunk -m developer.xml --no-repo-verify
    repo sync -c
    repo forall -c 'git lfs pull'
    ```

2. **Compilation**

    Build unsigned HAP package simultaneously:

    **Platform**: rk3568
    ```
    ./build.sh  -t w -A rk3568
    ```
    Only compile SO library:
    ```
    ./build.sh -A rk3568
    ```

    **Platform**: rk3568_64
    ```
    ./build.sh  -t w -A rk3568_64
    ```
    Only compile SO library:
    ```
    ./build.sh -A rk3568_64
    ```

3. **Signing**

    **Platform**: rk3568
    ```
    ./sign.sh rk3568
    ```
    **Platform**: rk3568_64
    ```
    ./sign.sh rk3568_64
    ```

4. **Debugging Methods**

    **Method 1**: Replace SO libraries

    After compilation, find the corresponding SO library files in the out directory and push them to the device:
    ```
    hdc shell "mount -o remount,rw /"
    hdc file send libnweb_render.so /data/app/el1/bundle/public/com.ohos.nweb/libs/arm
    hdc file send libweb_engine.so /data/app/el1/bundle/public/com.ohos.nweb/libs/arm
    pause
    hdc shell reboot
    pause
    ```

    **Method 2**: Replace HAP package

    After compilation, find NWeb-rk3568.hap or NWeb-rk3568_64.hap in the out directory and push it to the device:
    ```
    hdc shell "mount -o remount,rw /"
    hdc file send NWeb-rk3568.hap /system/app/com.ohos.nweb/NWeb.hap
    hdc shell "rm /data/* -rf"
    hdc shell reboot
    ```

5. **All Chromium Repository Directory Mapping**

    https://gitcode.com/openharmony-tpc/manifest/blob/chromium/chromium.xml

6. **Submission Guidelines**

    6.1 Fork the chromium_src repository to your private repository

    6.2 Download the full codebase

    6.3 Modify and debug the code

    6.4 Add files to the staging area

    Use `git add` to add modified files to the staging area

    6.5 Show working directory and staging area status

    Use `git status` to check if your modifications are in the staging area, and use `git log` to view project history information.

    6.6 Commit working directory or staging area content to the version repository

    Use `git commit -sm "commit message description"` to commit modified files. **Note: -s must not be omitted as it is a signature, otherwise the PR will report a DCO error**.

    DCO signing link: ***https://dco.openharmony.cn/sign-dco***

    6.7 Push code to the corresponding forked private repository address

    For example: `git push ***https://gitcode.com/[gitcodeUserName]/chromium_src***`

    6.8 Create a new PR

    6.9 If joint construction is involved, create an ISSUE and bind it to all PRs that require joint construction

    6.10 Comment "start build" under the PR to begin construction

    6.11 Contact a committer for scoring

7. **Chromium Version Manifest Branch Names**

    99 branch: chromium

    114 branch: 114_trunk

    132 branch: 132_trunk

    Compatible with OpenHarmony 3.2 Release branch: 3.2_Release

    Compatible with OpenHarmony 4.0 Release branch: 4.0_Release

    Compatible with OpenHarmony 4.1 Beta1 branch: master114_20231218

## Other Related Repository Addresses:

[Webview ArkTS Repository in Architecture Diagram
](https://gitcode.com/openharmony/interface_sdk-js/tree/master/api)

[Webview NDK Repository in Architecture Diagram
](https://gitcode.com/openharmony/interface_sdk_c/tree/master/web)

[Web Component Repository in Architecture Diagram
](https://gitcode.com/openharmony/arkui_ace_engine/tree/master/frameworks/core/components/web)

[web_webview Repository in Architecture Diagram
](https://gitcode.com/openharmony/web_webview)

[Chromium Repository in Architecture Diagram](https://gitcode.com/openharmony-tpc/chromium_src)

[CEF Repository in Architecture Diagram](https://gitcode.com/openharmony-tpc/chromium_cef)