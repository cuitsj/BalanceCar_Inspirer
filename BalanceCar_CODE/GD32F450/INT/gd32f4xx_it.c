/*!
    \file  gd32f4xx_it.c
    \brief interrupt service routines
    \version 2016-08-15, V1.0.0, demo for GD32F4xx
    \version 2018-12-12, V2.0.0, demo for GD32F4xx
*/
 
/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.
    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/
 
#include "gd32f4xx_it.h"
#include "systick.h"
#include "gd32f4xx_usart.h"

/*!
    \brief      this function handles TIMER2 interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER2_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER2,TIMER_INT_CH0))
	{
		timer_interrupt_flag_clear(TIMER2,TIMER_INT_CH0);
	}
	if(timer_interrupt_flag_get(TIMER2,TIMER_INT_CH1))
	{
		timer_interrupt_flag_clear(TIMER2,TIMER_INT_CH1);
	}
}

/*!
    \brief      this function handles TIMER3 interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER3_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER3,TIMER_INT_CH0))
	{
		timer_interrupt_flag_clear(TIMER3,TIMER_INT_CH0);
	}
	if(timer_interrupt_flag_get(TIMER3,TIMER_INT_CH1))
	{
		timer_interrupt_flag_clear(TIMER3,TIMER_INT_CH1);
	}
}

////空闲中断一帧数据响应一次
//void USART0_IRQHandler(void)
//{
//	if(usart_interrupt_flag_get(USART0, USART_INT_FLAG_IDLE))
//	{
//		usart_data_receive(USART0);//必须加这一句，不然程序卡死
//		usart_interrupt_flag_clear(USART0,USART_INT_FLAG_IDLE);//清空闲中断标志
//	}
//}

//void USART1_IRQHandler(void)
//{
//	if(usart_interrupt_flag_get(USART1, USART_INT_FLAG_IDLE))
//	{
//		usart_data_receive(USART1);//必须加这一句，不然程序卡死
//		usart_interrupt_flag_clear(USART1,USART_INT_FLAG_IDLE);//清空闲中断标志
//	}
//}

//void USART2_IRQHandler(void)
//{
//	if(usart_interrupt_flag_get(USART2, USART_INT_FLAG_IDLE))
//	{
//		usart_data_receive(USART2);//必须加这一句，不然程序卡死
//		usart_interrupt_flag_clear(USART2,USART_INT_FLAG_IDLE);//清空闲中断标志
//	}
//}

/*!
    \brief      this function handles DMA1_Channel7_IRQHandler interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
//UART0_TX
void DMA1_Channel7_IRQHandler(void)
{
	if(dma_interrupt_flag_get(DMA1, DMA_CH7, DMA_INT_FLAG_FTF))
	{
		dma_interrupt_flag_clear(DMA1, DMA_CH7, DMA_INT_FLAG_FTF);
	}
}
 
/*!
    \brief      this function handles DMA0_Channel4_IRQHandler interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
//UART0_RX
void DMA1_Channel2_IRQHandler(void)
{
	if(dma_interrupt_flag_get(DMA1, DMA_CH2, DMA_INT_FLAG_FTF))
	{
		dma_interrupt_flag_clear(DMA1, DMA_CH2, DMA_INT_FLAG_FTF);
	}
}

//UART1_RX
void DMA0_Channel5_IRQHandler(void)
{
	if(dma_interrupt_flag_get(DMA0, DMA_CH5, DMA_INT_FLAG_FTF))
	{
		dma_interrupt_flag_clear(DMA0, DMA_CH5, DMA_INT_FLAG_FTF);
	}
}
 
/*!
    \brief      this function handles DMA0_Channel4_IRQHandler interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
//UART1_TX
void DMA0_Channel6_IRQHandler(void)
{
	if(dma_interrupt_flag_get(DMA0, DMA_CH6, DMA_INT_FLAG_FTF))
	{
		dma_interrupt_flag_clear(DMA0, DMA_CH6, DMA_INT_FLAG_FTF);
	}
}

//UART2_RX
void DMA0_Channel1_IRQHandler(void)
{
	if(dma_interrupt_flag_get(DMA0, DMA_CH1, DMA_INT_FLAG_FTF))
	{
		dma_interrupt_flag_clear(DMA0, DMA_CH1, DMA_INT_FLAG_FTF);
	}
}

//UART2_TX
void DMA0_Channel3_IRQHandler(void)
{
	if(dma_interrupt_flag_get(DMA0, DMA_CH3, DMA_INT_FLAG_FTF))
	{
		dma_interrupt_flag_clear(DMA0, DMA_CH3, DMA_INT_FLAG_FTF);
	}
}
 
 
/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}
 
/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
//void HardFault_Handler(void)
//{
//    /* if Hard Fault exception occurs, go to infinite loop */
//    while (1){
//    }
//}
 
/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1){
    }
}
 
/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1){
    }
}
 
/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1){
    }
}
 
/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}
 
/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}
 
/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
//void PendSV_Handler(void)
//{
//}
 
/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
//void SysTick_Handler(void)
//{
//    delay_decrement();
//		rt_os_tick_callback();
//}