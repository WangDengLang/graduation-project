/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
	
int main()
{
	uint8_t temp,humi;
	USART_Config();
	OLED_Init();	
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	SysTick_Delay_Ms(200);	
	printf("���ڲ���\r\n");
	OLED_ShowChinese(0,0,0,16,1);//��
	OLED_ShowChinese(16,0,1,16,1);//��
	OLED_ShowChinese(0,16,2,16,1);//ʪ
	OLED_ShowChinese(16,16,3,16,1);//��
	OLED_ShowChar(32,0,':',16,1);
	OLED_ShowChar(32,16,':',16,1);
	OLED_ShowChar(72,16,'%',16,1);//
	OLED_ShowChinese(65,0,4,16,1);//���
	OLED_ShowChar(72,0,'C',16,1);//
	while(DHT11_Init()) 
	{
		printf("���������ô���\n");
		SysTick_Delay_Ms(500);
	}		
	while(1)
	 {	 

			DHT11_Read_Data(&temp,&humi);//û��0.5s��ȡһ���¶�
			SysTick_Delay_Ms(500);
			OLED_ShowNum(48,0,temp,2,16,1);
			OLED_Refresh();
			OLED_ShowNum(48,16,humi,2,16,1);
			OLED_Refresh();
			OLED_Refresh();
	 }


}


