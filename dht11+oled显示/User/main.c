/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "sys.h"
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./delay/bsp_SysTick.h"
#include "./dht11/bsp_dht11.h"
#include "oled.h"
#include "bmp.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
	
int main()
{
	uint8_t temp,humi;
	USART_Config();
	OLED_Init();	
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	SysTick_Delay_Ms(200);	
	printf("串口测试\r\n");
	OLED_ShowChinese(0,0,0,16,1);//温
	OLED_ShowChinese(16,0,1,16,1);//度
	OLED_ShowChinese(0,16,2,16,1);//湿
	OLED_ShowChinese(16,16,3,16,1);//度
	OLED_ShowChar(32,0,':',16,1);
	OLED_ShowChar(32,16,':',16,1);
	OLED_ShowChar(72,16,'%',16,1);//
	OLED_ShowChinese(65,0,4,16,1);//°度
	OLED_ShowChar(72,0,'C',16,1);//
	while(DHT11_Init()) 
	{
		printf("传感器设置错误\n");
		SysTick_Delay_Ms(500);
	}		
	while(1)
	 {	 

			DHT11_Read_Data(&temp,&humi);//没隔0.5s读取一次温度
			SysTick_Delay_Ms(500);
			OLED_ShowNum(48,0,temp,2,16,1);
			OLED_Refresh();
			OLED_ShowNum(48,16,humi,2,16,1);
			OLED_Refresh();
			OLED_Refresh();
	 }


}


