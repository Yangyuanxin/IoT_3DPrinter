/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Yuanxin.Yang
 * Version            : V1.0.0
 * Date               : 2022/07/04
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "app_main.h"
#include "SystemConfig.h"

__IO uint8_t MqttInitFlag = 0;
static void DisplayTemp(marlin_temp temp);
static void DisplayAxis(marlin_coordinate axis);

#define DEFAULT_TASK_SIZE 2048
void StartMainTask(void *pdata);
osThreadDef(StartMainTask, osPriorityLow, 1, DEFAULT_TASK_SIZE);

#define GCODE_FORWARD_TASK_SIZE 1024
void StartGCodeForWardTask(void *arg);
osThreadDef(StartGCodeForWardTask, osPriorityHigh, 1, GCODE_FORWARD_TASK_SIZE);

#define MQTT_TASK_SIZE 2048
void StartNetworkTask(void *pdata);
osThreadDef(StartNetworkTask, osPriorityLow, 1, MQTT_TASK_SIZE);

ring_buffer Fifo;

k_msg_q_t DataMsg;
uint8_t DataMsgPool[50];

k_msg_q_t GCodeMsg;
uint8_t GCodeMsgPool[50];

/*MQTT任务处理*/
void StartNetworkTask(void *pdata)
{
	(void) pdata;
	printf("StartNetworkTask...\n");
	MqttTask();
}

/*GCode转发线程*/
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

void StartGCodeForWardTask(void *arg)
{
	(void) arg;
	k_err_t err;
	char *GCode;
	void *MsgRecv;
	struct Msg_t Msg;
	for (;;)
	{
		err = tos_msg_q_pend(&GCodeMsg, &MsgRecv, TOS_TIME_FOREVER);
		if (K_ERR_NONE == err)
		{
			memcpy(&Msg, MsgRecv, sizeof(struct Msg_t));
			if (Msg.Type > MSG_2_GCODE_CMD_START_PRINT)
				printf("Msg.Type is Unknow!\n");
			else
			{
				if (MSG_2_GCODE_CMD_FAN_SETTING == Msg.Type)
					GCodeForward(Msg.Data, GCode_Send);
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

/*
 * 1.完成消息队列、网络线程、GCode转发线程的创建
 * 2.向打印机发送自动获取温度命令，用于定时获取打印机的温度数据上报
 * 3.获取打印机上报的GCode命令回复数据并进行解析
 *   将温度、移动坐标、调平数据等通过消息队列转发。
 * */
void StartMainTask(void *arg)
{
	(void) arg;
	uint8_t data;
	k_err_t err;
	struct Msg_t Msg;
	marlin_temp temp;
	marlin_coordinate axis;
	static uint8_t status = 0;
	static uint8_t getleveldata = 0;
	static uint8_t parser_count = 0;
	static uint8_t parser_status = 0;
	osSchedLock();
	err = tos_msg_q_create(&DataMsg, DataMsgPool, 50);
	if (K_ERR_NONE != err)
	{
		printf("Create DataMsg Fail:%d!\n", err);
		return;
	}
	err = tos_msg_q_create(&GCodeMsg, GCodeMsgPool, 50);
	if (K_ERR_NONE != err)
	{
		printf("Create GCodeMsg Fail:%d!\n", err);
		return;
	}
	if (NULL == osThreadCreate(osThread(StartNetworkTask), NULL))
	{
		printf("osThreadCreate Mqtt Fail!\n");
		return;
	}
	if (NULL == osThreadCreate(osThread(StartGCodeForWardTask), NULL))
	{
		printf("osThreadCreate StartGCodeForWardTask Fail!\n");
		return;
	}
	osSchedUnLock();
	parser_count = 0;
	parser_status = MSG_NORMAL;
	/*M155 - Temperature Auto-Report*/
	for (int i = 0; i < 3; i++)
	{
		Msg.Type = MSG_2_GCODE_CMD_AUTO_GET_TEMP;
		tos_msg_q_post(&GCodeMsg, (void *) &Msg);
	}
	LCD_ShowPicture(0, 190, 240, 50, gImage_icon_for_tencentos_tiny);
	for (;;)
	{
		if (0 == ring_buffer_read(&data, &Fifo))
		{
			if (data != '\n')
				GCodeReplyBuff.GCodeLineBuff[GCodeReplyBuff.GCodeLineCount++] =
						data;
			else
			{
				GCodeReplyBuff.GCodeLineBuff[GCodeReplyBuff.GCodeLineCount] =
						'\0';
				printf("reply:%s\n", GCodeReplyBuff.GCodeLineBuff);
				status = !status;
				DEBUG_GET_TEMP_LED(status);
				if ((GCodeReplyBuff.GCodeLineBuff[0] == ' '
						&& GCodeReplyBuff.GCodeLineBuff[1] == 'T')
						|| GCodeReplyBuff.GCodeLineBuff[3] == 'T')
				{
					Get_Temperature(GCodeReplyBuff.GCodeLineBuff, &temp);
					Msg.Type = MSG_CMD_UPDATE_TEMP;
					memset(Msg.Data, 0, sizeof(Msg.Data));
					memcpy(Msg.Data, &temp, sizeof(marlin_temp));
					if (MqttInitFlag && 0 == getleveldata)
					{
						DisplayTemp(temp);
						tos_msg_q_post(&DataMsg, (void *) &Msg);
					}
				}
				else if (GCodeReplyBuff.GCodeLineBuff[0] == 'X'
						&& GCodeReplyBuff.GCodeLineBuff[1] == ':')
				{
					Get_Move_Coordinate(GCodeReplyBuff.GCodeLineBuff, &axis);
					Msg.Type = MSG_CMD_UPDATE_AXIS;
					memset(Msg.Data, 0, sizeof(Msg.Data));
					memcpy(Msg.Data, &axis, sizeof(marlin_coordinate));
					if (MqttInitFlag && 0 == getleveldata)
					{
						DisplayAxis(axis);
						tos_msg_q_post(&DataMsg, (void *) &Msg);
					}
				}

				if (strstr(GCodeReplyBuff.GCodeLineBuff,"Bilinear Leveling Grid:"))
				{
					getleveldata = 1;
					parser_status = MSG_LEVEING;
				}
				if (MSG_LEVEING == parser_status)
				{
					if (parser_count < 6)
					{
						parser_count++;
						if (3 == parser_count)
							Msg.Type = MSG_CMD_LEVELING_1;
						else if (4 == parser_count)
							Msg.Type = MSG_CMD_LEVELING_2;
						else if (5 == parser_count)
							Msg.Type = MSG_CMD_LEVELING_3;
						else if (6 == parser_count)
							Msg.Type = MSG_CMD_LEVELING_4;
						memset(Msg.Data, 0, sizeof(Msg.Data));
						memcpy(Msg.Data, GCodeReplyBuff.GCodeLineBuff + 2,
								strlen(GCodeReplyBuff.GCodeLineBuff) - 2);
						tos_msg_q_post(&DataMsg, (void *) &Msg);
					}
					else
					{
						parser_count = 0;
						getleveldata = 0 ;
						parser_status = MSG_NORMAL;
					}
				}
				memset(GCodeReplyBuff.GCodeLineBuff, 0, REPLY_MAX_LEN);
				GCodeReplyBuff.GCodeLineCount = 0;
			}
		}
		osDelay(5);
	}
}
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	osStatus Status;
	Delay_Init();
	Delay_Ms(1000);
	Led_Init();
	Key_Init();
	LCD_Init();
	LCD_BLK_Clr();
	USART_Printf_Init(115200);
	printer_uart_init(115200);
	LCD_Fill(0, 0, 240, 240, BLACK);
	LCD_BLK_Set();
	ring_buffer_init(&Fifo);
	//关闭串口接收中断
	USART_ITConfig(UART7, USART_IT_RXNE, DISABLE);
	Status = osKernelInitialize();
	if (osOK != Status)
	{
		printf("osKernelInitialize Fail:%d!\n", Status);
		return -1;
	}
	if (NULL == osThreadCreate(osThread(StartMainTask), NULL))
	{
		printf("osThreadCreate StartMainTask Fail!\n");
		return -1;
	}
	Status = osKernelStart();
	if (osOK != Status)
	{
		printf("osKernelStart Fail:%d!\n", Status);
		return -1;
	}
	while(1)
	{
		asm("nop");
	}
}

static void DisplayTemp(marlin_temp temp)
{
	char buf[32] =
	{ 0 };
	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "Hotend:%.lf/%.lf", temp.nozzle_cur_temp,
			temp.nozzle_target_temp);
	LCD_Fill(10, 122, 240, 122 + 16, BLACK);
	LCD_Fill(10, 122 + 16, 240, 122 + 16 + 16, BLACK);
	LCD_ShowString(10, 122, buf, RED, BLACK, 16, 0);
	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "Hotbed:%.lf/%.lf", temp.hotbed_cur_temp,
			temp.hotbed_target_temp);
	LCD_ShowString(10, 122 + 16, buf, RED, BLACK, 16, 0);
}

static void DisplayAxis(marlin_coordinate axis)
{
	char buf[32] =
	{ 0 };
	memset(buf, 0, 32);
	snprintf(buf, sizeof(buf), "Axis:%.lf %.lf %.lf", axis.X, axis.Y, axis.Z);
	LCD_Fill(10, 122 + 16 + 16, 240, 122 + 16 + 16 + 16, BLACK);
	LCD_ShowString(10, 122 + 16 + 16, buf, RED, BLACK, 16, 0);
}
