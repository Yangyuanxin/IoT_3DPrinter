# IoT_3DPrinter
#### 1、介绍

这是一个基于沁恒CH32V_EVB开发套件的TencentOS Tiny 3D打印机云控制系统方案，包括基于腾讯云IoT Explorer物联网平台、腾讯连连小程序以及3D打印控制系统固件的开发，该方案作为本年度腾讯AIoT开发者成长激励计划的参赛项目，其整体架构设计如下图所示：![img](https://ask.qcloudimg.com/http-save/yehe-5745070/07b3629159899c9d046f7a9e1890f503.jpeg?imageView2/2/w/1620)

该项目分为TencentCloud IoT Explorer、APP、Common、Operating System、Hardware、Bsp、McuPlatform这几个部分，每个部分的功能如下：

###### 1.1、TencentCloud IoT Explorer

腾讯IoT Explorer物联网设备管理平台、集成腾讯连连小程序、微信公众号推送等物联网业务。

###### 1.2、APP

主要为本项目的业务逻辑部分，主要分为串口数据解析、GCode命令转发、Mqtt订阅和发布业务处理等。

###### 1.3、Common 

主要集成了提供给项目使用的软件组件，其中包括ringbuffer、cJSON、Mqtt、Log系统等其它组件。

###### 1.4、Operating System

目前仅支持TencentOS-tiny，TencentOS-tiny，是一个内存占用极小、组件丰富且效率极高的实时操作系统。

###### 1.5、Hardware

主要实现了一些完成项目必备的硬件驱动程序，包括按键驱动、LCD驱动、LED驱动、WIFI驱动等。

###### 1.6、Bsp

主要是由Mcu平台提供的板级支持包，目前该部分仅支持CH32V_EVB平台。

###### 1.7、McuPlatform

具体的Mcu平台，目前该部分仅支持CH32_EVB平台。

#### 2、项目目录

##### 2.1、Firmware

与腾讯云IoT Explorer、腾讯连连、3D打印机的固件源代码。

##### 2.2、Hardware

开发板硬件原理图及芯片数据手册。

##### 2.3、3Dprinter_firmware

Anycubic 3D打印机Vyper固件。

##### 2.4、Resource

存放TencentOS-tiny图标、腾讯云平台Json模板、测试3D模型、WIFI固件及烧录方法、视频和PPT。

#### 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request