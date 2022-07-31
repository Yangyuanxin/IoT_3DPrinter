# Firmware
#### 1、介绍

这是一个基于沁恒CH32V_EVB开发套件的TencentOS Tiny 3D打印机云控制系统方案的固件部分。

#### 2、固件源代码架构

除去TencentCloud IoT Explorer层，其它都是固件层需要开发的：![img](https://ask.qcloudimg.com/http-save/yehe-5745070/07b3629159899c9d046f7a9e1890f503.jpeg?imageView2/2/w/1620)

该项目的固件层分为APP、Bsp、Common、Hardware、McuPlatform、OperatingSystem这几个部分，每个部分的功能如下：

##### 2.1、APP

主要为本项目的业务逻辑部分，主要分为串口数据解析、GCode命令转发、Mqtt订阅和发布业务处理等。

##### 2.2、Bsp

主要是由Mcu平台提供的板级支持包，目前该部分仅支持CH32V_EVB平台。

##### 2.3、Common

主要集成了提供给项目使用的软件组件，其中包括ringbuffer、cJSON、Mqtt、Log系统等其它组件。

##### 2.4、Hardware

主要实现了一些完成项目必备的硬件驱动程序，包括按键驱动、LCD驱动、LED驱动、WIFI驱动等。

##### 2.6、McuPlatform

具体的Mcu平台，目前该部分仅支持CH32_EVB平台。

##### 2.7、OperatingSystem

操作系统层，目前仅包含TencentOS-tiny，它是一个内存占用极小、组件丰富且效率极高的实时操作系统。

#### 3、业务设计流程

APP主业务流程分别创建三个线程来进行不同业务的处理，而线程间通信机制采用TencentOS-tiny提供的消息队列进行交互通讯，当线程没有接收到消息时，该线程为阻塞等待状态而不消耗CPU时间，直到接收到消息时，线程才恢复就绪态，对接收的数据进行处理。这样做的好处是能够高效的管理CPU资源，避免CPU资源浪费。![img](https://ask.qcloudimg.com/http-save/yehe-5745070/a465aa59afcda9887760ff5390f036e5.jpeg?imageView2/2/w/1620)

其中，消息队列之间的数据传输设计是基于一个消息结构体来进行的，如下所示：

```c
/*消息结构体封装*/
#define MSG_LEN 50
struct Msg_t
{
    //消息类型
	uint8_t Type;
	//消息负载
	char Data[MSG_LEN];
};
```

而消息类型则是由各种命令构成，如下所示：

```c
//往网络线程发送的消息类型
enum MsgCmd_t
{
	MSG_CMD_UPDATE_TEMP=0,
	MSG_CMD_UPDATE_AXIS,
	MSG_CMD_UPDATE_TOKEN,
	MSG_CMD_LEVELING_1,
	MSG_CMD_LEVELING_2,
	MSG_CMD_LEVELING_3,
	MSG_CMD_LEVELING_4,
};
//往GCode转发线程发送的消息类型
enum Msg2GCode_t
{
	MSG_2_GCODE_CMD_AUTO_GET_TEMP = 0, 
	MSG_2_GCODE_CMD_PLA_PRE,
	MSG_2_GCODE_CMD_ABS_PRE,
	MSG_2_GCODE_CMD_TEMP_DROP,
	MSG_2_GCODE_CMD_X_MOVE_ADD,
	MSG_2_GCODE_CMD_X_MOVE_SUB,
	MSG_2_GCODE_CMD_Y_MOVE_ADD,
	MSG_2_GCODE_CMD_Y_MOVE_SUB,
	MSG_2_GCODE_CMD_Z_MOVE_ADD,
	MSG_2_GCODE_CMD_Z_MOVE_SUB,
	MSG_2_GCODE_CMD_ZERO_OF_X,
	MSG_2_GCODE_CMD_ZERO_OF_Y,
	MSG_2_GCODE_CMD_ZERO_OF_Z,
	MSG_2_GCODE_CMD_ZERO_OF_ALL,
	MSG_2_GCODE_CMD_LEVEL_DATA,
	MSG_2_GCODE_CMD_FAN_SETTING,
	MSG_2_GCODE_CMD_START_PRINT
};
```

消息类型的负载可能是没有任何内容的，可能是字符串类型，也可能是结构体类型，也可能是其它类型。要接收什么类型的数据，一般由消息类型决定，但最终如何实现也取决于用户的业务逻辑。因此，这样的设计方案可拓展性非常强。

#### 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request
