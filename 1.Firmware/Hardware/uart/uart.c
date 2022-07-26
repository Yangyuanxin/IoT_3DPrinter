#include "uart.h"
#include "tos_k.h"
#include "cmsis_os.h"
/*********************************************************************
 * @fn      _write
 *
 * @brief   Support Printf Function
 *
 * @param   *buf - UART send Data.
 *          size - Data length
 *
 * @return  size: Data length
 */
__attribute__((used)) int _write(int fd, char *buf, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
#if(DEBUG == DEBUG_UART1)
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1, *buf++);
#elif(DEBUG == DEBUG_UART2)
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2, *buf++);
#elif(DEBUG == DEBUG_UART3)
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
		USART_SendData(USART3, *buf++);
#endif
	}

	return size;
}

void usart2_init(int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* USART2 TX-->A.2   RX-->A.3 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2, ENABLE);
}

void uart6_init(int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* UART6 TX-->C.0   RX-->C.1 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(UART6, &USART_InitStructure);
	USART_ITConfig(UART6, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = UART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(UART6, ENABLE);
}

void uart7_init(int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* UART7 TX-->C.2   RX-->C.3 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(UART7, &USART_InitStructure);
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(UART7, ENABLE);
}

/*********************************************************************
 * @fn      USART_Printf_Init
 *
 * @brief   Initializes the USARTx peripheral.
 *
 * @param   baudrate - USART communication baud rate.
 *
 * @return  None
 */
void USART_Printf_Init(int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

#if(DEBUG == DEBUG_UART1)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,
			ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

#elif(DEBUG == DEBUG_UART2)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

#elif(DEBUG == DEBUG_UART3)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

#endif

	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;

#if(DEBUG == DEBUG_UART1)
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

#elif(DEBUG == DEBUG_UART2)
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);

#elif(DEBUG == DEBUG_UART3)
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);

#endif
}

void printer_uart_init(int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* UART7 TX-->C.2   RX-->C.3 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(UART7, &USART_InitStructure);
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_Cmd(UART7, ENABLE);
}

void GCode_Send(char *str)
{
	osSchedLock();
	//发之前关闭接收中断
	USART_ITConfig(UART7, USART_IT_RXNE, DISABLE);
	while(*str != '\0')
	{
		USART_SendData(UART7, *str++);
		while(USART_GetFlagStatus(UART7, USART_FLAG_TC) == RESET);
	}
	/*清除发送标志位*/
	USART_ClearFlag(UART7,USART_FLAG_TC);
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);
	//发完开启接收中断
	osSchedUnLock();
}
