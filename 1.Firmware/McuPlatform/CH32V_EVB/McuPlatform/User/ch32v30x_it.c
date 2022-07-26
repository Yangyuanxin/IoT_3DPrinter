/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v30x_it.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main Interrupt Service Routines.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "ch32v30x_it.h"
#include "SystemConfig.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void UART7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
	while (1)
	{
	}
}

/*********************************************************************
 * @fn      USART2_IRQHandler
 *
 * @brief   This function handles USART2 global interrupt request.
 *
 * @return  none
 */
void USART2_IRQHandler(void)
{
	uint8_t data;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(USART2);
		tos_at_uart_input_byte(&esp8266_tf_agent, data);
	}

}

GCodeReplyBuff_t GCodeReplyBuff;
/*********************************************************************
 * @fn      UART7_IRQHandler
 *
 * @brief   This function handles UART7 global interrupt request.
 *
 * @return  none
 */
void UART7_IRQHandler(void)
{
	uint8_t data;
	osSchedLock();
	if (USART_GetITStatus(UART7, USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(UART7);
		ring_buffer_write(data,&Fifo);
	}
	osSchedUnLock();
}
