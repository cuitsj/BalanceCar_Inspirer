/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
 
#include "BSP_F450.hpp"
#include "OS.hpp"
#include "IO_F450.hpp"
#include "UART_F450.hpp"
#include "SPI_F450.hpp"
#include "ADC_F450.hpp"
#include "TIM_F450.hpp"

#include "TASK_SCREEN.hpp"
#include "TASK_BALANCE.hpp"
#include "TASK_MUSIC.hpp"
#include "TASK_MPU.hpp"
#include "OS_TIMER.hpp"
#include "MPU_IIC.hpp"
#include "MPU9250.hpp"
#include "AHRS.hpp"

extern BSP_F450 *gBSP;
extern OS *gOS;

#ifdef __cplusplus
extern "C" {
#endif
 
	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <rtthread.h>
#include <math.h>
#include "gd32f4xx.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx.h"
#include "gd32f4xx_dma.h"
#include "system_gd32f4xx.h"
#include "gd32f4xx_rcu.h"
#include "DataScope_DP.h"
#include "systick.h"

#include "dmpKey.hpp"
#include "dmpmap.hpp"
#include "inv_mpu.hpp"
#include "inv_mpu_dmp_motion_driver.hpp"
#include "LCD.hpp"
#include "LCD_SPI.hpp"
#include "PIC.hpp"
#include "LCDFONT.hpp"


 
 
 
	
 
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
 
/* USER CODE END Includes */
 
/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
 
/* USER CODE END ET */
 
/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
 
/* USER CODE END EC */
 
/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
/* USER CODE END EM */
 
/* Exported functions prototypes ---------------------------------------------*/
//void Error_Handler(void);
 
/* USER CODE BEGIN EFP */
 
/* USER CODE END EFP */
 
/* Private defines -----------------------------------------------------------*/
 
/* USER CODE BEGIN Private defines */
 
/* USER CODE END Private defines */
 
#ifdef __cplusplus
}
#endif

 
#endif /* __MAIN_H */