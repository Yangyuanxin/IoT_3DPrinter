#ifndef __SYSTEMCONFIG_H
#define __SYSTEMCONFIG_H
/*ISO*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/*ISO End*/

/*Hardware*/
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "uart.h"
#include "delay.h"
#include "lcd_init.h"
/*Hardware End*/

/*Custom*/
#include "cJSON.h"
#include "ring_buffer.h"
#include "gcode_forward.h"
#include "gcode_analysis.h"
extern ring_buffer Fifo;
/*Custom End*/

/*OperatingSystem*/
#include "tos_k.h"
#include "tos_at.h"
#include "cmsis_os.h"
#include "esp8266_tencent_firmware.h"
#include "tencent_firmware_module_wrapper.h"
extern k_msg_q_t DataMsg;
extern k_msg_q_t GCodeMsg;
extern __IO uint8_t MqttInitFlag;
extern at_agent_t esp8266_tf_agent;
/*OperatingSystem End*/

/*McuPlatform*/
#include "ch32v30x_it.h"
extern GCodeReplyBuff_t GCodeReplyBuff;
/*McuPlatform End*/

#define UPDATE_TEMP  "UpdateTemp"
#define UPDATE_AXIS  "UpdateAxis"
#define UPDATE_TOKEN "ClientToken"
#define UPDATE_LEVELING1 "Leveling1"
#define UPDATE_LEVELING2 "Leveling2"
#define UPDATE_LEVELING3 "Leveling3"
#define UPDATE_LEVELING4 "Leveling4"
#define AUTO_GET_TEMP_MCODE "M155 S4\n"

enum MsgCmd_t
{
	MSG_CMD_UPDATE_TEMP=0,
	MSG_CMD_UPDATE_AXIS,
	MSG_CMD_UPDATE_TOKEN,
	MSG_CMD_LEVELING_1,
	MSG_CMD_LEVELING_2,
	MSG_CMD_LEVELING_3,
	MSG_CMD_LEVELING_4
};

enum MsgGCodeReply_t
{
    MSG_NORMAL=0,
    MSG_LEVEING
};

extern const unsigned char gImage_wifi_config[45000];
extern const unsigned char gImage_icon_for_tencentos_tiny[24008];

#endif //__SYSTEMCONFIG_H
