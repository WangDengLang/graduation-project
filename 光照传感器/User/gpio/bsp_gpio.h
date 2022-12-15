#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f10x.h"

#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //读取GPIOA的P0口电平（0/1）
 
void Gpio_Init(void);         //延时初始化函数
int Gpio_read(void);        //读取A0口

#endif

