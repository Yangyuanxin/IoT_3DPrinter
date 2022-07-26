/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v30x_it.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file contains the headers of the interrupt handlers.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CH32V30x_IT_H
#define __CH32V30x_IT_H

#include "delay.h"

#define REPLY_MAX_LEN 1024
typedef struct GCodeReplyBuff_t
{
	int  GCodeLineCount;
	char GCodeLineBuff[REPLY_MAX_LEN];
}GCodeReplyBuff_t;

#endif /* __CH32V30x_IT_H */

