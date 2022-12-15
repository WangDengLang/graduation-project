#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "./SysTick/bsp_SysTick.h"
#include "./gpio/bsp_gpio.h"

int shidu;
float temp_avrg=0;


int main(void) 
{
	
	SysTick_Init();         //��ʱ���ܳ�ʼ��              
	USART_Config();      		//����1���ܳ�ʼ����������115200
	Gpio_Init();            // PA0,��ȡ��������
	Adc_Init();             //ADC��ʼ��
	
	while(1)                //��ѭ��
	{		
    shidu=Get_Adc_Average(1,10);
    printf("����ʪ�ȣ�%d\r\n",shidu);  //�������������ŵ�printf����Ӧ��λ�ü��ɴ�ӡ��������ʪ�������ˣ�ֱ�Ӽ��й�ȥ����ǰ�¶ȣ�%d  ��ǰʪ�ȣ�%d    DHT11_Temp,DHT11_Hum,��
		SysTick_Delay_Ms(1000);
	}
}

