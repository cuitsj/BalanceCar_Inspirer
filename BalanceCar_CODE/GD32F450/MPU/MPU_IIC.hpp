#pragma once
 
#include <stdint.h>

/*模拟IIC端口输出输入定义*/
#define SCL_H         gBSP->MPU_SCL->Set()
#define SCL_L         gBSP->MPU_SCL->Reset()
   
#define SDA_H         gBSP->MPU_SDA->Set()
#define SDA_L         gBSP->MPU_SDA->Reset()

#define SCL_READ      gBSP->MPU_SCL->Gets()
#define SDA_READ      gBSP->MPU_SDA->Gets()

#define SDA_IN				gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);
#define SDA_OUT				gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);
						
void IIC_delay(void);						
bool MPU_Write_Byte(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char MPU_Read_Byte(unsigned char SlaveAddress,unsigned char REG_Address);
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
			
	