#include "./gpio/bsp_gpio.h"
#include "./SysTick/bsp_SysTick.h"
#include "bsp_usart.h"
 
void Gpio_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                     //����һ������GPIO�ı���
	
	
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);    //ʹ��GPIOA�˿�ʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                 //����PA0
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   		   //�������룬Ĭ��״̬�ǵ͵�ƽ
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   		   //�������룬Ĭ��״̬�Ǹߵ�ƽ 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
 GPIO_Init(GPIOA, &GPIO_InitStructure);            		 //����PA
	
}
 
int Gpio_read(void)
{
	if(gpio_readA == 1)
	{ 
		SysTick_Delay_Ms(100);
		return 1;
	}
	return 0;
}

