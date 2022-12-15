#include "bsp_adc.h"

int shidu1;

/*函数名：初始化ADC */									   
void Adc_Init(void)
{    
	GPIO_InitTypeDef      GPIO_InitStructure;                             //定义一个设置GPIO的变量
	ADC_InitTypeDef       ADC_InitStructure;                              //定义一个设置ADC的变量
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	              //使能GPIOA通道时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE );	             		//使能ADC1通道时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                      //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       									 		 //准备设置PA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		                   		 //模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                 //设置PA5
    	
	ADC_DeInit(ADC2);                                                      //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	                   //ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	                         //模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	                   //模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	               //ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	                               //顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC2, &ADC_InitStructure);                                    //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
 
	ADC_Cmd(ADC2, ENABLE);	                                               //使能指定的ADC1	
	ADC_ResetCalibration(ADC2);	                                           //使能复位校准  	 
	while(ADC_GetResetCalibrationStatus(ADC2));                     	     //等待复位校准结束	
	ADC_StartCalibration(ADC2);	                                           //开启AD校准
	while(ADC_GetCalibrationStatus(ADC2));	                               //等待校准结束
}
 
/*-------------------------------------------------*/
/*函数名：获得ADC结果                              */
/*参  数：ch: 通道数                               */
/*-------------------------------------------------*/	
int Get_Adc(u8 ch)   
{	
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		                          //使能指定的ADC1的软件转换启动功能	
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));                     //等待转换结束
	return ADC_GetConversionValue(ADC2);	                              //返回最近一次ADC1规则组的转换结果
}



u16 Get_Adc_Average(u8 ch,u8 times)  //获取土壤湿度数据并返回给主函数
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


