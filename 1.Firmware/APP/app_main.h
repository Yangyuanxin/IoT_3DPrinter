#ifndef __APP_MAIN_H
#define __APP_MAIN_H
#include "SystemConfig.h"

typedef struct ap_info
{
	char ssid[32] ;
	char bssid[32] ;
	char channel[10] ;
	char rssi[10] ;
}ap_info;

typedef struct GCodeCmdHandler_t
{
	uint8_t Type;
	char *GcodeCmd;
}GCodeCmdHandler_t;

//屏幕显示宽度、高度定义
#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   240

//物联网平台三元组
#define PRODUCT_ID              ""
#define DEVICE_NAME             ""
#define DEVICE_KEY              ""

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

enum MAPPING_CONTROL
{
	PRINTER_RESPONSE = 0, //回应
	PRINTER_PLA_PRE,   //PLA预热
	PRINTER_ABS_PRE,    //ABS预热
	PRINTER_TEMP_DROP,  //降温
	PRINTER_X_ADD_10,   //X轴移动+10mm
	PRINTER_X_SUB_10,   //X轴移动-10mm
	PRINTER_Y_ADD_10,   //Y轴移动+10mm
	PRINTER_Y_SUB_10,   //Y轴移动-10mm
	PRINTER_Z_ADD_10,   //Z轴移动+10mm
	PRINTER_Z_SUB_10,   //Z轴移动-10mm
	PRINTER_X_ZERO,     //X轴归零
	PRINTER_Y_ZERO,     //Y轴归零
	PRINTER_Z_ZERO,     //Z轴归零
	PRINTER_ALL_ZERO,   //全部归零
	PRINTER_LEVEING_GET,//调平数据获取
	PRINTER_PRINTING    //开始打印
};

#define DEBUG_GET_TEMP_LED(STATUS)	\
		do{	\
			GPIO_WriteBit(GPIOE, GPIO_Pin_2, !STATUS); \
		}while(0);

#define DEBUG_LED(STATUS) \
		do{ \
			{GPIO_WriteBit(GPIOE, GPIO_Pin_3, !STATUS); \
			GPIO_WriteBit(GPIOE, GPIO_Pin_4, !STATUS); \
			GPIO_WriteBit(GPIOE, GPIO_Pin_5, !STATUS);}\
		}while(0);

void MqttTask(void);

#endif //__APP_MAIN_H

