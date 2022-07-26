#include "led.h"

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
			| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOE, GPIO_Pin_2, 1);
	GPIO_WriteBit(GPIOE, GPIO_Pin_3, 1);
	GPIO_WriteBit(GPIOE, GPIO_Pin_4, 1);
	GPIO_WriteBit(GPIOE, GPIO_Pin_5, 1);
}
