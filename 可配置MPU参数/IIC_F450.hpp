#pragma once
 
#include <stdint.h>

/*模拟IIC端口输出输入定义*/
#define SCL_H         gBSP->MPU_SCL->Set()
#define SCL_L         gBSP->MPU_SCL->Reset()
   
#define SDA_H         gBSP->MPU_SDA->Set()
#define SDA_L         gBSP->MPU_SDA->Reset()

#define SCL_read      gBSP->MPU_SCL->Gets()
#define SDA_read      gBSP->MPU_SDA->Gets()
             			 
void IIC_Init(void);
bool IIC_Start(void);				
void IIC_Stop(void);	
void IIC_Ack(void);					
void IIC_NAck(void);		
bool IIC_WaitAck(void); 	
void IIC_SendByte(uint8_t SendByte);	
unsigned char IIC_ReadByte(void);
bool Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);
			
	