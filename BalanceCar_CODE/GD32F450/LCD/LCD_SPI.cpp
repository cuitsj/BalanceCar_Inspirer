#include "main.h"
#include "lcd_spi.hpp"

#define HAL_Delay gOS->delay_ms

void LCD_GPIO_Init(void)
{
	//IPS: B12-->SPI_SCL,B13-->SPI_SDA,B14-->SPI_DC,B15-->SPI_RES
//	rcu_periph_clock_enable(RCU_GPIOB);
//	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
//	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
}


void SPI_Delay(void)
{
		
   uint8_t i=30; //��������Ż��ٶ�	����������͵�5����д��
   while(i) 
   { 
     i--; 
   }  
}

/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
	u8 i;
//	LCD_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		LCD_SCLK_Clr();
		if(dat&0x80)
		{
		   LCD_MOSI_Set();
		}
		else
		{
		   LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat<<=1;
	}	
//	HAL_SPI_Transmit(&hspi1,&dat,1,10);//��������
  LCD_DC_Set();//д����
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();//д����
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//д����
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+52);
		LCD_WR_DATA(x2+52);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+40);
		LCD_WR_DATA(y2+40);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+53);
		LCD_WR_DATA(x2+53);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+40);
		LCD_WR_DATA(y2+40);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+40);
		LCD_WR_DATA(x2+40);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+53);
		LCD_WR_DATA(y2+53);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+40);
		LCD_WR_DATA(x2+40);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+52);
		LCD_WR_DATA(y2+52);
		LCD_WR_REG(0x2c);//������д
	}
}

void LCD_Init(void)
{
	//LCD_GPIO_Init();//��ʼ��GPIO
	
	LCD_RES_Clr();//��λ
	HAL_Delay(100);
	LCD_RES_Set();
	HAL_Delay(100);
	
	//LCD_BLK_Set();//�򿪱���
  HAL_Delay(100);
	
	LCD_WR_REG(0x11); 
	HAL_Delay(120); 
	LCD_WR_REG(0x36); 
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29); 
}