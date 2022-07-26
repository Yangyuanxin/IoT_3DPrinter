/********************************** (C) COPYRIGHT  *******************************
 * File Name          : debug.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file contains all the functions prototypes for UART
 *                      Printf , Delay functions.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "delay.h"
#include <stddef.h>

static uint8_t p_us = 0;
static uint16_t p_ms = 0;

/*********************************************************************
 * @fn      Delay_Init
 *
 * @brief   Initializes Delay Funcation.
 *
 * @return  none
 */
void Delay_Init(void)
{
	p_us = SystemCoreClock / 8000000;
	p_ms = (uint16_t) p_us * 1000;
}

/*********************************************************************
 * @fn      Delay_Us
 *
 * @brief   Microsecond Delay Time.
 *
 * @param   n - Microsecond number.
 *
 * @return  None
 */
void Delay_Us(uint32_t n)
{
	uint32_t i;

	SysTick->SR &= ~(1 << 0);
	i = (uint32_t) n * p_us;

	SysTick->CMP = i;
	SysTick->CTLR |= (1 << 4) | (1 << 5) | (1 << 0);

	while((SysTick->SR & (1 << 0)) != (1 << 0))
	;
	SysTick->CTLR &= ~(1 << 0);
}

/*********************************************************************
 * @fn      Delay_Ms
 *
 * @brief   Millisecond Delay Time.
 *
 * @param   n - Millisecond number.
 *
 * @return  None
 */
void Delay_Ms(uint32_t n)
{
	uint32_t i;

	SysTick->SR &= ~(1 << 0);
	i = (uint32_t) n * p_ms;

	SysTick->CMP = i;
	SysTick->CTLR |= (1 << 4) | (1 << 5) | (1 << 0);

	while((SysTick->SR & (1 << 0)) != (1 << 0))
	;
	SysTick->CTLR &= ~(1 << 0);
}

/*********************************************************************
 * @fn      _sbrk
 *
 * @brief   Change the spatial position of data segment.
 *
 * @return  size: Data length
 */
void *_sbrk(ptrdiff_t incr)
{
	extern char _end[];
	extern char _heap_end[];
	static char *curbrk = _end;

	if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
		return NULL - 1;

	curbrk += incr;
	return curbrk - incr;
}

