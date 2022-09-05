# 基于TencentOS Tiny FDM 3D打印机云控制系统方案

#### 1、方案摘要
##### 1.1、前言
​    3D打印技术是增材制造的典型体现。它的原理是通过特定的切片软件将产品的3D设计模型图转换成3D打印机控制系统可以识别的控制代码，该控制代码在导入3D打印机控制系统后，3D打印机控制系统通过解析每一行控制代码，进而控制3D打印机打印模型。例如FDM打印机的打印原理，如下图1-1所示。

![01602f598a25c32cdec32e531cd4b8e7.png](https://img-blog.csdnimg.cn/img_convert/01602f598a25c32cdec32e531cd4b8e7.png)

​																			图1-1、3D打印原理

​	STL/Obj(当然还有很多种格式)文件就是模型本身的文件，它可能是由三维模型设计师、结构工程师设计出来的模型文件，也可能是通过3D扫描仪扫描出来的模型文件，而GCode就是通过切片软件将这些STL/Obj等模型文件切出来的一堆能够让3D打印机识别并运行的指令，它会告诉3D打印机应该如何去运行，例如以下是通过FDM Cura切片软件切出来的开源模型文件(如下图1-2所示)-可动盘龙的GCode代码(如下图1-3所示)：
![07fc66a3616903ca70148a604d1ce06e.png](https://img-blog.csdnimg.cn/img_convert/07fc66a3616903ca70148a604d1ce06e.png)

​																	图1-2、可动盘龙模型STL文件 

​	可动盘龙切片后生成的GCode文件：

![f11c2ca60c81e77412030d0c1eaa99fb.png](https://img-blog.csdnimg.cn/img_convert/f11c2ca60c81e77412030d0c1eaa99fb.png)

​																图1-3、可动盘龙GCode切片文件

开源下载地址：

```c
https://www.bilibili.com/video/BV1HM4y1A73r?spm_id_from=333.337.search-card.all.click
```

​	目前，3D打印技术在全球增材制造领域已经发展十分成熟。而我国的3D打印技术与欧美国家相比相对来说较为落后，具体体现在3D打印机技术在物联网方面的应用。目前，我国市场上的3D打印机大部分都不具备网络控制和管理功能，不能更好地与现代物联网信息时代接轨。

​	本次参加开发者成长激励计划的作品是基于TencentOS Tiny的FDM 3D打印机云控制系统方案，该方案初步构思一个基于FDM 3D打印机的云控制交互系统，实现对FDM 3D打印机的控制、信息交互等基本功能。相对于3D打印机本身来说，本次参赛作品的云控制系统方案相当于是一个上位机，而上位机的体现方式可以是串口屏、物联网通讯模块等其它任何组成形式。市面上常见的主流串口屏式3D打印机主流通信架构如下图1-4所示：
![a2e56ff98f5d4c39a120902e205ba29a.png](https://img-blog.csdnimg.cn/img_convert/a2e56ff98f5d4c39a120902e205ba29a.png)

​																图1-4、主流的3D打印机通讯架构

​	该方案的设计初衷是为TencentOS-tiny与腾讯云IoT结合在3D打印物联网方面的应用打下一定的基础。TencentOS-tiny与IoT Explorer结合在嵌入式设备端具备完善的从端到云，从云到端的一体化解决方案。因此，在未来，有TencentOS-tiny与IoT Explorer物联网平台的赋能加持，3D打印物联网方面的应用一定能够有更好的发展和创新的应用场景，为智能制造、工业集群、人工智能等行业做出更多的贡献，进而帮助企业提升研发和生产效率，降低人工和生产成本，实现规模经济。

##### 1.2、方案亮点

- 软件业务设计解耦，可拓展性强

- 支持多平台快速适配与工程迁移

- 支持腾讯连连WIFI Smart Config扫码配网功能

- 支持腾讯连连小程序数据上行(温度、坐标、调平数据等)

- 支持腾讯连连小程序数据下行(温度、移动轴、风扇速度设置等)

- 支持腾讯云IoT Explorer平台实时查看上报数据信息(对标腾讯连连小程序数据上行)

- 支持腾讯云IoT Explorer平台下发控制指令(对标腾讯连连小程序数据下行)

- 支持腾讯连连微信公众号、腾讯连连小程序移动轴、喷头温度过高信息预警信息推送

- 首次采用腾讯云可视化编辑器进行腾讯连连小程序界面的布局、事件、属性关联等。

- 实现3D打印机的基本控制和交互功能，未来可拓展成为云打印方式，实现3D打印机物联网打印。

##### 1.3、方案演示

项目Github仓库地址:

```c
https://github.com/Yangyuanxin/IoT_3DPrinter
```

项目Gitee仓库地址:

```c#
https://gitee.com/morixinguan/IoT_3DPrinter
```

功能演示地址：

```c
https://cloud.tencent.com/developer/video/32150
```

#### 2、方案构成
##### 2.1、硬件部分
​    硬件部分主要分为3D打印机(Anycubic Vyper 3D打印机)和3D打印机联网控制系统( 基于沁恒RISV-V MCU CH32V307VCT6芯片的CH32V_EVB开发平台)两部分，其中CH32V_EVB(如图2-2所示)作为上位机，而Anycubic Vyper 3D打印机则作为下位机，如下图2-1所示:

![637e96a70079a8b9e0e14b15c7236261.jpeg](https://img-blog.csdnimg.cn/img_convert/637e96a70079a8b9e0e14b15c7236261.jpeg)

​														图2-1、3D打印机控制系统硬件组成部分

![2d03539987d8f902a151e94c0ba54b4e.png](https://img-blog.csdnimg.cn/img_convert/2d03539987d8f902a151e94c0ba54b4e.png)

​																	图2-2、CH32V_EVB开发平台

 	Anycubic Vyper是一款优秀的3D打印机，不管是外观、打印速度、打印质量而言都相当不错。其固件源代码是基于著名的Marlin开源固件进行开发，它的源代码也是开源的，开源仓库地址：

```c
https://github.com/ANYCUBIC-3D/Vyper
```

​	用户可根据自身需求定制和修改Marlin固件来实现3D打印机的自定义功能，甚至也可以结合其它配件改装成为雕刻机等方案。CH32V_EVB是腾讯本次TencentOS Tiny RISC-V IoT训练营结合沁恒推出的RISV芯片方案的开发板，如下图2-3所示:

![489b29ec56b6c17341889f635776a1e7.png](https://img-blog.csdnimg.cn/img_convert/489b29ec56b6c17341889f635776a1e7.png)



​																图2-3、沁恒CH32V307开发板

##### 2.2、软件部分

​    软件部分是将3D打印机与TencentOS Tiny、腾讯云IoT Explorer、腾讯连连小程序进行结合，从而实现3D打印机物联网控制交互、数据交互的基本功能，其主要由以下三个部分构成，如下图2-2所示:

![ff911e6f4dc5ddfeb0bde6a32d6346e7.png](https://img-blog.csdnimg.cn/img_convert/ff911e6f4dc5ddfeb0bde6a32d6346e7.png)

​																				图2-3、交互框架图

#### 3、方案核心设计

​    方案的核心主要在于软件部分的设计，主要包括腾讯连连小程序部分以及嵌入式设备端部分。

##### 3.1、腾讯连连小程序部分
​    腾讯连连小程序部分采用的是IoT Explorer团队提供的最新的可视化面板编辑器来实现，可视化面板编辑器相对于标准面板(如图3-1所示)来说，控件种类和可操作性更加强大，即使开发者不懂微信小程序的开发，只需结合数据模版所提供的功能属性，即能够通过可视化面板编辑器轻松、快速做出功能丰富、样式好看、人机交互体验感超好的交互界面。

![bb8c9a051aca4e19f8a5f9b70f5bff07.png](https://img-blog.csdnimg.cn/img_convert/bb8c9a051aca4e19f8a5f9b70f5bff07.png)

​																	图3-1、标准面板界面的呈现

​	由于时间关系，目前仅用可视化面板编辑器规划了两个页面，如下图3-2所示:

![a09609bf79444ad1921fc23e165c30d5.jpeg](https://img-blog.csdnimg.cn/img_convert/a09609bf79444ad1921fc23e165c30d5.jpeg)

​															图3-2、腾讯连连小程序界面

##### 3.2、嵌入式设备端部分
​       嵌入式设备端部分主要包括TencentCloud IoT Explorer、APP、Common、OperatingSystem、Hardware、Bsp、McuPlatform这几个部分组成。其软件整体框架组织设计理念是为了方便项目的可持续功能迭代和未来的发展，如下图3-3所示：

![ae6b86d6b42ab9909f8eb819dca7c7fb.png](https://img-blog.csdnimg.cn/img_convert/ae6b86d6b42ab9909f8eb819dca7c7fb.png)

​																			图3-3、软件框架结构图

- **(1)TencentCloud IoT Explorer**

​	    腾讯IoT Explorer物联网设备管理平台、集成腾讯连连小程序、微信公众号推送等物联网业务。

- **(2)APP**

  主要为本项目的业务逻辑部分，主要分为串口数据解析、GCode命令转发、Mqtt订阅和发布业务处理等。

- **(3)Common**

  主要集成了提供给项目使用的软件组件，其中包括ringbuffer、cJSON、Mqtt、Log系统等其它组件。

- **(4)OperatingSystem**
  操作系统部分，目前仅支持TencentOS-tiny，TencentOS-tiny是一个内存占用极小、组件丰富、扩展性极强且效率极高的物联网实时操作系统。

- **(5)Hardware**
  主要实现了一些完成项目必备的硬件驱动程序，包括按键驱动、LCD驱动、LED驱动、WIFI驱动等。

- **(6)Bsp**

  主要是由Mcu平台提供的板级支持包，目前该部分仅支持CH32V_EVB平台，未来可继续添加更多平台提供的Bsp。

- **(7)McuPlatform**
  具体的Mcu平台，目前该部分仅支持CH32_EVB平台，未来可继续支持更多的平台。

##### 3.3、主业务流程详细设计
​    APP主业务流程分别创建三个线程来进行不同业务的处理，而线程间通信机制采用TencentOS-tiny提供的消息队列进行交互通讯，当线程没有接收到消息时，该线程为阻塞等待状态而不消耗CPU时间，直到接收到消息时，线程才恢复就绪态，对接收的数据进行处理。这样做的好处是能够高效的管理CPU资源，避免CPU资源浪费。

​	在APP主业务流程设计中，采用消息队列通讯也是一种软件设计解耦的实现方式，线程与线程之间通过消息队列通信，能够实现业务隔离，让整个系统的可拓展性大大提高。除此之外，采用消息队列的好处是能够携带数据载体，数据格式也可以由用户自定义。本次参赛的作品主业务流程设计思路如下图3-4所示:

![bfb14e6384264601ad22ba5856c6bc83.png](https://img-blog.csdnimg.cn/img_convert/bfb14e6384264601ad22ba5856c6bc83.png)

​																		图3-4、程序业务流程设计

​	其中，消息队列之间的数据传输设计是基于一个消息结构体来进行的，如下所示：

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

![551456f8ee992615dacfafdff8b711a5.png](https://img-blog.csdnimg.cn/img_convert/551456f8ee992615dacfafdff8b711a5.png)

​															3-6、Marlin自动获取温度上报命令

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

​	消息类型的负载可能是没有任何内容的，可能是字符串类型，也可能是结构体类型，也可能是其它类型。要接收什么类型的数据，一般由消息类型决定，但最终如何实现也取决于用户的业务逻辑。因此，这样的设计方案可拓展性非常强。

###### 3.3.1、主线程任务处理

**(1)完成消息队列、网络线程、GCode转发线程的创建。**

```c
#define DEFAULT_TASK_SIZE 2048
void StartMainTask(void *pdata);
osThreadDef(StartMainTask, osPriorityLow, 1, DEFAULT_TASK_SIZE);
 
#define GCODE_FORWARD_TASK_SIZE 1024
void StartGCodeForWardTask(void *arg);
osThreadDef(StartGCodeForWardTask, osPriorityHigh, 1, GCODE_FORWARD_TASK_SIZE);
 
#define MQTT_TASK_SIZE 2048
void StartNetworkTask(void *pdata);
osThreadDef(StartNetworkTask, osPriorityLow, 1, MQTT_TASK_SIZE);
//主线程往网络线程的消息队列
k_msg_q_t DataMsg;
uint8_t DataMsgPool[50];
//网络线程往GCode转发线程的消息队列
k_msg_q_t GCodeMsg;
uint8_t GCodeMsgPool[50];
 
.....省略部分代码
 
//创建主线程往网络线程的消息队列
err = tos_msg_q_create(&DataMsg, DataMsgPool, 50);
if (K_ERR_NONE != err)
{
     printf("Create DataMsg Fail:%d!\n", err);
     return;
}
//创建网络线程往GCode转发线程的消息队列
err = tos_msg_q_create(&GCodeMsg, GCodeMsgPool, 50);
if (K_ERR_NONE != err)
{
     printf("Create GCodeMsg Fail:%d!\n", err);
     return;
}
//创建网络线程
if (NULL == osThreadCreate(osThread(StartNetworkTask), NULL))
{
     printf("osThreadCreate Mqtt Fail!\n");
     return;
}
//创建GCode转发线程
if (NULL == osThreadCreate(osThread(StartGCodeForWardTask), NULL))
{
     printf("osThreadCreate StartGCodeForWardTask Fail!\n");
     return;
}
```

**(2)向打印机发送自动获取温度命令，用于定时获取打印机喷头、热床的温度数据上报。**

​	发送自动获取温度的命令主要是基于GCode命令传输协议，而3D打印机的通信方式就是基于GCode命令进行传输的，当我们向3D打印机串口发送GCode代码+\n(换行)，3D打印机串口接收到指令时，内部固件会对下发的指令进行处理并回复对应的数据。因此，我们可以到Marlin的官网上找到温度获取对应的GCode命令并在程序中进行设置，这样打印机就能够自动上报喷头、热床的温度了。以下是Marlin官方网站GCode指令查询：

```c
https://marlinfw.org/meta/gcode/
```

​	3D打印机获取温度有两种形式，一种可以是专门开一个3-4s的定时器，定时发送M105命令给3D打印机，这样3D打印机收到M105指令后，会返回温度数据。而Marlin官方并不建议采用这样的方式来获取温度，而是建议发送M155指令来让温度自动上报。因此，我们可以使用M155指令来避免这个问题，前提是3D打印机固件程序开启了AUTO_REPORT_TEMPRATURES宏，否则，我们就需要去修改3D打印机固件，以支持温度自动定时上报命令。使用方法如下图3-6所示:
![a07e6fdf9163ed5d06b8732488f7e224.png](https://img-blog.csdnimg.cn/img_convert/a07e6fdf9163ed5d06b8732488f7e224.png)

​														图3-6、Marlin自动获取温度上报命令

​	此部分的代码逻辑如下所示，先设置自动获取温度的消息类型，然后通过消息队列将消息转发给GCode转发线程，具体转发的内容到GCode转发线程部分会进行讲解，大致代码逻辑如下所示:

```c
/*M155 - Temperature Auto-Report*/
for (int i = 0; i < 3; i++)
{
    //设置消息类型，不需要带数据负载
    Msg.Type = MSG_2_GCODE_CMD_AUTO_GET_TEMP;
    //向GCode转发线程发送消息
    tos_msg_q_post(&GCodeMsg, (void *) &Msg);
}
.....省略部分代码
```

**(3)获取打印机上报的GCode命令回复的数据并进行解析，并进行温度等数据的显示以及将温度、移动轴坐标等信息通过消息队列转发给网络线程进行Topic发布。**

​	其中，GCode数据回复需要根据预判的信息进行处理，例如解析喷头和热床的温度数据，通过串口我们能够得知打印机上报的温度数据格式如下：

```c
T:27.00 /0.00 B:27.80 /0.00 @:0 B@:0(末尾是\n)       //The first byte is a space
ok T:27.03 /0.00 B:27.78 /0.00 @:0 B@:0(末尾是\n)     //The first two bytes consist of ok
```

数据的回复是从串口接收中断过来的，然后主线程通过读取环形队列的数据，再进行处理，大致逻辑如下：

```c
void UART7_IRQHandler(void)
{
     uint8_t data;
     osSchedLock();
     if (USART_GetITStatus(UART7, USART_IT_RXNE) != RESET)
     {
          data = USART_ReceiveData(UART7);
          //将接收的每一个字节写入环形队列
          ring_buffer_write(data,&Fifo);
     }
     osSchedUnLock();
}    
 
//主线程
void StartMainTask(void *arg)
{
      //......省略部分代码
      for (;;)
      {
          //从环形队列里取数据，存到缓存里，然后进行处理
          if (0 == ring_buffer_read(&data, &Fifo))
          {  
            //判断是否有一行
            if (data != '\n')
                 GCodeReplyBuff.GCodeLineBuff[GCodeReplyBuff.GCodeLineCount++] = data;
            else
            {
                GCodeReplyBuff.GCodeLineBuff[GCodeReplyBuff.GCodeLineCount] ='\0';
                 //todo:处理一行数据
                 //......省略部分代码
                 //todo end
                 memset(GCodeReplyBuff.GCodeLineBuff, 0, REPLY_MAX_LEN);
                 GCodeReplyBuff.GCodeLineCount = 0;
          }
      }
      osDelay(5);
  }
  //......省略部分代码
}
```

​	明白了数据接收和解析的方法后，我们来看看温度上报数据格式的特点。第一类温度上报指令通常是打印预热中上报的指令格式，它的特点是第一个字体恰好是空格，而第二类温度指令是属于设置类指令，当我们设置温度成功以后，3D打印机就会回复一个ok，然后空格接下来就是温度数据。根据上面温度上报的数据特征，我们能够很容易写出一个解析程序来提取对应的数据字段：

```c
typedef struct Temperature
{
     //喷头当前温度
     double nozzle_cur_temp;
     //喷头目标温度
     double nozzle_target_temp;
     //热床当前温度
     double hotbed_cur_temp;
     //热床目标温度
     double hotbed_target_temp;
} marlin_temp;
 
void marlin_data_buffer_bzero(void *s, size_t n)
{
     memset(s, 0, n);
}
 
/*
 example:
 T:27.00 /0.00 B:27.80 /0.00 @:0 B@:0     The first byte is a space
ok T:27.03 /0.00 B:27.78 /0.00 @:0 B@:0   The first two bytes consist of ok
 */
void Get_Temperature(char *str, marlin_temp *temp_info)
{
     char buf[10] = { 0 };
     int cut_out_len = 0;
     char *data_field = NULL;
     char *space_field = NULL;
     if (str[0] == ' ' && str[1] == 'T')
      str += 1;
     if (str[0] == 'o' && str[1] == 'k')
      str += 3;
     //找到分号
     data_field = strstr(str, ":");
     //找到空格
     space_field = strstr(str, " ");
     //算出分为和空格之间要提取的子串的长度
     cut_out_len = space_field - data_field - 1;
     //拷贝子串到临时缓冲区
     memcpy(buf, data_field + 1, cut_out_len);
     //将子串转换为浮点型并输出到结构体对应的变量中
     temp_info->nozzle_cur_temp = atof(buf);
     data_field = strstr(space_field, "/");
     space_field = strstr(space_field + 1, " ");
     cut_out_len = space_field - data_field - 1;
     marlin_data_buffer_bzero(buf, 10);
     memcpy(buf, data_field + 1, cut_out_len);
     temp_info->nozzle_target_temp = atof(buf);
     data_field = strstr(space_field, ":");
     space_field = strstr(space_field + 1, " ");
     cut_out_len = space_field - data_field - 1;
     marlin_data_buffer_bzero(buf, 10);
     memcpy(buf, data_field + 1, cut_out_len);
     temp_info->hotbed_cur_temp = atof(buf);
     data_field = strstr(space_field, "/");
     space_field = strstr(space_field + 1, " ");
     cut_out_len = space_field - data_field - 1;
     marlin_data_buffer_bzero(buf, 10);
     memcpy(buf, data_field + 1, cut_out_len);
     temp_info->hotbed_target_temp = atof(buf);
}
```

​	其它指令回复的格式则需要根据回复的消息进行处理，详情参考Marlin指令帮助文档:

```c
https://marlinfw.org/meta/gcode/
```

 当然，还有一种更简单的测试方式，那便是直接将串口线连接打印机和PC端，然后通过串口调试软件测试、查看指令的收发过程。

###### 3.3.2、网络线程处理
网络线程主要包括以下几个部分：

**(1)WIFI Esp8266初始化及SmartConfig配网功能**

​	WIFI Esp8266相关的操作都是基于AT框架来进行的。腾讯云定制的Esp8266固件能够实现与IoT explorer平台的快速对接、腾讯连连WIFI SmartConfig配网功能。至于如何烧写腾讯云定制固件，会在后续章节进行描述。该部分的代码实现大致的逻辑如下：

```c
//注册Sal，此处会自动调用内部的init函数来完成Esp8266的初始化
ret = esp8266_tencent_firmware_sal_init(HAL_UART_PORT_2);
if (ret < 0)
{
     printf("esp8266 tencent firmware sal init fail, ret is %d\r\n", ret);
     NVIC_SystemReset();
}
tos_task_delay(6000);
/*执行WIFI配网逻辑*/
WifiSmartConfig();
//省略部分代码.......
 
//WIFI Smart Config配网逻辑
static void WifiSmartConfig(void)
{
     int rssi;
     int channel = -1;
     static uint8_t ConfigWifi = 0;
     char ssid[50] = { 0 };
     char bssid[50] = { 0 };
     /*获取WIFI AP信息，如果返回-1，则说明获取不成功*/
     /*当开机前长按按键3，则进入WIFI配网模式*/
     if (-1 == tos_tf_module_get_info(ssid, bssid, &channel, &rssi)
           || 3 == Key_Scan())
     {
          /*进入配网模式 & 显示WIFI配网二维码*/
          LCD_Fill(0, 0, 240, 240, WHITE);
          GPIO_WriteBit(GPIOE, GPIO_Pin_5, 0); //亮灯提示
          LCD_ShowString(30, 10, "3D Printer Add", BLACK, WHITE, 24, 0);
          LCD_ShowPicture((240 - 150) / 2, (240 - 150) / 2, 150, 150,
            gImage_wifi_config);
          if (0 == tos_tf_module_smartconfig_start())
          {
               ConfigWifi = 1;
               LCD_Fill(0, 0, 240, 240, BLACK);
               tos_tf_module_smartconfig_stop();
          }
          else
          {
               LCD_ShowString(10, 10, "WifiConfig Error!", WHITE, BLACK, 32, 0);
               NVIC_SystemReset();
          }
     }
     if(0 == ConfigWifi)
          LCD_Fill(0, 0, 240, 120, BLACK);
     GPIO_WriteBit(GPIOE, GPIO_Pin_5, 1);
     //获取网络信息，并通过LCD将信息展示出来
     snprintf(esp8266_info.ssid, sizeof(esp8266_info.ssid), "ssid:%s", ssid);
     snprintf(esp8266_info.bssid, sizeof(esp8266_info.bssid), "bssid:%s", bssid);
     snprintf(esp8266_info.channel, sizeof(esp8266_info.channel), "channel:%d",channel);
     snprintf(esp8266_info.rssi, sizeof(esp8266_info.rssi), "rssi:%d", rssi);
     LCD_ShowString(10, 10, "Wifi Connect OK", WHITE, BLACK, 16, 0);
     LCD_ShowString(10, 26, esp8266_info.ssid, WHITE, BLACK, 16, 0);
     LCD_ShowString(10, 26 + 16, esp8266_info.bssid, WHITE, BLACK, 16, 0);
     LCD_ShowString(10, 26 + 16 + 16, esp8266_info.channel, WHITE, BLACK, 16, 0);
     LCD_ShowString(10, 26 + 16 + 16 + 16, esp8266_info.rssi, WHITE, BLACK, 16,0);
     LCD_ShowPicture(0,190, 240, 50,gImage_icon_for_tencentos_tiny);
}
```

**(2)腾讯云平台三元组配置、Mqtt服务器连接、Topic订阅及回调处理**

​	当Esp8266模块连接网络成功以后，接下来就要执行连接腾讯云Iot Explorer服务器的操作，这里我们需要在腾讯云Iot Explorer获取相应的设备三元组，三元组指的是产品ID、设备名称和密钥。在连接服务器时将三元组传递给服务器连接接口，这样才能成功连接上腾讯云Iot Explorer服务器。设备三元组相当于服务器对设备的鉴权功能，如果没有三元组，即使设备知道服务器的连接地址以及端口号并进行连接，即使连接成功，但服务器并不知道当前具体是哪一台设备，因此就无法在前端进行控制和交互了。此部分代码实现逻辑如下：

```c
//将设备三元组设置到模组中，然后进行Mqtt服务器连接操作
strncpy(dev_info.product_id, product_id, PRODUCT_ID_MAX_SIZE);
strncpy(dev_info.device_name, device_name, DEVICE_NAME_MAX_SIZE);
strncpy(dev_info.device_serc, key, DEVICE_SERC_MAX_SIZE);
tos_tf_module_info_set(&dev_info, TLS_MODE_PSK);
mqtt_param_t init_params = DEFAULT_MQTT_PARAMS;
if (tos_tf_module_mqtt_conn(init_params) != 0)
{
     printf("module mqtt conn fail\n");
     NVIC_SystemReset();
}
 
if (tos_tf_module_mqtt_state_get(&state) != -1)
{
     printf("MQTT: %s\n",state == MQTT_STATE_CONNECTED ? "CONNECTED" : "DISCONNECTED");
}
```

​	当服务器连接成功以后，接下来设备端需要订阅服务器的Topic，这样设备端才能够收到服务器下发的控制指令。当前，对于物模型设备，腾讯IoT explorer提供了三类Topic类型如下图3-7所示，分别是物模型Topic、系统级Topic以及自定义Topic:

![ce6d6060e469c743e196d409823a1a39.png](https://img-blog.csdnimg.cn/img_convert/ce6d6060e469c743e196d409823a1a39.png)

​																		图3-7、物模型Topic

而本项目采用的订阅Topic是物模型Topic：

```c
$thing/down/property/99LPJ2KWLM/${deviceName}
```

具体代码逻辑实现如下所示：

```c
/* 开始订阅topic */
size = snprintf(report_reply_topic_name, TOPIC_NAME_MAX_SIZE,
    "$thing/down/property/%s/%s", product_id, device_name);
if (size < 0 || size > sizeof(report_reply_topic_name) - 1)
{
   printf("sub topic content length not enough! content size:%d  buf size:%d",
     size, (int) sizeof(report_reply_topic_name));
    return;
}
if (tos_tf_module_mqtt_sub(report_reply_topic_name, QOS0,
     MessageParamsHandler) != 0)
{
   printf("module mqtt sub fail\n");
   NVIC_SystemReset();
}
```

当`Iot Explorer`下发消息时，将由`MessageParamsHandler`回调函数进行处理，部分代码逻辑如下所示：

```c
void MessageParamsHandler(mqtt_message_t* msg)
{
   struct Msg_t Msg;
   cJSON *root = NULL;
   cJSON *token = NULL;
   cJSON *params = NULL;
   cJSON *method = NULL;
   cJSON *led_control = NULL;
   cJSON *printer_control = NULL;
   cJSON *printer_fan_speed = NULL;
   char GCodeBuf[15] =
   { 0 };
   double result_fan_speed;
#if 0
   printf("mqtt callback:\r\n");
   printf("---------------------------------------------------------\r\n");
   printf("\ttopic:%s\r\n", msg->topic);
   printf("\tpayload:%s\r\n", msg->payload);
   printf("---------------------------------------------------------\r\n");
#endif
   /*1. 解析从云端收到的控制信息*/
   root = cJSON_Parse(msg->payload + 1);
   if (!root)
   {
    printf("Invalid json root\r\n");
    return;
   }
   /*2. 解析method*/
   method = cJSON_GetObjectItem(root, "method");
   if (!method)
   {
    printf("Invalid json method\r\n");
    cJSON_Delete(root);
    return;
   }
   /*3. 仅处理云端下发的 control 数据，report_reply暂不处理*/
   if (0 != strncmp(method->valuestring, "control", strlen("control")))
   {
    cJSON_Delete(root);
    return;
   }
   /*4. 解析出params*/
   params = cJSON_GetObjectItem(root, "params");
   if (!params)
   {
    printf("Invalid json params\r\n");
    cJSON_Delete(root);
    return;
   }
   /*5. 根据params，解析"params":{"power_switch":0}*/
   led_control = cJSON_GetObjectItem(params, "power_switch");
   if (led_control)
   {
    if (led_control->valueint)
    {
     DEBUG_LED(1)
    }
    else
    {
     DEBUG_LED(0)
    }
   }
   /*6. 根据params，解析"params":{"printing_control":3}*/
   printer_control = cJSON_GetObjectItem(params, "printing_control");
   if (printer_control)
   {
       //将具体的属性值转换为消息类型并转发给GCode转发线程
    Msg.Type = printer_control->valueint;
    tos_msg_q_post(&GCodeMsg, (void *) &Msg);
   }
 
   printer_fan_speed = cJSON_GetObjectItem(params, "fan_speed");
   if (printer_fan_speed)
   {
    memset(GCodeBuf, 0, 15);
    result_fan_speed = (double) printer_fan_speed->valueint / 255 * 2.55
      * 100 * 2.55;
    snprintf(GCodeBuf, sizeof(GCodeBuf), GCODE_FAN_SETTING,
      (int) result_fan_speed);
    //设置消息类型,并将处理完成的字符串拷贝到消息负载中
    //通过消息队列转发给GCode转发线程
    Msg.Type = MSG_2_GCODE_CMD_FAN_SETTING;
    memcpy(Msg.Data, GCodeBuf, sizeof(GCodeBuf));
    tos_msg_q_post(&GCodeMsg, (void *) &Msg);
   }
 
   /*7. 设置clientToken回复*/
   token = cJSON_GetObjectItem(root, "clientToken");
   if (token)
   {
       //设置消息类型为MSG_CMD_UPDATE_TOKEN,并转发给网络线程处理
    Msg.Type = MSG_CMD_UPDATE_TOKEN;
    tos_msg_q_post(&DataMsg, (void *) &Msg);
   }
   cJSON_Delete(root);
   root = NULL;
}
```

对3D打印机的控制则取的是printing_control属性，这块是由Iot Explorer的物模型JSON脚本决定的，此部分会在后续平台对接部分进行介绍，如下图3-8所示：

![f9e8ca4511102515000877c790c7468e.png](https://img-blog.csdnimg.cn/img_convert/f9e8ca4511102515000877c790c7468e.png)

​																			图3-8、物模型JSON

​	此部分是负责处理接收由主线程上报的消息，在没有消息到来时，它是阻塞等待的，直到接收到了具体的消息以后，才会改变状态往下执行，然后，通过具体的消息匹配具体需要发布内容。消息发布使用的物模型Topic如下所示：

```c
$thing/up/property/99LPJ2KWLM/${deviceName}
```

​	发布的消息格式主要在app_main.h中定义：

```c
/*喷头温度上报*/
#define REPORT_NOZZLE_TEMP_DATA_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"nozzle_temp\\\":\\\"%s\\\"}}"
 
/*喷头温度告警上报*/
#define REPORT_NOZZLE_TEMP_ALARM_DATA_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"nozzle_temp_alarm\\\":\\\"%s\\\"}}"
 
/*热床温度上报*/
#define REPORT_HOTBED_TEMP_DATA_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"hotbed_temp\\\":\\\"%s\\\"}}"
 
/*喷头位置上报*/
#define REPORT_POS_DATA_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"axis_text\\\":\\\"%s\\\"}}"
 
/*回复消息上报*/
#define CONTROL_REPLY_DATA_TEMPLATE       \
"{\\\"method\\\":\\\"control_reply\\\"\\,\\\"clientToken\\\":\\\"%s\\\"\\,\\\"code\\\":0\\,\\\"status\\\":\\\"ok\\\"}"
 
/*调平数据上报*/
#define REPORT_LEVELING_DATA1_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"level1_data\\\":\\\"%s\\\"}}"
 
#define REPORT_LEVELING_DATA2_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"level2_data\\\":\\\"%s\\\"}}"
 
#define REPORT_LEVELING_DATA3_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"level3_data\\\":\\\"%s\\\"}}"
 
#define REPORT_LEVELING_DATA4_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"level4_data\\\":\\\"%s\\\"}}"
 
#define REPORT_LEVELING_DATA_STATUS_TEMPLATE  \
"{\\\"method\\\":\\\"report\\\"\\,\\\"clientToken\\\":\\\"00000001\\\"\\,\\\"params\\\":{\\\"levelDataStatus\\\":\\\"%s\\\"}}"
```

​	这里需要将特定的数据与这个宏所定义的字符串进行拼接，然后调用tos_tf_module_mqtt_pub函数实现消息的发布，大致的代码逻辑如下所示：

```c
//....省略部分代码
memset(report_topic_name, 0, sizeof(report_topic_name));
size = snprintf(report_topic_name, TOPIC_NAME_MAX_SIZE,
  "$thing/up/property/%s/%s", product_id, device_name);
if (size < 0 || size > sizeof(report_topic_name) - 1)
{
 printf("pub topic content length not enough! content size:%d  buf size:%d",
   size, (int) sizeof(report_topic_name));
}
//....省略部分代码
while (1)
{
    //阻塞等待消息
 err = tos_msg_q_pend(&DataMsg, &MsgRecv, TOS_TIME_FOREVER);
 if(K_ERR_NONE == err)
 {
     if(K_ERR_NONE == err)
  {
   //将接收到的数据载体转换为消息类型结构体
   memcpy(&Msg,MsgRecv,sizeof(struct Msg_t));
   //匹配具体的消息类型并进行不同消息类型的处理
   switch(Msg.Type)
   {
       //上报温度数据
    case MSG_CMD_UPDATE_TEMP:
     ReportDeviceTemp((marlin_temp *)&Msg.Data);
    break;
    //上报轴移动坐标
    case MSG_CMD_UPDATE_AXIS:
     ReportDeviceAxis((marlin_coordinate *)&Msg.Data);
    break;
    //上报Client Token信息
    case MSG_CMD_UPDATE_TOKEN:
     ReportClientToken();
    break;
    //上报获取调平信息的数据
    case MSG_CMD_LEVELING_1:case MSG_CMD_LEVELING_2:
    case MSG_CMD_LEVELING_3:case MSG_CMD_LEVELING_4:
     ReportDeviceLevelData(Msg.Type,Msg.Data);
    break;
 
    default:
        printf("Msg.Type is Unknow!\n");
    break;
   }
  }
 }
 osDelay(5);
}
```

##### 3.3.3、GCode转发线程处理

​    GCode转发线程会将接收到的消息进行转换，然后判断消息类型的合法性，最后将消息映射为GCode命令并将其转发给3D打印机串口：

```c
//.....省略部分代码
typedef struct GCodeCmdHandler_t
{
    //命令类型
    uint8_t Type;
    //GCode命令
    char *GcodeCmd;
}GCodeCmdHandler_t;
//.....省略部分代码
 
//消息类型对应GCode代码映射表
GCodeCmdHandler_t Msg2GCodeTab[] =
{
     {MSG_2_GCODE_CMD_AUTO_GET_TEMP,GCODE_AUTO_GET_TEMP },
     {MSG_2_GCODE_CMD_PLA_PRE, GCODE_PLA_PRE },
     {MSG_2_GCODE_CMD_ABS_PRE, GCODE_ABS_PRE },
     {MSG_2_GCODE_CMD_TEMP_DROP,GCODE_TEMP_DROP },
     {MSG_2_GCODE_CMD_X_MOVE_ADD, GCODE_X_MOVE_ADD },
     {MSG_2_GCODE_CMD_X_MOVE_SUB, GCODE_X_MOVE_SUB },
     {MSG_2_GCODE_CMD_Y_MOVE_ADD, GCODE_Y_MOVE_ADD },
     {MSG_2_GCODE_CMD_Y_MOVE_SUB, GCODE_Y_MOVE_SUB },
     {MSG_2_GCODE_CMD_Z_MOVE_ADD, GCODE_Z_MOVE_ADD },
     {MSG_2_GCODE_CMD_Z_MOVE_SUB, GCODE_Z_MOVE_SUB },
     {MSG_2_GCODE_CMD_ZERO_OF_X, GCODE_ZERO_OF_X },
     {MSG_2_GCODE_CMD_ZERO_OF_Y, GCODE_ZERO_OF_Y },
     {MSG_2_GCODE_CMD_ZERO_OF_Z, GCODE_ZERO_OF_Z },
     {MSG_2_GCODE_CMD_ZERO_OF_ALL, GCODE_ZERO_OF_ALL },
     {MSG_2_GCODE_CMD_LEVEL_DATA, GCODE_LEVELING_DATA },
     {MSG_2_GCODE_CMD_START_PRINT, GCODE_START_PRINT }
};
 
//GCode转发线程
void StartGCodeForWardTask(void *arg)
{
 (void) arg;
 k_err_t err;
 char *GCode;
 void *MsgRecv;
 struct Msg_t Msg;
 for (;;)
 {
     //阻塞等待消息
  err = tos_msg_q_pend(&GCodeMsg, &MsgRecv, TOS_TIME_FOREVER);
  if (K_ERR_NONE == err)
  {
      //将接收到的数据转换为消息类型结构体
   memcpy(&Msg, MsgRecv, sizeof(struct Msg_t));
   //判断消息类型是否合法
   if (Msg.Type > MSG_2_GCODE_CMD_START_PRINT)
    printf("Msg.Type is Unknow!\n");
   else
   {
       //如果是设置风扇速度，则进行特殊处理
    if (MSG_2_GCODE_CMD_FAN_SETTING == Msg.Type)
     GCodeForward(Msg.Data, GCode_Send);
    //否则直接调用表中的GCode命令将其发送给3D打印机串口
    else
    {
     GCode = Msg2GCodeTab[Msg.Type].GcodeCmd;
     GCodeForward(GCode, GCode_Send);
    }
   }
  }
  osDelay(5);
 }
}
 
//以下是GCode转发线程调用的接口
//GCode命令转发
char *GCodeForward(char *Gcode, void(*GCodeToSend)(char *))
{
 if(NULL == Gcode || NULL == GCodeToSend)
  return NULL;
 GCodeToSend(Gcode);
 return "OK";
}
 
//往串口发送字符串
void GCode_Send(char *str)
{
 osSchedLock();
 //发之前关闭接收中断
 USART_ITConfig(UART7, USART_IT_RXNE, DISABLE);
 while(*str != '\0')
 {
  USART_SendData(UART7, *str++);
  while(USART_GetFlagStatus(UART7, USART_FLAG_TC) == RESET);
 }
 /*清除发送标志位*/
 USART_ClearFlag(UART7,USART_FLAG_TC);
 USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);
 //发完开启接收中断
 osSchedUnLock();
}
```

#### 4、腾讯云IoT Explorer平台和腾讯连连小程序的对接设计
​    整个方案的开发依托于腾讯云固件，腾讯云固件支持的AT指令十分丰富，能够实现WIFI配网、MQTT连接、订阅、发布等各种强大的功能。但是在开发之前，我们需要给开发板烧写固件程序。

##### 4.1、腾讯云ESP8266固件烧录
###### 4.1.1、硬件原理图与板载硬件熟悉
**(1)硬件原理图**

![d3389a5b0e0cc6cb7f3473bff442ea06.png](https://img-blog.csdnimg.cn/img_convert/d3389a5b0e0cc6cb7f3473bff442ea06.png)

​														图4-1、串口切换电路以及WIFI网络电路图

**(2)开发板实物所对应的管脚位置图**

![afdb6e68a492c5f784f7deb20dbfa2d7.png](https://img-blog.csdnimg.cn/img_convert/afdb6e68a492c5f784f7deb20dbfa2d7.png)

​												图4-2、串口切换电路图对应实际硬件上的具体位置

![6368af89af4aba3a6dcf8988054df1c2.png](https://img-blog.csdnimg.cn/img_convert/6368af89af4aba3a6dcf8988054df1c2.png)

​												图4-3、WIFI网络电路图对应实际硬件上的具体位置

**(3)将开发板与PC连接**

![09766c91adf3675f8672ffdd5bfb560b.png](https://img-blog.csdnimg.cn/img_convert/09766c91adf3675f8672ffdd5bfb560b.png)

​														图4-4、将开发板与电脑的USB口进行连接

###### 4.1.2、ESP8266腾讯云固件烧录

**(1)打开ESP8266固件烧录软件**

![ee594375d2f03dd4c0d58354ae0fe00c.png](https://img-blog.csdnimg.cn/img_convert/ee594375d2f03dd4c0d58354ae0fe00c.png)

​																		图4-5、ESP8266烧录软件

**(2)设置ESP8266固件烧录参数并开始烧录软件**

![8f6f42920b1a3bb49147d39e1090a8f1.png](https://img-blog.csdnimg.cn/img_convert/8f6f42920b1a3bb49147d39e1090a8f1.png)

​												图4-6、ESP8266烧录软件参数设置以及开始烧录

​	如图4-6所示，烧录成功。烧录成功后需要将H5口跳线帽短接回3.3V处，如图4-7所示，将ESP8266设置为正常模式：

![04711e1c20ea8c606401931a0d95cc7f.png](https://img-blog.csdnimg.cn/img_convert/04711e1c20ea8c606401931a0d95cc7f.png)

​																	图4-7、切换为正常模式

###### 4.1.3、测试ESP8266腾讯云固件是否烧录成功

​    打开TencentOS Tiny RISC-V IoT训练营资料中的腾讯云wifi固件里的腾讯云IoT-AT指令集，如图4-8所示：

![ccfee6ba5c14e52ff4f3a47c750e82f7.png](https://img-blog.csdnimg.cn/img_convert/ccfee6ba5c14e52ff4f3a47c750e82f7.png)

​																	图4-8、腾讯云IoT-AT指令集手册

​	打开串口调试软件，发送AT+TCMODULE指令，这里我用的是SSCOM5.13软件：

![a6b13468def35452ed16b7fbc710fe95.png](https://img-blog.csdnimg.cn/img_convert/a6b13468def35452ed16b7fbc710fe95.png)

​																图4-9、ESP8266模组信息回复

​	如上图4-9所示，能看到指令回复的模组信息则代表腾讯云固件已经成功烧录在ESP8266 WIFI模块中了。如果需要通过PC测试WIFI模块，则如下图4-10所示进行连接，这样连接电脑串口软件，默认情况下上电打印的是WIFI模块的LOG信息：

![a4de31622fc1d25c2dc554662f1c1294.png](https://img-blog.csdnimg.cn/img_convert/a4de31622fc1d25c2dc554662f1c1294.png)

​															图4-10、ESP8266 PC端AT交互模式

 	如果需要通过MCU串口与WIFI连接进行通信，则如下图4-11所示进行连接，这样连接电脑串口软件，默认情况下上电打印的是MCU的LOG信息：

![4db0d9b57ad3bbd6bc850b229c167643.png](https://img-blog.csdnimg.cn/img_convert/4db0d9b57ad3bbd6bc850b229c167643.png)

​																图4-11、ESP8266与MCU连接

![da6c5959c8803ec82fa2e43e8867a5d6.png](https://img-blog.csdnimg.cn/img_convert/da6c5959c8803ec82fa2e43e8867a5d6.png)

​															图4-12、ESP8266连接MCU串口图

​	一般情况下，在烧录完WIFI模组固件并且测试固件烧录成功以后，后续就进入真正的程序开发阶段，这时候需要将WIFI模块的串口与MCU的串口进行连接。

​	至此，ESP8266固件烧录完毕，接下来就可以编写程序和IoT Explorer平台和腾讯连连小程序进行交互了。

##### 4.2、腾讯云IoT Explorer与腾讯连连小程序配置

关于腾讯云IoT Explorer产品创建等流程可参考TencentOS官方公众号文章：

```c
https://mp.weixin.qq.com/s/t8iVaypA1BtZwt7EEkAWyw
```

​	本次参赛的作品方案是基于标准模板进行创建，而本作品是在标准模板的基础上做了相应的修改，其数据模板如下所示：

```json
{
  "version": "1.0",
  "properties": [
    {
      "id": "power_switch",
      "name": "灯光",
      "desc": "控制灯光",
      "mode": "rw",
      "required": true,
      "define": {
        "type": "bool",
        "mapping": {
          "0": "关灯",
          "1": "开灯"
        }
      }
    },
    {
      "id": "printing_control",
      "name": "3D打印机控制",
      "desc": "3D打印机控制",
      "mode": "rw",
      "define": {
        "type": "enum",
        "mapping": {
          "0": "指令回应",
          "1": "PLA预热",
          "2": "ABS预热",
          "3": "降温",
          "4": "X轴移动正10",
          "5": "X轴移动负10",
          "6": "Y轴移动正10",
          "7": "Y轴移动负10",
          "8": "Z轴移动正10",
          "9": "Z轴移动负10",
          "10": "X轴归零",
          "11": "Y轴归零",
          "12": "Z轴归零",
          "13": "全部归零",
          "14": "调平数据",
          "15": "开始打印"
        }
      },
      "required": false
    },
    {
      "id": "axis_text",
      "name": "显示位置信息",
      "desc": "位置",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "nozzle_temp",
      "name": "喷头温度",
      "desc": "摄氏度",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "hotbed_temp",
      "name": "热床温度",
      "desc": "摄氏度",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "levelDataStatus",
      "name": "获取调平数据状态",
      "desc": "N/A",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "level1_data",
      "name": "调平数据1",
      "desc": "N/A",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "level2_data",
      "name": "调平数据2",
      "desc": "N/A",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "level3_data",
      "name": "调平数据3",
      "desc": "N/A",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "level4_data",
      "name": "调平数据4",
      "desc": "N/A",
      "mode": "r",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    },
    {
      "id": "fan_speed",
      "name": "风扇速度",
      "desc": "",
      "mode": "rw",
      "define": {
        "type": "int",
        "min": "0",
        "max": "100",
        "start": "0",
        "step": "1",
        "unit": "风速"
      },
      "required": false
    },
    {
      "id": "nozzle_temp_alarm",
      "name": "喷头温度告警",
      "desc": "",
      "mode": "rw",
      "define": {
        "type": "string",
        "min": "0",
        "max": "2048"
      },
      "required": false
    }
  ],
  "events": [],
  "actions": [],
  "profile": {
    "ProductId": "99LPJ2KWLM",
    "CategoryId": "539"
  }
}
```

将模板导入平台后，就可以和设备平台进行交互了。

![7a366d7b090dd7f3a52eac2573ecd443.png](https://img-blog.csdnimg.cn/img_convert/7a366d7b090dd7f3a52eac2573ecd443.png)

​														图4-13、数据模板导入IoT explorer平台

接下来配置相应的小程序功能，如下图4-14所示：

![bcb501e5abb94e81c1628bd4038b6232.png](https://img-blog.csdnimg.cn/img_convert/bcb501e5abb94e81c1628bd4038b6232.png)

​																			图4-14、配置小程序

**(1)产品显示配置**

![18e7ea4c74a1cad8f872482324765b58.png](https://img-blog.csdnimg.cn/img_convert/18e7ea4c74a1cad8f872482324765b58.png)

​																			图4-15、产品显示配置

**(2)快捷入口配置**

![329dd926ab7f6eca49bf8c0c8afe97c3.png](https://img-blog.csdnimg.cn/img_convert/329dd926ab7f6eca49bf8c0c8afe97c3.png)

​																			图4-16、快捷入口配置

**(3)面板配置**

​    如下图4-17所示，这里我用的是可视化编辑面板来进行开发：

![dea6cb51f9a5fe316b0a46250ba55491.png](https://img-blog.csdnimg.cn/img_convert/dea6cb51f9a5fe316b0a46250ba55491.png)

​																		图4-17、可视化编辑面板

​    可视化编辑面板的操作十分简单，即使不需要文档学习，也能够很快上手，如下图4-18所示：

![5c7520747a2520908fe175708a143499.png](https://img-blog.csdnimg.cn/img_convert/5c7520747a2520908fe175708a143499.png)

​																	图4-18、可视化编辑模板介绍

**(4)配网引导**

这里我选择的是乐鑫+Smart Config的方式：

![94524b40ec73fffda73cf5117a4c5271.png](https://img-blog.csdnimg.cn/img_convert/94524b40ec73fffda73cf5117a4c5271.png)

​																			图4-18、配网方式配置

然后点击保存进入配网引导页的设计，如下图4-19所示：

![2a8198584b3fe803a03055a951b4a57c.png](https://img-blog.csdnimg.cn/img_convert/2a8198584b3fe803a03055a951b4a57c.png)

​																			图4-19、配网引导页

然后我们就需要将这个页面右下角生成的二维码保存起来，如下图4-20所示，详情访问以下链接：

```c
https://cloud.tencent.com/developer/article/2061046
```

​																		图4-20、配网引导页二维码

接下来通过image2Lcd将这个二维码转成能够在Mcu Lcd上显示的数组：

```c
https://cloud.tencent.com/developer/article/2061046
```

​													图4-21、将配网引导页二维码转换为C语言数组

然后将生成的这个数组复制到代码工程里：

```c
https://cloud.tencent.com/developer/article/2061046
```

​																图4-21、配网引导页C语言数组定义

 后续在程序中需要调用显示bmp的函数，即可显示二维码，最终效果如下图4-22所示：

```c
https://cloud.tencent.com/developer/article/2061046
```

​															图4-22、配网引导页在硬件平台上显示

 当设备进入配网模式后，会显示该二维码，用手机扫描二维码以后，根据嵌入式平台上的程序以及小程序上的提示逻辑进行WIFI配网，如图4-23所示:

![ce28eaaa82ff075e1bea8f969769bff7.jpeg](https://img-blog.csdnimg.cn/img_convert/ce28eaaa82ff075e1bea8f969769bff7.jpeg)

​																		图4-23、WIFI配网流程

##### 4.3、数据流配置

​    此部分是为了实现腾讯连连公众号和腾讯连连小程序的告警功能，如下图4-24所示，总共配置了两个数据流，分别是喷头移动、喷头温度过高：

![190c30764886391e884cc60f1bbb1e79.png](https://img-blog.csdnimg.cn/img_convert/190c30764886391e884cc60f1bbb1e79.png)

​																			图4-24、数据流配置

​    以数据流-喷头温度过高为例。我们这里需要获取设备数据来源，设备数据的输入来源直接来源于设备数据属性，它与前面的数据模板里的属性数据是一一对应的关系，如下图4-25所示：

![6fe2024d17bd800bae50522299acae36.png](https://img-blog.csdnimg.cn/img_convert/6fe2024d17bd800bae50522299acae36.png)																	图4-25、数据流输入节点配置

​    有了输入，当然要有输出吧，这里我们可以增加处理条件，也可以直接输出，这里我采用的是直接输出的方式，将数据直接推送到腾讯连连小程序APP以及公众号上，如下图4-26所示:

![0cec7fafa44bdc363de0efc573d3ee97.png](https://img-blog.csdnimg.cn/img_convert/0cec7fafa44bdc363de0efc573d3ee97.png)

​																	图4-25、数据流输出详细配置

当特定条件触发时，以喷头移动为例，显示效果如下图4-26所示：

![ac97e379223c5f8a7c48c65a6814c89b.jpeg](https://img-blog.csdnimg.cn/img_convert/ac97e379223c5f8a7c48c65a6814c89b.jpeg)

​																		图4-26、设备告警显示效果

​    至此，本方案的腾讯云IoT Explorer与腾讯连连小程序配置完毕，能够与嵌入式平台进行数据上行和下行交互。

#### 5、使用腾讯云IoT Explorer平台和腾讯连连的感受
​    腾讯云IoT Explorer平台与腾讯连连的结合，能够在产品开发前期以最快的速度提供物联网样机前端页面交互Demo。即使是基于腾讯云与腾讯连连打造的量产产品，也能够快速的实现方案开发，因为腾讯云IoT Explorer已经提供了多个行业的成熟解决方案，因此能够帮助用户实现端到云的融合，赋能物联产业的发展。

#### 6、本次活动收获
​    本次参加开发者成长激励计划，让我全方面学习了TencentOS-tiny操作系统的使用，在主业务和程序框架设计上考虑了RTOS中各个组件的实际应用场景，让我能够在实际方案开发过程中真正掌握RTOS的应用开发和组件的使用。另外，基于TencentOS-Tiny 3D打印机云控制系统方案，也是作为TencentOS-tiny赋能3D打印行业的开始。经过本次学习和实践，将会让我在未来在其它相关方案的物联网应用开发上有更深的理解。

#### 7、持续开源计划

​	这是一个全平台的TencentOS Tiny 3D打印机云控制系统方案，包括基于腾讯云IoT Explorer物联网平台、腾讯连连小程序以及3D打印控制系统固件的开发，该方案作为本年度腾讯AIoT开发者成长激励计划的参赛项目，其整体架构设计如下图所示：

![ae6b86d6b42ab9909f8eb819dca7c7fb.png](https://img-blog.csdnimg.cn/img_convert/ae6b86d6b42ab9909f8eb819dca7c7fb.png)	该项目分为TencentCloud IoT Explorer、APP、Common、Operating System、Hardware、Bsp、McuPlatform这几个部分，每个部分的功能如下：

###### 1、TencentCloud IoT Explorer

腾讯IoT Explorer物联网设备管理平台、集成腾讯连连小程序、微信公众号推送等物联网业务。

###### 2、APP

主要为本项目的业务逻辑部分，主要分为串口数据解析、GCode命令转发、Mqtt订阅和发布业务处理等。

###### 3、Common 

主要集成了提供给项目使用的软件组件，其中包括ringbuffer、cJSON、Mqtt、Log系统等其它组件。

###### 4、Operating System

目前仅支持TencentOS-tiny，TencentOS-tiny，是一个内存占用极小、组件丰富且效率极高的实时操作系统。

###### 5、Hardware

主要实现了一些完成项目必备的硬件驱动程序，包括按键驱动、LCD驱动、LED驱动、WIFI驱动等。

###### 6、Bsp

主要是由Mcu平台提供的板级支持包，目前该部分仅支持基于沁恒CH32V_EVB开发套件。

###### 7、McuPlatform

具体的Mcu平台，目前该部分仅支持CH32_EVB平台。

#### 8、项目目录

##### 8.1、Firmware

与腾讯云IoT Explorer、腾讯连连、3D打印机的固件源代码。

##### 8.2、Hardware

开发板硬件原理图及芯片数据手册。

##### 8.3、3Dprinter_firmware

Anycubic 3D打印机Vyper固件。

##### 8.4、Resource

存放TencentOS-tiny图标、腾讯云平台Json模板、测试3D模型、WIFI固件及烧录方法、视频和PPT。

#### 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request
