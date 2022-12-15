#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "./sgp30/bsp_sgp30.h"


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	u32 CO2Data, TVOCData;  //定义CO2浓度变量与TVOC浓度变量
	u32 sgp30_dat;          //定义SGP30读取到的数据
	
	SysTick_Init();
  USART_Config();
	SGP30_Init();           //SGP30初始化
	
	SysTick_Delay_Ms(100);
	SGP30_Write(0x20,0x08);
	sgp30_dat = SGP30_Read();                  //读取SGP30的值
	CO2Data = (sgp30_dat & 0xffff0000) >> 16;  //获取CO2的值
	TVOCData = sgp30_dat & 0x0000ffff;         //获取TVOC的值
	while(CO2Data == 400 && TVOCData == 0)
	{
		SGP30_Write(0x20,0x08);
		sgp30_dat = SGP30_Read();                 //读取SGP30的值
		CO2Data = (sgp30_dat & 0xffff0000) >> 16; //获取CO2的值
		TVOCData = sgp30_dat & 0x0000ffff;		  //获取TVOC的值
		printf("正在检测中......");
		SysTick_Delay_Ms(500);
	}
	while(1)
	{
		SGP30_Write(0x20,0x08);
		sgp30_dat = SGP30_Read();                  //读取SGP30的值
		CO2Data = (sgp30_dat & 0xffff0000) >> 16;  //获取CO2的值
		TVOCData = sgp30_dat & 0x0000ffff;         //获取TVOC的值
		printf("CO2浓度为：%0.2d\r\nTVOC浓度为：%0.2d\r\n",CO2Data,TVOCData);
		SysTick_Delay_Ms(1000);
	}

}

