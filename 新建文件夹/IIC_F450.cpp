#include "IIC_F450.hpp"
#include "main.h"

/**************************************************************************
函数功能：IIC引脚初始化
入口参数：无
返回  值：无
**************************************************************************/
void IIC_Init(void)
{
	//MPU9250: B8-->IIC0_SCL,B9-->IIC0_SDA
	rcu_periph_clock_enable(RCU_GPIOB);
	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_8|GPIO_PIN_9);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8|GPIO_PIN_9);
	gpio_bit_write(GPIOB,GPIO_PIN_8|GPIO_PIN_9,SET);
}

/*******************************************************************************
* Function Name  : IIC_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_delay(void)
{
   uint8_t i=30; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   }  
}

void delay5ms(void)
{
		
   int i=5000;  
   while(i) 
   { 
     i--; 
   }  
}
/*******************************************************************************
* Function Name  : IIC_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
void IIC_Start(void)
{
	SDA_H;
	SCL_H;
	IIC_delay();
	SDA_L;
	IIC_delay();
	SDA_L;
}
/*******************************************************************************
* Function Name  : IIC_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_Stop(void)
{
	SCL_L;
	SDA_L;
	IIC_delay();
	SCL_H;
	SDA_H;
	IIC_delay();
} 
/*******************************************************************************
* Function Name  : IIC_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_Ack(void)
{	
	SCL_L;
	SDA_L;
	IIC_delay();
	SCL_H;
	IIC_delay();
	SCL_L;
}   
/*******************************************************************************
* Function Name  : IIC_NAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_NAck(void)
{	
	SCL_L;
	SDA_H;
	IIC_delay();
	SCL_H;
	IIC_delay();
	SCL_L;
} 
/*******************************************************************************
* Function Name  : IIC_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
bool IIC_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	uint8_t ucErrTime=0;
	  
	SDA_H;		
	IIC_delay();
	SCL_H;
	IIC_delay(); 
	while(SDA_read)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL_L;//时钟输出0 	   
	return 0;  
	
//	SCL_L;
//	IIC_delay();
//	SDA_H;			
//	IIC_delay();
//	SCL_H;
//	IIC_delay();
//	if(SDA_read)
//	{
//      SCL_L;
//	  IIC_delay();
//      return 0;
//	}
//	SCL_L;
//	IIC_delay();
//	return 1;
}
/*******************************************************************************
* Function Name  : IIC_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_SendByte(uint8_t SendByte) //数据从高位到低位//
{
    uint8_t i=8;
    while(i--)
    {
        SCL_L;
        IIC_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        IIC_delay();
				SCL_H;
        IIC_delay();
    }
    SCL_L;
}  

 
/*******************************************************************************
* Function Name  : IIC_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char IIC_ReadByte(unsigned char ack)  //数据从高位到低位//
{ 
	uint8_t i=8;
  uint8_t ReceiveByte=0;
	
	SDA_H;				
	while(i--)
	{
		ReceiveByte<<=1;      
		SCL_L;
		IIC_delay();
	SCL_H;
		IIC_delay();	
		if(SDA_read)
		{
			ReceiveByte|=0x01;
		}
	}
	if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
	return ReceiveByte;
} 

/**************************************************************************
函数功能：写入指定设备 指定寄存器的一个字节
**************************************************************************/

bool MPU_WriteByte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	IIC_Start();
    IIC_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!IIC_WaitAck()){IIC_Stop(); return 0;}
    IIC_SendByte(REG_Address );   //设置低起始地址      
    IIC_WaitAck();	
    IIC_SendByte(REG_data);
    IIC_WaitAck();   
    IIC_Stop(); 
    delay5ms();
    return 1;
}

/**************************************************************************
函数功能：读取指定设备 指定寄存器的一个字节
**************************************************************************/
unsigned char MPU_ReadByte(unsigned char SlaveAddress,unsigned char REG_Address)
{   
	unsigned char REG_data;   
	
	IIC_Start();
	IIC_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
	if(!IIC_WaitAck()){IIC_Stop(); return 0;}
	IIC_SendByte((uint8_t) REG_Address);   //设置低起始地址      
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(SlaveAddress+1);
	IIC_WaitAck();

	REG_data= IIC_ReadByte(0);
	IIC_Stop();
	return REG_data;
}

//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
	uint8_t i; 
  IIC_Start(); 
	IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
	if(!IIC_WaitAck())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_SendByte(reg);	//写寄存器地址
    IIC_WaitAck();		//等待应答
	for(i=0;i<len;i++)
	{
		IIC_SendByte(buf[i]);	//发送数据
		if(!IIC_WaitAck())		//等待ACK
		{
			IIC_Stop();	 
			return 1;		 
		}		
	}    
    IIC_Stop();	 
	return 0;	
} 
//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
 	IIC_Start(); 
	IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
	if(!IIC_WaitAck())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_SendByte(reg);	//写寄存器地址
    IIC_WaitAck();		//等待应答
    IIC_Start();
		IIC_SendByte((addr<<1)|1);//发送器件地址+读命令	
    IIC_WaitAck();		//等待应答 
	while(len)
	{
		if(len==1)*buf=IIC_ReadByte(0);//读数据,发送nACK 
		else *buf=IIC_ReadByte(1);		//读数据,发送ACK  
		len--;
		buf++; 
	}    
    IIC_Stop();	//产生一个停止条件 
	return 0;	
}

