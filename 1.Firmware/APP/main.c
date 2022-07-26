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

marlin_temp temp;
marlin_coordinate axis;
__IO uint8_t MqttInitFlag = 0;
extern report_info report_printer_info;
extern report_leveling_data leveling_data;
static void DisplayPrinterInfo(enum MsgCmd_t Cmd);

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
void StartGCodeForWardTask(void *arg)
{
	(void) arg;
	k_err_t err;
	void *MsgRecv;
	for (;;)
	{
		err = tos_msg_q_pend(&GCodeMsg, &MsgRecv, TOS_TIME_FOREVER);
		if (K_ERR_NONE == err)
			GCodeForward(MsgRecv, GCode_Send);
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
	static uint8_t status = 0;
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
	for(int i = 0 ; i < 3 ; i++)
		tos_msg_q_post(&GCodeMsg, AUTO_GET_TEMP_MCODE);
	LCD_ShowPicture(0,190, 240, 50,gImage_icon_for_tencentos_tiny);
	for (;;)
	{
		if (0 == ring_buffer_read(&data, &Fifo))
		{
			if (data != '\n')
				GCodeReplyBuff.GCodeLineBuff[GCodeReplyBuff.GCodeLineCount++] =
						data;
			else
			{
				GCodeReplyBuff.GCodeLineBuff[GCodeReplyBuff.GCodeLineCount] ='\0';
				printf("reply:%s\n",GCodeReplyBuff.GCodeLineBuff);
				status = !status;
				DEBUG_GET_TEMP_LED(status);
				if ((GCodeReplyBuff.GCodeLineBuff[0] == ' '
						&& GCodeReplyBuff.GCodeLineBuff[1] == 'T')
						|| GCodeReplyBuff.GCodeLineBuff[3] == 'T')
				{
					Get_Temperature(GCodeReplyBuff.GCodeLineBuff, &temp);
					report_printer_info.hotbed_cur = temp.hotbed_cur_temp;
					report_printer_info.hotbed_target = temp.hotbed_target_temp;
					report_printer_info.hotend_cur = temp.nozzle_cur_temp;
					report_printer_info.hotend_target = temp.nozzle_target_temp;
					if (MqttInitFlag)
					{
						DisplayPrinterInfo(MSG_CMD_UPDATE_TEMP);
						tos_msg_q_post(&DataMsg, UPDATE_TEMP);
					}
				}
				else if (GCodeReplyBuff.GCodeLineBuff[0] == 'X'
						&& GCodeReplyBuff.GCodeLineBuff[1] == ':')
				{
					Get_Move_Coordinate(GCodeReplyBuff.GCodeLineBuff, &axis);
					report_printer_info.X = axis.X;
					report_printer_info.Y = axis.Y;
					report_printer_info.Z = axis.Z;
					if (MqttInitFlag)
					{
						DisplayPrinterInfo(MSG_CMD_UPDATE_AXIS);
						tos_msg_q_post(&DataMsg, UPDATE_AXIS);
					}
				}

				if (strstr(GCodeReplyBuff.GCodeLineBuff,
						"Bilinear Leveling Grid:"))
					parser_status = MSG_LEVEING;
				switch (parser_status)
				{
				case MSG_NORMAL:
					break;
				case MSG_LEVEING:
					if (parser_count < 6)
					{
						parser_count++;
						switch (parser_count)
						{
						case 3:
							memset(leveling_data.leveling_data1, 0, 30);
							memcpy(leveling_data.leveling_data1,
									GCodeReplyBuff.GCodeLineBuff + 2,
									strlen(GCodeReplyBuff.GCodeLineBuff) - 2);
							tos_msg_q_post(&DataMsg, UPDATE_LEVELING1);
							break;
						case 4:
							memset(leveling_data.leveling_data2, 0, 30);
							memcpy(leveling_data.leveling_data2,
									GCodeReplyBuff.GCodeLineBuff + 2,
									strlen(GCodeReplyBuff.GCodeLineBuff) - 2);
							tos_msg_q_post(&DataMsg, UPDATE_LEVELING2);
							break;
						case 5:
							memset(leveling_data.leveling_data3, 0, 30);
							memcpy(leveling_data.leveling_data3,
									GCodeReplyBuff.GCodeLineBuff + 2,
									strlen(GCodeReplyBuff.GCodeLineBuff) - 2);
							tos_msg_q_post(&DataMsg, UPDATE_LEVELING3);
							break;
						case 6:
							memset(leveling_data.leveling_data4, 0, 30);
							memcpy(leveling_data.leveling_data4,
									GCodeReplyBuff.GCodeLineBuff + 2,
									strlen(GCodeReplyBuff.GCodeLineBuff));
							tos_msg_q_post(&DataMsg, UPDATE_LEVELING4);
							break;
						}
						printf("%d->level_data:%s\n", parser_count,
								GCodeReplyBuff.GCodeLineBuff);
					}
					else
					{
						parser_count = 0;
						parser_status = MSG_NORMAL;
					}
					break;
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

static void DisplayPrinterInfo(enum MsgCmd_t Cmd)
{
	char buf[32] = { 0 };
	switch (Cmd)
	{
	case MSG_CMD_UPDATE_TEMP:
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "Hotend:%.lf/%.lf",
				report_printer_info.hotend_cur,
				report_printer_info.hotend_target);
		LCD_Fill(10, 122, 240, 122 + 16, BLACK);
		LCD_Fill(10, 122 + 16, 240, 122 + 16 + 16, BLACK);
		LCD_ShowString(10, 122, buf, RED, BLACK, 16, 0);
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "Hotbed:%.lf/%.lf",
				report_printer_info.hotbed_cur,
				report_printer_info.hotbed_target);
		LCD_ShowString(10, 122 + 16, buf, RED, BLACK, 16, 0);
		break;
	case MSG_CMD_UPDATE_AXIS:
		memset(buf, 0, 32);
		snprintf(buf, sizeof(buf), "Axis:%.lf %.lf %.lf", report_printer_info.X,
				report_printer_info.Y, report_printer_info.Z);
		LCD_Fill(10, 122 + 16 + 16, 240, 122 + 16 + 16 + 16, BLACK);
		LCD_ShowString(10, 122 + 16 + 16, buf, RED, BLACK, 16, 0);
		break;
	default:
		break;
	}
}

