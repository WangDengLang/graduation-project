#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f10x.h"

#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //��ȡGPIOA��P0�ڵ�ƽ��0/1��
 
void Gpio_Init(void);         //��ʱ��ʼ������
int Gpio_read(void);        //��ȡA0��

#endif

