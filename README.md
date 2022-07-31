# IoT_3DPrinter
基于腾讯云Iot explorer物联网平台、腾讯连连小程序的3D打印控制系统开发

#### 1、介绍

这是一个基于沁恒CH32V_EVB开发套件的TencentOS Tiny 3D打印机云控制系统方案，该方案作为本年度腾讯AIoT开发者成长激励计划的参赛项目。

#### 2、项目目录

##### 2.1、Firmware(开发板固件源代码)

以下是整个固件源代码的框架结构：

![在这里插入图片描述](https://img-blog.csdnimg.cn/89c9ed6d8e354aa584c4d19c29693af0.jpeg)

该项目分为TencentCloud IoT Explorer、APP、Common、TencentOS tiny、Hardware、Bsp、McuPlatform这几个部分，每个部分的功能如下：

###### 2.1.1、TencentCloud IoT Explorer

腾讯IoT Explorer物联网设备管理平台、集成腾讯连连小程序、微信公众号推送等物联网业务。

###### 2.1.2、APP

主要为本项目的业务逻辑部分，主要分为串口数据解析、GCode命令转发、Mqtt订阅和发布业务处理等。

###### 2.1.3、Common 

主要集成了提供给项目使用的软件组件，其中包括ringbuffer、cJSON、Mqtt、Log系统等其它组件。

###### 2.1.4、TencentOS tiny

腾讯物联网操作系统，是一个内存占用极小、组件丰富且效率极高的实时操作系统。

###### 2.1.5、Hardware

主要实现了一些完成项目必备的硬件驱动程序，包括按键驱动、LCD驱动、LED驱动、WIFI驱动等。

###### 2.1.6、Bsp

主要是由Mcu平台提供的板级支持包，目前该部分仅支持CH32V_EVB平台。

###### 2.1.7、McuPlatform

具体的Mcu平台，目前该部分仅支持CH32_EVB平台。

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