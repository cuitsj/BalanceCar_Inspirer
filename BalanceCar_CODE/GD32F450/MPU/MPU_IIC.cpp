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
		
   uint8_t i=30; //��������Ż��ٶ�	����������͵�5����д��
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
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Start(void)
*��������:		����IIC��ʼ�ź�
*******************************************************************************/
int IIC_Start(void)
{
	SDA_OUT;     //sda�����
	SDA_H;
	if(!SDA_READ)return 0;	
	SCL_H;
	IIC_delay();
 	SDA_L;//START:when CLK is high,DATA change form high to low 
	if(SDA_READ)return 0;
	IIC_delay();
	SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
	return 1;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Stop(void)
*��������:	    //����IICֹͣ�ź�
*******************************************************************************/	  
void IIC_Stop(void)
{
	SDA_OUT;//sda�����
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	IIC_delay();
	SCL_H; 
	SDA_H;//����I2C���߽����ź�
	IIC_delay();							   	
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		uint8_t IIC_Wait_Ack(void)
*��������:	    �ȴ�Ӧ���źŵ��� 
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
*******************************************************************************/
int IIC_WaitAck(void)
{
	uint8_t ucErrTime=0;
	SDA_IN;      //SDA����Ϊ����  
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
	SCL_L;//ʱ�����0 	   
	return 1;  
} 

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Ack(void)
*��������:	    ����ACKӦ��
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
	
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_NAck(void)
*��������:	    ����NACKӦ��
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
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Send_Byte(uint8_t txd)
*��������:	    IIC����һ���ֽ�
*******************************************************************************/		  
void IIC_SendByte(uint8_t txd)
{                        
    uint8_t t;  
	
		SDA_OUT; 	    
    SCL_L;//����ʱ�ӿ�ʼ���ݴ���
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
unsigned char IIC_ReadByte(unsigned char ack)  //���ݴӸ�λ����λ//
{ 
    unsigned char i,receive=0;
	SDA_IN;//SDA����Ϊ����
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
        IIC_Ack(); //����ACK 
    else
        IIC_NAck();//����nACK  
    return receive;
} 

/**************************************************************************
�������ܣ�д��ָ���豸 ָ���Ĵ�����һ���ֽ�
**************************************************************************/

bool MPU_Write_Byte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!IIC_Start())return 0;
    IIC_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�//IIC_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!IIC_WaitAck()){IIC_Stop(); return 0;}
    IIC_SendByte(REG_Address );   //���õ���ʼ��ַ      
    IIC_WaitAck();	
    IIC_SendByte(REG_data);
    IIC_WaitAck();   
    IIC_Stop(); 
    delay5ms();
    return 1;
}

/**************************************************************************
�������ܣ���ȡָ���豸 ָ���Ĵ�����һ���ֽ�
**************************************************************************/
unsigned char MPU_Read_Byte(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	if(!IIC_Start())return 0;
    IIC_SendByte(SlaveAddress); //IIC_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!IIC_WaitAck()){IIC_Stop(); return 0;}
    IIC_SendByte((uint8_t) REG_Address);   //���õ���ʼ��ַ      
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

//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
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

//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
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

