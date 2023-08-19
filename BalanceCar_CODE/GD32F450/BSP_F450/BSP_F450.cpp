#include "BSP_F450.hpp"
#include "main.h"

BSP_F450::BSP_F450()
{
	flag_debug = 0;
	KEY_MODE = new IO_F450(GPIOE,GPIO_PIN_14);
	KEY_OK = new IO_F450(GPIOE,GPIO_PIN_13);
	MPU_SCL = new IO_F450(GPIOB,GPIO_PIN_8);
	MPU_SDA = new IO_F450(GPIOB,GPIO_PIN_9);
	LCD_SCL = new IO_F450(GPIOB,GPIO_PIN_12);
	LCD_SDA = new IO_F450(GPIOB,GPIO_PIN_13);
	LCD_DC = new IO_F450(GPIOB,GPIO_PIN_14);
	LCD_RES = new IO_F450(GPIOB,GPIO_PIN_15);
	LED_R = new IO_F450(GPIOA,GPIO_PIN_1);
	LED_G = new IO_F450(GPIOA,GPIO_PIN_0);
	LED_B = new IO_F450(GPIOA,GPIO_PIN_2);
	UART0_DEBUG = new UART0_F450();
	UART1_BT = new UART1_F450();
	ADC0_VOL = new ADC0_F450();
	TIM0_MOTORR = new TIM0_F450(0);
	TIM0_MOTORL = new TIM0_F450(1);
	TIM3_LENCODER = new TIM3_F450();
	TIM2_RENCODER = new TIM2_F450();
	TIM8_BEEP = new TIM8_F450();
}
 
void BSP_F450::Init(void)
{
	KEY_MODE->Init();//初始化了所有的IO
	KEY_OK->Init();//初始化了所有的IO
	LCD_SCL->Init();
	LCD_SDA->Init();
	LCD_DC->Init();
	LCD_RES->Init();
	UART0_DEBUG->Init(115200);
	UART1_BT->Init(115200);
	ADC0_VOL->Init();
	TIM0_MOTORL->Init();
	TIM0_MOTORR->Init();
	TIM3_LENCODER->Init();
	TIM2_RENCODER->Init();
	TIM8_BEEP->Init();
}
 

//extern "C"
//{
//	void Error_Handler(void)
//	{
//		/* USER CODE BEGIN Error_Handler_Debug */
//		/* User can add his own implementation to report the HAL error return state */
//		__disable_irq();
//		while (1)
//		{
//		}
//		/* USER CODE END Error_Handler_Debug */
//	}
//}
 