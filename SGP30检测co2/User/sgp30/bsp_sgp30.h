#ifndef __BSP_SGP30_H
#define __BSP_SGP30_H

#include "stm32f10x.h"
#include "bsp_SysTick.h"


#define SGP30_SCL_Clr() GPIO_ResetBits(GPIOE,GPIO_Pin_7)//SCL
#define SGP30_SCL_Set() GPIO_SetBits(GPIOE,GPIO_Pin_7)

#define SGP30_SDA_Set() GPIO_SetBits(GPIOE,GPIO_Pin_8)
#define SGP30_SDA_Clr() GPIO_ResetBits(GPIOE,GPIO_Pin_8)



// GPIO 引脚宏定义
#define  SGP30_SCL_GPIO_CLK        RCC_APB2Periph_GPIOE
#define  SGP30_SCL_GPIO_PORT       GPIOE
#define  SGP30_SCL_GPIO_PIN        GPIO_Pin_7

#define  SGP30_SDA_GPIO_SDA        RCC_APB2Periph_GPIOE
#define  SGP30_SDA_GPIO_PORT       GPIOE
#define  SGP30_SDA_GPIO_PIN        GPIO_Pin_8

#define  SGP30_SDA_READ()           GPIO_ReadInputDataBit(SGP30_SDA_GPIO_PORT, SGP30_SDA_GPIO_PIN)

#define SGP30_read  0xb1  //SGP30的读地址
#define SGP30_write 0xb0  //SGP30的写地址


void SGP30_IIC_Start(void);				
void SGP30_IIC_Stop(void);	  		
void SGP30_IIC_Send_Byte(u8 txd);	
u16 SGP30_IIC_Read_Byte(unsigned char ack); 
u8 SGP30_IIC_Wait_Ack(void); 			
void SGP30_IIC_Ack(void);				
void SGP30_IIC_NAck(void);				
void SGP30_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 SGP30_IIC_Read_One_Byte(u8 daddr,u8 addr);	
void SGP30_Init(void);				  
void SGP30_Write(u8 a, u8 b);
u32 SGP30_Read(void);

#endif
