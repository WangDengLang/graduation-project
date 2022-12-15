#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"
#include "./SysTick/bsp_SysTick.h"

//正点原子的adc采集代码
void Adc_Init(void);
int Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);
extern float temp_avrg;
extern int shidu;
 
#endif 


