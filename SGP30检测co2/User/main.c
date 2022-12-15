#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "./sgp30/bsp_sgp30.h"


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	u32 CO2Data, TVOCData;  //����CO2Ũ�ȱ�����TVOCŨ�ȱ���
	u32 sgp30_dat;          //����SGP30��ȡ��������
	
	SysTick_Init();
  USART_Config();
	SGP30_Init();           //SGP30��ʼ��
	
	SysTick_Delay_Ms(100);
	SGP30_Write(0x20,0x08);
	sgp30_dat = SGP30_Read();                  //��ȡSGP30��ֵ
	CO2Data = (sgp30_dat & 0xffff0000) >> 16;  //��ȡCO2��ֵ
	TVOCData = sgp30_dat & 0x0000ffff;         //��ȡTVOC��ֵ
	while(CO2Data == 400 && TVOCData == 0)
	{
		SGP30_Write(0x20,0x08);
		sgp30_dat = SGP30_Read();                 //��ȡSGP30��ֵ
		CO2Data = (sgp30_dat & 0xffff0000) >> 16; //��ȡCO2��ֵ
		TVOCData = sgp30_dat & 0x0000ffff;		  //��ȡTVOC��ֵ
		printf("���ڼ����......");
		SysTick_Delay_Ms(500);
	}
	while(1)
	{
		SGP30_Write(0x20,0x08);
		sgp30_dat = SGP30_Read();                  //��ȡSGP30��ֵ
		CO2Data = (sgp30_dat & 0xffff0000) >> 16;  //��ȡCO2��ֵ
		TVOCData = sgp30_dat & 0x0000ffff;         //��ȡTVOC��ֵ
		printf("CO2Ũ��Ϊ��%0.2d\r\nTVOCŨ��Ϊ��%0.2d\r\n",CO2Data,TVOCData);
		SysTick_Delay_Ms(1000);
	}

}

