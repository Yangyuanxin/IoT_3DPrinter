#ifndef __UART_H
#define __UART_H
#include <stdio.h>
#include "ch32v30x.h"

/* UART Printf Definition */
#define DEBUG_UART1    1
#define DEBUG_UART2    2
#define DEBUG_UART3    3

/* DEBUG UATR Definition */
#define DEBUG   DEBUG_UART1
//#define DEBUG   DEBUG_UART2
//#define DEBUG   DEBUG_UART3

void GCode_Send(char *str);
void printer_uart_init(int baud);
void USART_Printf_Init(int baud);

void usart2_init(int baud);
void uart6_init(int baud);
void uart7_init(int baud);

#endif

