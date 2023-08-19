#include "MPU_IIC.hpp"
#include "main.h"



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
/**************************实现函数********************************************
*函数原型:		void IIC_Start(void)
*功　　能:		产生IIC起始信号
*******************************************************************************/
int IIC_Start(void)
{
	SDA_OUT;     //sda线输出
	SDA_H;
	if(!SDA_READ)return 0;	
	SCL_H;
	IIC_delay();
 	SDA_L;//START:when CLK is high,DATA change form high to low 
	if(SDA_READ)return 0;
	IIC_delay();
	SCL_L;//钳住I2C总线，准备发送或接收数据 
	return 1;
}

/**************************实现函数********************************************
*函数原型:		void IIC_Stop(void)
*功　　能:	    //产生IIC停止信号
*******************************************************************************/	  
void IIC_Stop(void)
{
	SDA_OUT;//sda线输出
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	IIC_delay();
	SCL_H; 
	SDA_H;//发送I2C总线结束信号
	IIC_delay();							   	
}

/**************************实现函数********************************************
*函数原型:		uint8_t IIC_Wait_Ack(void)
*功　　能:	    等待应答信号到来 
//返回值：1，接收应答失败
//        0，接收应答成功
*******************************************************************************/
int IIC_WaitAck(void)
{
	uint8_t ucErrTime=0;
	SDA_IN;      //SDA设置为输入  
	SDA_H;
	IIC_delay();	   
	SCL_H;
	IIC_delay();	 
	while(SDA_READ)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			IIC_Stop();
			return 0;
		}
	  IIC_delay();
	}
	SCL_L;//时钟输出0 	   
	return 1;  
} 

/**************************实现函数********************************************
*函数原型:		void IIC_Ack(void)
*功　　能:	    产生ACK应答
*******************************************************************************/
void IIC_Ack(void)
{
	SCL_L;
	SDA_OUT;
	SDA_L;
	IIC_delay();
	SCL_H;
	IIC_delay();
	SCL_L;
}
	
/**************************实现函数********************************************
*函数原型:		void IIC_NAck(void)
*功　　能:	    产生NACK应答
*******************************************************************************/	    
void IIC_NAck(void)
{
	SCL_L;
	SDA_OUT;
	SDA_H;
	IIC_delay();
	SCL_H;
	IIC_delay();
	SCL_L;
}
/**************************实现函数********************************************
*函数原型:		void IIC_Send_Byte(uint8_t txd)
*功　　能:	    IIC发送一个字节
*******************************************************************************/		  
void IIC_SendByte(uint8_t txd)
{                        
    uint8_t t;  
	
		SDA_OUT; 	    
    SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
			if(txd&0x80)SDA_H;  
			else SDA_L;
			txd<<=1; 	  
			IIC_delay();   
			SCL_H;
			IIC_delay(); 
			SCL_L;	
			IIC_delay();
    }	 
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
    unsigned char i,receive=0;
	SDA_IN;//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        SCL_L; 
        IIC_delay();
		SCL_H;
        receive<<=1;
        if(SDA_READ)receive++;   
		IIC_delay();
    }					 
    if (ack)
        IIC_Ack(); //发送ACK 
    else
        IIC_NAck();//发送nACK  
    return receive;
} 

/**************************************************************************
函数功能：写入指定设备 指定寄存器的一个字节
**************************************************************************/

bool MPU_Write_Byte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!IIC_Start())return 0;
    IIC_SendByte(SlaveAddress);   //发送设备地址+写信号//IIC_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
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
unsigned char MPU_Read_Byte(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	if(!IIC_Start())return 0;
    IIC_SendByte(SlaveAddress); //IIC_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!IIC_WaitAck()){IIC_Stop(); return 0;}
    IIC_SendByte((uint8_t) REG_Address);   //设置低起始地址      
    IIC_WaitAck();
    IIC_Start();
    IIC_SendByte(SlaveAddress+1);
    IIC_WaitAck();

	REG_data= IIC_ReadByte(0);
    IIC_NAck();
    IIC_Stop();
    //return 1;
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
   int i;
    if (!IIC_Start())
        return 1;
    IIC_SendByte(addr);
    if (!IIC_WaitAck()) {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg);
    IIC_WaitAck();
		for (i = 0; i < len; i++) {
        IIC_SendByte(buf[i]);
        if (!IIC_WaitAck()) {
            IIC_Stop();
            return 0;
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
    if (!IIC_Start())
        return 1;
    IIC_SendByte(addr);
    if (!IIC_WaitAck()) {
        IIC_Stop();
        return 1;
    }
    IIC_SendByte(reg);
    IIC_WaitAck();
    IIC_Start();
    IIC_SendByte((addr)+1);
    IIC_WaitAck();
    while (len) {
        if (len == 1)
            *buf = IIC_ReadByte(0);
        else
            *buf = IIC_ReadByte(1);
        buf++;
        len--;
    }
    IIC_Stop();
    return 0;
}

