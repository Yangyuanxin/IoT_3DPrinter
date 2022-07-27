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


#define GCODE_PLA_PRE 	  	  "M140 S60\nM104 S190\n"
#define GCODE_ABS_PRE 	  	  "M140 S100\nM104 S240\n"
#define GCODE_TEMP_DROP 	  "M140 S0\nM104 S0\n"
#define GCODE_X_MOVE_ADD 	  "G91\nG1 F1500 X+10\nG90\nM114\n"
#define GCODE_X_MOVE_SUB      "G91\nG1 F1500 X-10\nG90\nM114\n"
#define GCODE_Y_MOVE_ADD 	  "G91\nG1 F1500 Y+10\nG90\nM114\n"
#define GCODE_Y_MOVE_SUB      "G91\nG1 F1500 Y-10\nG90\nM114\n"
#define GCODE_Z_MOVE_ADD 	  "G91\nG1 F1500 Z+10\nG90\nM114\nM114\n"
#define GCODE_Z_MOVE_SUB      "G91\nG1 F1500 Z-10\nG90\nM114\nM114\n"
#define GCODE_ZERO_OF_X	      "G28 X\n"
#define GCODE_ZERO_OF_Y	      "G28 Y\n"
#define GCODE_ZERO_OF_Z	      "G28 Z\n"
#define GCODE_ZERO_OF_ALL	  "G28\n"
#define GCODE_LEVELING_DATA   "M420V\n"
#define GCODE_FAN_SETTING 	  "M106 S%d\n"
#define GCODE_START_PRINT     "M23 TENCEN~1.GCO\nM24\n"
#define GCODE_AUTO_GET_TEMP   "M155 S4\n"

#define MSG_LEN 50

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

/*ÏûÏ¢·â×°*/
struct Msg_t
{
	uint8_t Type;
	char Data[50];
};

enum MsgGCodeReply_t
{
    MSG_NORMAL=0,
    MSG_LEVEING
};

extern const unsigned char gImage_wifi_config[45000];
extern const unsigned char gImage_icon_for_tencentos_tiny[24008];

#endif //__SYSTEMCONFIG_H
