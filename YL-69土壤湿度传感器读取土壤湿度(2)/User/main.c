#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "./SysTick/bsp_SysTick.h"
#include "./gpio/bsp_gpio.h"

int shidu;
float temp_avrg=0;


int main(void) 
{
	
	SysTick_Init();         //延时功能初始化              
	USART_Config();      		//串口1功能初始化，波特率115200
	Gpio_Init();            // PA0,读取数字数据
	Adc_Init();             //ADC初始化
	
	while(1)                //主循环
	{		
    shidu=Get_Adc_Average(1,10);
    printf("土壤湿度：%d\r\n",shidu);  //将后面这个代码放到printf的相应的位置即可打印空气的温湿度数据了，直接剪切过去（当前温度：%d  当前湿度：%d    DHT11_Temp,DHT11_Hum,）
		SysTick_Delay_Ms(1000);
	}
}

