#pragma once
 
#include <stdint.h>

/*ģ��IIC�˿�������붨��*/
#define SCL_H         gBSP->MPU_SCL->Set()
#define SCL_L         gBSP->MPU_SCL->Reset()
   
#define SDA_H         gBSP->MPU_SDA->Set()
#define SDA_L         gBSP->MPU_SDA->Reset()

#define SCL_read      gBSP->MPU_SCL->Gets()
#define SDA_read      gBSP->MPU_SDA->Gets()
             			 
void IIC_Init(void);
void IIC_Start(void);				
void IIC_Stop(void);	
void IIC_Ack(void);					
void IIC_NAck(void);		
bool IIC_WaitAck(void); 	
void IIC_SendByte(uint8_t SendByte);	
unsigned char IIC_ReadByte(unsigned char ack);
bool MPU_WriteByte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char MPU_ReadByte(unsigned char SlaveAddress,unsigned char REG_Address);
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
			
	