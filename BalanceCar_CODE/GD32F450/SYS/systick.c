/*!
    \file  systick.c
    \brief the systick configuration file

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

#include "gd32f4xx.h"
#include "systick.h"

volatile static uint32_t delay;


#define SYSTICK_EXT_CLOCK_500MS_CNT (120000000/8/2)
 
volatile static uint32_t systick_ms = 0;
volatile static uint32_t systick_us = 0;
volatile static uint8_t is_init = 0;

//static void systick_init(void)
//{
//	__disable_irq();
//	is_init = 1;
//	SysTick->LOAD  = SYSTICK_EXT_CLOCK_500MS_CNT; 
//	SysTick->VAL   = SYSTICK_EXT_CLOCK_500MS_CNT;
//	SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
//	__enable_irq();
//}
// 
//void systick_deinit(void)
//{
//	__disable_irq();
//	is_init = 0;
//	SysTick->CTRL  &= (~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk));
//	__enable_irq();
//}
// 
//void delay_us(uint32_t us)
//{
//	uint32_t end_count = 0, current = 0;
//	
//	if (!is_init) systick_init();
//	
//	current = get_systick_us();
//	end_count = current + us;
// 
//	if (end_count == current) {
//		return;
//	} else if (end_count > current) {
//		while (get_systick_us() < end_count);
//	} else {
//		while (get_systick_us() >= current);
//		while (get_systick_us() < end_count);
//	}
//}
// 
//void delay_ms(uint32_t ms)
//{
//	uint32_t end_count = 0, current = 0;
//	
//	if(!is_init) systick_init();
//	current = get_systick_ms();
//	end_count = current + ms;
// 
//	if (end_count == current) {
//		return;
//	} else if (end_count > current) {
//		while (get_systick_ms() < end_count);
//	} else {
//		while (get_systick_ms() >= current);
//		while (get_systick_ms() < end_count);
//	}
//}
// 
///*
// * Max 4294967295(us)=4294967(us)=4294(s)=71(min)
// */
//uint32_t get_systick_us(void)
//{
//	uint32_t _systick_us, _val;
//	
//	
// 
//#if 0
//	/*
//	 * 64bit, low efficiency 
//	 */
//	uint64_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val); 
//	uint32_t tick_us =(tick * 1000 * 500) / SYSTICK_EXT_CLOCK_500MS_CNT;
//#else
//	/*
//	 * 32bit, high efficiency 
//	 */
//	uint32_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val);
//	uint32_t tick_us =(tick * 200) / (SYSTICK_EXT_CLOCK_500MS_CNT / 2500);
//#endif
//	
//	if (!is_init) systick_init();
//	do {
//		_systick_us = systick_us;
//		_val = SysTick->VAL;
//	} while (_systick_us != systick_us);
// 
//	return (tick_us + _systick_us);
//}
// 
///*
// * Max 4294967295(ms)=4294967(s)=71582(min)=1193(hour)=49(day)
// */
//uint32_t get_systick_ms(void)
//{
//	uint32_t _systick_ms, _val;
// 
//	uint32_t tick = (SYSTICK_EXT_CLOCK_500MS_CNT - _val);
//	uint32_t tick_ms = tick / (SYSTICK_EXT_CLOCK_500MS_CNT / 500);
//	tick_ms = tick_ms + _systick_ms;
// 
//	if (!is_init) systick_init();
//	do {
//		_systick_ms = systick_ms;
//		_val = SysTick->VAL;
//	} while (_systick_ms != systick_ms);
//	
//	return tick_ms ;
//}

/*!
    \brief      configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U)){
        /* capture error */
        while (1){
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_1ms(uint32_t count)
{
    delay = count;

    while(0U != delay){
    }
}

/*!
    \brief      delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
    if (0U != delay){
        delay--;
    }
}
