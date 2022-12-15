#include "bsp_adc.h"

int shidu1;

/*����������ʼ��ADC */									   
void Adc_Init(void)
{    
	GPIO_InitTypeDef      GPIO_InitStructure;                             //����һ������GPIO�ı���
	ADC_InitTypeDef       ADC_InitStructure;                              //����һ������ADC�ı���
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	              //ʹ��GPIOAͨ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE );	             		//ʹ��ADC1ͨ��ʱ��
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                      //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       									 		 //׼������PA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		                   		 //ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                 //����PA5
    	
	ADC_DeInit(ADC2);                                                      //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	                   //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	                         //ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	                   //ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	               //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	                               //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC2, &ADC_InitStructure);                                    //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
 
	ADC_Cmd(ADC2, ENABLE);	                                               //ʹ��ָ����ADC1	
	ADC_ResetCalibration(ADC2);	                                           //ʹ�ܸ�λУ׼  	 
	while(ADC_GetResetCalibrationStatus(ADC2));                     	     //�ȴ���λУ׼����	
	ADC_StartCalibration(ADC2);	                                           //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC2));	                               //�ȴ�У׼����
}
 
/*-------------------------------------------------*/
/*�����������ADC���                              */
/*��  ����ch: ͨ����                               */
/*-------------------------------------------------*/	
int Get_Adc(u8 ch)   
{	
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		                          //ʹ��ָ����ADC1�����ת����������	
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));                     //�ȴ�ת������
	return ADC_GetConversionValue(ADC2);	                              //�������һ��ADC1�������ת�����
}



u16 Get_Adc_Average(u8 ch,u8 times)  //��ȡ����ʪ�����ݲ����ظ�������
{
	uint32_t temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		SysTick_Delay_Ms(1);
	}
	temp_avrg=temp_val/times;
	if(temp_avrg>4000)
	{
		return 0;
	}
	shidu1=100-(temp_avrg/40);
	return shidu1;
}


