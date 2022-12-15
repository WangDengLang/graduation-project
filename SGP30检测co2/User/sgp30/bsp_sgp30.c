#include "./sgp30/bsp_sgp30.h"

void SGP30_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(SGP30_SCL_GPIO_CLK | SGP30_SDA_GPIO_SDA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = SGP30_SCL_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SGP30_SCL_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = SGP30_SDA_GPIO_PIN;
  GPIO_Init(SGP30_SDA_GPIO_PORT, &GPIO_InitStructure);
}

void SDA_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = SGP30_SDA_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SGP30_SDA_GPIO_PORT, &GPIO_InitStructure);
}

void SDA_IN(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = SGP30_SDA_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(SGP30_SDA_GPIO_PORT, &GPIO_InitStructure);
}

void SGP30_IIC_Start(void)
{
  SDA_OUT();
  SGP30_SDA_Set();
  SGP30_SCL_Set();
  SysTick_Delay_Us(20);
  SGP30_SDA_Clr();
  SysTick_Delay_Us(20);
  SGP30_SCL_Clr();
}

void SGP30_IIC_Stop(void)
{
  SDA_OUT();
  SGP30_SCL_Clr();
  SGP30_SDA_Clr();	
  SysTick_Delay_Us(20);
  SGP30_SCL_Set();
  SGP30_SDA_Set();
  SysTick_Delay_Us(20);
}

u8 SGP30_IIC_Wait_Ack(void)
{
  u8 ucErrTime = 0;
  SDA_IN();
  SGP30_SDA_Set();
  SysTick_Delay_Us(10);
  SGP30_SCL_Set();
  SysTick_Delay_Us(10);
  while(SGP30_SDA_READ())
  {
    ucErrTime++;
    if(ucErrTime > 250)
    {
      SGP30_IIC_Stop();
      return 1;
    }
  }
  SGP30_SCL_Clr();
  return 0;
}

void SGP30_IIC_Ack(void)
{
  SGP30_SCL_Clr();
  SDA_OUT();
  SGP30_SDA_Clr();
  SysTick_Delay_Us(20);
  SGP30_SCL_Set();
  SysTick_Delay_Us(20);
  SGP30_SCL_Clr();
}

void SGP30_IIC_NAck(void)
{
  SGP30_SCL_Clr();
  SDA_OUT();
  SGP30_SDA_Set();
  SysTick_Delay_Us(20);
  SGP30_SCL_Set();
  SysTick_Delay_Us(20);
  SGP30_SCL_Clr();
}

void SGP30_IIC_Send_Byte(u8 txd)
{
  u8 t;
  SDA_OUT();
  SGP30_SCL_Clr();
  for(t = 0; t < 8; t++)
  {
    if((txd & 0x80) >> 7)
      SGP30_SDA_Set();
    else
      SGP30_SDA_Clr();
    txd <<= 1;
    SysTick_Delay_Us(20);
    SGP30_SCL_Set();
    SysTick_Delay_Us(20);
    SGP30_SCL_Clr();
    SysTick_Delay_Us(20);
  }
  SysTick_Delay_Us(20);

}

u16 SGP30_IIC_Read_Byte(u8 ack)
{
  u8 i;
  u16 receive = 0;
  SDA_IN();
  for(i = 0; i < 8; i++ )
  {
    SGP30_SCL_Clr();
    SysTick_Delay_Us(20);
    SGP30_SCL_Set();
    receive <<= 1;
    if(SGP30_SDA_READ())
      receive++;
    SysTick_Delay_Us(20);
  }
  if (!ack)
    SGP30_IIC_NAck();
  else
    SGP30_IIC_Ack();
  return receive;
}

void SGP30_Init(void)
{
  SGP30_GPIO_Init();
  SGP30_Write(0x20, 0x03);
//	SGP30_ad_write(0x20,0x61);
//	SGP30_ad_write(0x01,0x00);
}


void SGP30_Write(u8 a, u8 b)
{
  SGP30_IIC_Start();
  SGP30_IIC_Send_Byte(SGP30_write); 
  SGP30_IIC_Wait_Ack();
  SGP30_IIC_Send_Byte(a);	
  SGP30_IIC_Wait_Ack();
  SGP30_IIC_Send_Byte(b);
  SGP30_IIC_Wait_Ack();
  SGP30_IIC_Stop();
  SysTick_Delay_Ms(100);
}

u32 SGP30_Read(void)
{
  u32 dat;
  u8 crc;
  SGP30_IIC_Start();
  SGP30_IIC_Send_Byte(SGP30_read); 
  SGP30_IIC_Wait_Ack();
  dat = SGP30_IIC_Read_Byte(1);
  dat <<= 8;
  dat += SGP30_IIC_Read_Byte(1);
  crc = SGP30_IIC_Read_Byte(1); 
  crc = crc;
  dat <<= 8;
  dat += SGP30_IIC_Read_Byte(1);
  dat <<= 8;
  dat += SGP30_IIC_Read_Byte(0);
  SGP30_IIC_Stop();
  return(dat);
}

