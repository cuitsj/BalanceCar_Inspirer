#pragma once

#include "main.h"
 		     
#define u16 uint16_t
#define u8 uint8_t

#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ���� 0��1���෴�ķ���


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 135
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 135
#endif

//-----------------LCD�˿ڶ���---------------- 
//IPS: B12-->SPI_SCL,B13-->SPI_SDA,B14-->SPI_DC,B15-->SPI_RES

#define LCD_SCLK_Clr() gBSP->LCD_SCL->Reset()//SCL=SCLK
#define LCD_SCLK_Set() gBSP->LCD_SCL->Set()

#define LCD_MOSI_Clr() gBSP->LCD_SDA->Reset()//SDA=MOSI
#define LCD_MOSI_Set() gBSP->LCD_SDA->Set()

#define LCD_RES_Clr()  gBSP->LCD_RES->Reset()//RES
#define LCD_RES_Set()  gBSP->LCD_RES->Set()

#define LCD_DC_Clr()   gBSP->LCD_DC->Reset()//DC
#define LCD_DC_Set()   gBSP->LCD_DC->Set()


//#define LCD_RES_Clr() HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_RESET)//RES
//#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,GPIO_PIN_SET)

//#define LCD_DC_Clr()  HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)//DC 
//#define LCD_DC_Set()   HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET) 
// 		     


//#define LCD_BLK_Clr()   HAL_GPIO_WritePin(LCD_BLK_GPIO_Port,LCD_BLK_Pin,GPIO_PIN_RESET)//BLK
//#define LCD_BLK_Set()    HAL_GPIO_WritePin(LCD_BLK_GPIO_Port,LCD_BLK_Pin,GPIO_PIN_SET)

//#define LCD_CS_Clr()   GPIO_ResetBits(GPIOD,GPIO_Pin_1)//CS
//#define LCD_CS_Set()   GPIO_SetBits(GPIOD,GPIO_Pin_1)

//#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_5)//SDA=MOSI
//#define LCD_MOSI_Set() GPIO_SetBits(GPIOD,GPIO_Pin_5)

//#define LCD_SCLK_Clr()  HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_RESET)//RES//SCL=SCLK
//#define LCD_SCLK_Set() GPIO_SetBits(GPIOG,GPIO_Pin_12)

//void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��





