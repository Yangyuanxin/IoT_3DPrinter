#include "app_main.h"

ap_info esp8266_info;
report_info report_printer_info;
report_leveling_data leveling_data;

char payload[256] = { 0 };
char client_token_cache[128] = { 0 };
static char report_topic_name[TOPIC_NAME_MAX_SIZE] = { 0 };
static char report_reply_topic_name[TOPIC_NAME_MAX_SIZE] = { 0 };

static void MqttToPrinter(uint8_t cmd);
static void WifiSmartConfig(void);
static void ReportDeviceInfo(enum MsgCmd_t Cmd);
static void ReportLevelingData(enum MsgCmd_t Cmd);

GCodeCmdHandler_t GCodeCmd[] = {
{ PRINTER_RESPONSE, NULL }, 					/*指令回应*/
{ PRINTER_PLA_PRE, GCODE_PLA_PRE }, 			/*PLA预热*/
{ PRINTER_ABS_PRE, GCODE_ABS_PRE }, 			/*ABS预热*/
{ PRINTER_TEMP_DROP, GCODE_TEMP_DROP }, 		/*降温*/
{ PRINTER_X_ADD_10, GCODE_X_MOVE_ADD }, 		/*X轴移动+10mm*/
{ PRINTER_X_SUB_10, GCODE_X_MOVE_SUB }, 		/*X轴移动-10mm*/
{ PRINTER_Y_ADD_10, GCODE_Y_MOVE_ADD }, 		/*Y轴移动+10mm*/
{ PRINTER_Y_SUB_10, GCODE_Y_MOVE_SUB }, 		/*Y轴移动-10mm*/
{ PRINTER_Z_ADD_10, GCODE_Z_MOVE_ADD }, 		/*Z轴移动+10mm*/
{ PRINTER_Z_SUB_10, GCODE_Z_MOVE_SUB }, 		/*Z轴移动-10mm*/
{ PRINTER_X_ZERO, GCODE_ZERO_OF_X }, 			/*X轴归零*/
{ PRINTER_Y_ZERO, GCODE_ZERO_OF_Y }, 			/*Y轴归零*/
{ PRINTER_Z_ZERO, GCODE_ZERO_OF_Z }, 			/*Z轴归零*/
{ PRINTER_ALL_ZERO, GCODE_ZERO_OF_ALL }, 		/*全部归零*/
{ PRINTER_LEVEING_GET, GCODE_LEVELING_DATA }, 	/*获取调平数据*/
{ PRINTER_PRINTING, GCODE_START_PRINT } 		/*开始打印*/
};

void MessageParamsHandler(mqtt_message_t* msg)
{
	cJSON *root = NULL;
	cJSON *token = NULL;
	cJSON *params = NULL;
	cJSON *method = NULL;
	cJSON *led_control = NULL;
	cJSON *printer_control = NULL;
	cJSON *printer_fan_speed = NULL;
	char GCodeBuf[15] = { 0 };
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
		MqttToPrinter(printer_control->valueint);
	}

	printer_fan_speed = cJSON_GetObjectItem(params, "fan_speed");
	if (printer_fan_speed)
	{
		memset(GCodeBuf, 0, 15);
		result_fan_speed = (double) printer_fan_speed->valueint / 255 * 2.55
				* 100 * 2.55;
		snprintf(GCodeBuf, sizeof(GCodeBuf), GCODE_FAN_SETTING,
				(int) result_fan_speed);
		tos_msg_q_post(&GCodeMsg, GCodeBuf);
	}
	/*7. 设置clientToken回复*/
	token = cJSON_GetObjectItem(root, "clientToken");
	if (token)
		tos_msg_q_post(&DataMsg, UPDATE_TOKEN);
	cJSON_Delete(root);
	root = NULL;
}

void MqttTask(void)
{
	int ret = 0;
	int size = 0;
	k_err_t err;
	uint8_t MsgCmd;
	void *MsgRecv;
	mqtt_state_t state;
	char *key = DEVICE_KEY;
	device_info_t dev_info;
	char *product_id = PRODUCT_ID;
	char *device_name = DEVICE_NAME;
	memset(&dev_info, 0, sizeof(device_info_t));
	LCD_ShowString(10, 10, "Wait Connecting...", WHITE, BLACK, 16, 0);
	ret = esp8266_tencent_firmware_sal_init(HAL_UART_PORT_2);
	if (ret < 0)
	{
		printf("esp8266 tencent firmware sal init fail, ret is %d\r\n", ret);
		NVIC_SystemReset();
	}
	tos_task_delay(6000);
	/*执行WIFI配网逻辑*/
	WifiSmartConfig();
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


	/* 开始订阅topic */
	size = snprintf(report_reply_topic_name, TOPIC_NAME_MAX_SIZE,
			"$thing/down/property/%s/%s", product_id, device_name);
	if (size < 0 || size > sizeof(report_reply_topic_name) - 1)
	{
		printf(
				"sub topic content length not enough! content size:%d  buf size:%d",
				size, (int) sizeof(report_reply_topic_name));
		return;
	}
	if (tos_tf_module_mqtt_sub(report_reply_topic_name, QOS0,
			MessageParamsHandler) != 0)
	{
		printf("module mqtt sub fail\n");
		NVIC_SystemReset();
	}

	memset(report_topic_name, 0, sizeof(report_topic_name));
	size = snprintf(report_topic_name, TOPIC_NAME_MAX_SIZE,
			"$thing/up/property/%s/%s", product_id, device_name);
	if (size < 0 || size > sizeof(report_topic_name) - 1)
	{
		printf(
				"pub topic content length not enough! content size:%d  buf size:%d",
				size, (int) sizeof(report_topic_name));
	}

	LCD_ShowString(10, 10, "MQTT Connect OK", WHITE, BLACK, 16, 0);
	MqttInitFlag = 1;
	while (1)
	{
		err = tos_msg_q_pend(&DataMsg, &MsgRecv, TOS_TIME_FOREVER);
		if(K_ERR_NONE == err)
		{
			if(strstr(MsgRecv,UPDATE_TEMP))
			MsgCmd = MSG_CMD_UPDATE_TEMP;
			else if(strstr(MsgRecv,UPDATE_AXIS))
			MsgCmd = MSG_CMD_UPDATE_AXIS;
			else if(strstr(MsgRecv,UPDATE_TOKEN))
			MsgCmd = MSG_CMD_UPDATE_TOKEN;
			else if(strstr(MsgRecv,UPDATE_LEVELING1))
			MsgCmd = MSG_CMD_LEVELING_1;
			else if(strstr(MsgRecv,UPDATE_LEVELING2))
			MsgCmd = MSG_CMD_LEVELING_2;
			else if(strstr(MsgRecv,UPDATE_LEVELING3))
			MsgCmd = MSG_CMD_LEVELING_3;
			else if(strstr(MsgRecv,UPDATE_LEVELING4))
			MsgCmd = MSG_CMD_LEVELING_4;
			else
			MsgCmd = 99;

			switch(MsgCmd)
			{
				case MSG_CMD_UPDATE_TEMP:
				ReportDeviceInfo(MSG_CMD_UPDATE_TEMP);
				break;
				case MSG_CMD_UPDATE_AXIS:
				ReportDeviceInfo(MSG_CMD_UPDATE_AXIS);
				break;
				case MSG_CMD_UPDATE_TOKEN:
				ReportDeviceInfo(MSG_CMD_UPDATE_TOKEN);
				break;
				case MSG_CMD_LEVELING_1:
				ReportLevelingData(MSG_CMD_LEVELING_1);
				break;
				case MSG_CMD_LEVELING_2:
				ReportLevelingData(MSG_CMD_LEVELING_2);
				break;
				case MSG_CMD_LEVELING_3:
				ReportLevelingData(MSG_CMD_LEVELING_3);
				break;
				case MSG_CMD_LEVELING_4:
				ReportLevelingData(MSG_CMD_LEVELING_4);
				break;
				default:
				break;
			}
		}
		osDelay(5);
	}
}

static void MqttToPrinter(uint8_t cmd)
{
	if (cmd == GCodeCmd[cmd].Index)
		tos_msg_q_post(&GCodeMsg, GCodeCmd[cmd].GcodeCmd);
}

static void ReportLevelingData(enum MsgCmd_t Cmd)
{
	char buf[50] = { 0 };
	static uint8_t flag = 0;
	if (0 == flag)
	{
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%s", "Get Leveling data...");
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA_STATUS_TEMPLATE,
				buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%s", "N/A");
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA1_TEMPLATE, buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%s", "N/A");
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA2_TEMPLATE, buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%s", "N/A");
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA3_TEMPLATE, buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%s", "N/A");
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA4_TEMPLATE, buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		flag = 1;
	}
	memset(buf, 0, sizeof(buf));
	memset(payload, 0, sizeof(payload));
	switch (Cmd)
	{
	case MSG_CMD_LEVELING_1:
		snprintf(buf, sizeof(buf), "%s", leveling_data.leveling_data1);
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA1_TEMPLATE, buf);
		break;
	case MSG_CMD_LEVELING_2:
		snprintf(buf, sizeof(buf), "%s", leveling_data.leveling_data2);
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA2_TEMPLATE, buf);
		break;
	case MSG_CMD_LEVELING_3:
		snprintf(buf, sizeof(buf), "%s", leveling_data.leveling_data3);
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA3_TEMPLATE, buf);
		break;
	case MSG_CMD_LEVELING_4:
		snprintf(buf, sizeof(buf), "%s", leveling_data.leveling_data4);
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA4_TEMPLATE, buf);
		flag = 0;
		break;
	default:
		break;
	}

	if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
		NVIC_SystemReset();

	if (MSG_CMD_LEVELING_4 == Cmd)
	{
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%s", "Get Data Success!");
		snprintf(payload, sizeof(payload), REPORT_LEVELING_DATA_STATUS_TEMPLATE,
				buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
	}
}

static void ReportDeviceInfo(enum MsgCmd_t Cmd)
{
	char buf[50] = { 0 };
	int nozzle_temp = 0 ;
	static uint32_t counter = 0;
	static uint8_t report_alarm = 0;
	switch (Cmd)
	{
	case MSG_CMD_UPDATE_TEMP:
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%.2lf/%.2lf",
				report_printer_info.hotend_cur,
				report_printer_info.hotend_target);
		snprintf(payload, sizeof(payload), REPORT_NOZZLE_TEMP_DATA_TEMPLATE,
				buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "%.2lf/%.2lf",
				report_printer_info.hotbed_cur,
				report_printer_info.hotbed_target);
		snprintf(payload, sizeof(payload), REPORT_HOTBED_TEMP_DATA_TEMPLATE,
				buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();

		//温度告警上报
		memset(payload, 0, sizeof(payload));
		nozzle_temp = (int)report_printer_info.hotend_cur ;
		if(nozzle_temp > 120)
		{
			if(0 == report_alarm)
			{
				report_alarm = 1;
				memset(buf, 0, sizeof(buf));
				snprintf(buf, sizeof(buf), "%d",nozzle_temp);
				snprintf(payload, sizeof(payload), REPORT_NOZZLE_TEMP_ALARM_DATA_TEMPLATE,buf);
				if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
					NVIC_SystemReset();
			}
		}
		if(nozzle_temp < 120)
			nozzle_temp = 0;
		break;
	case MSG_CMD_UPDATE_AXIS:
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		snprintf(buf, sizeof(buf), "X:%.1f Y:%.1f Z:%.1f",
				report_printer_info.X, report_printer_info.Y,
				report_printer_info.Z);
		printf("axis:%s\n",buf);
		snprintf(payload, sizeof(payload), REPORT_POS_DATA_TEMPLATE, buf);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		break;
	case MSG_CMD_UPDATE_TOKEN:
		memset(buf, 0, sizeof(buf));
		memset(payload, 0, sizeof(payload));
		memset(client_token_cache,0,sizeof(client_token_cache));
		snprintf(client_token_cache,sizeof(client_token_cache),"%d",counter++);
		snprintf(payload, sizeof(payload), CONTROL_REPLY_DATA_TEMPLATE,
				client_token_cache);
		if (tos_tf_module_mqtt_pub(report_topic_name, QOS0, payload) != 0)
			NVIC_SystemReset();
		break;
	default:
		break;
	}
}

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
		GPIO_WriteBit(GPIOE, GPIO_Pin_5, 0); //亮灯
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
	GPIO_WriteBit(GPIOE, GPIO_Pin_5, 1); //灭灯
	snprintf(esp8266_info.ssid, sizeof(esp8266_info.ssid), "ssid:%s", ssid);
	snprintf(esp8266_info.bssid, sizeof(esp8266_info.bssid), "bssid:%s", bssid);
	snprintf(esp8266_info.channel, sizeof(esp8266_info.channel), "channel:%d",
			channel);
	snprintf(esp8266_info.rssi, sizeof(esp8266_info.rssi), "rssi:%d", rssi);
	LCD_ShowString(10, 10, "Wifi Connect OK", WHITE, BLACK, 16, 0);
	LCD_ShowString(10, 26, esp8266_info.ssid, WHITE, BLACK, 16, 0);
	LCD_ShowString(10, 26 + 16, esp8266_info.bssid, WHITE, BLACK, 16, 0);
	LCD_ShowString(10, 26 + 16 + 16, esp8266_info.channel, WHITE, BLACK, 16, 0);
	LCD_ShowString(10, 26 + 16 + 16 + 16, esp8266_info.rssi, WHITE, BLACK, 16,
			0);
	LCD_ShowPicture(0,190, 240, 50,gImage_icon_for_tencentos_tiny);
}
