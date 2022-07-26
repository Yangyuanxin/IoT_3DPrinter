#include "Key.h"

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_Scan(void)
{
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
		return 3 ;
	else if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == Bit_RESET)
		return 2 ;
	else if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == Bit_RESET)
		return 1 ;
	return 0 ;
}
