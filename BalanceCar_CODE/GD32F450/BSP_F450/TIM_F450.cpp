#include "TIM_F450.hpp"
#include "main.h"

 
bool flag = 0;

TIM0_F450::TIM0_F450(uint8_t _motor_id)
{
	motor_id = _motor_id;
}

//PA8 PA9 PA10 PA11
void TIM0_F450::Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11);
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11);
	
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;
 
	rcu_periph_clock_enable(RCU_TIMER0);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
 
	if (flag == 0)
	{
		timer_deinit(TIMER0);
		flag = 1;
	}
	timer_primary_output_config(TIMER0,ENABLE);

	timer_initpara.prescaler         = 9;
	timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;
	timer_initpara.period            = 999;
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER0,&timer_initpara);
 
	timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
	timer_channel_output_config(TIMER0,TIMER_CH_0,&timer_ocintpara);
	timer_channel_output_config(TIMER0,TIMER_CH_1,&timer_ocintpara);
	timer_channel_output_config(TIMER0,TIMER_CH_2,&timer_ocintpara);
	timer_channel_output_config(TIMER0,TIMER_CH_3,&timer_ocintpara);
 
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,0);
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,0);
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_2,0);
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,0);
	timer_channel_output_mode_config(TIMER0,TIMER_CH_0,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(TIMER0,TIMER_CH_1,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(TIMER0,TIMER_CH_2,TIMER_OC_MODE_PWM0);
	timer_channel_output_mode_config(TIMER0,TIMER_CH_3,TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER0,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);
	timer_channel_output_shadow_config(TIMER0,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);
	timer_channel_output_shadow_config(TIMER0,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
	timer_channel_output_shadow_config(TIMER0,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
 
	timer_auto_reload_shadow_enable(TIMER0);
	timer_enable(TIMER0);
}

void TIM0_F450::SetDUTY(int16_t duty)
{
	switch(motor_id)
	{
		case 0://左轮
			if (duty>0)
			{
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,0);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_0,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,duty);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_1,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);
			}
			else
			{
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,-duty);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_0,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,0);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_1,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);
			}
			break;
		case 1://右轮
			if (duty>0)
			{
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_2,duty);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_2,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,0);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_3,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
			}
			else
			{
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_2,0);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_2,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
				timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,-duty);
				timer_channel_output_mode_config(TIMER0,TIMER_CH_3,TIMER_OC_MODE_PWM0);
				timer_channel_output_shadow_config(TIMER0,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
			}
			break;
			default :break;
	}
}

//PC6 PC7
void TIM2_F450::Init(void)
{
		timer_ic_parameter_struct timer_icinitpara;
		timer_parameter_struct timer_initpara;

		rcu_periph_clock_enable(RCU_TIMER2);
		rcu_periph_clock_enable(RCU_GPIOC);

	  gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6|GPIO_PIN_7);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6|GPIO_PIN_7);                                
    gpio_af_set(GPIOC, GPIO_AF_2, GPIO_PIN_6|GPIO_PIN_7);
	
		timer_deinit(TIMER2);
		timer_initpara.prescaler         = 0;
		timer_initpara.alignedmode       = TIMER_COUNTER_CENTER_BOTH;
		timer_initpara.counterdirection  = TIMER_COUNTER_UP;//向上计数
		timer_initpara.period            = 65535;
		timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
		timer_initpara.repetitioncounter = 0;
		timer_init(TIMER2,&timer_initpara);

		timer_icinitpara.icfilter = 0x03;
		timer_icinitpara.icpolarity = TIMER_IC_POLARITY_BOTH_EDGE;
		timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
		timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;

		timer_input_capture_config(TIMER2,TIMER_CH_0,&timer_icinitpara);
		timer_input_capture_config(TIMER2,TIMER_CH_1,&timer_icinitpara);

		timer_quadrature_decoder_mode_config(TIMER2,TIMER_ENCODER_MODE2,TIMER_IC_POLARITY_BOTH_EDGE,TIMER_IC_POLARITY_BOTH_EDGE);
		timer_counter_value_config(TIMER2,0);
		timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_CH0);
		timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_CH1);               
		timer_interrupt_enable(TIMER2, TIMER_INT_UP);
		timer_interrupt_enable(TIMER2, TIMER_INT_CH0 |TIMER_INT_CH1);
		timer_enable(TIMER2);
}

int16_t TIM2_F450::ReadCnt(void)
{
	int16_t temp = 0;
	
	temp = (int16_t)timer_counter_read(TIMER2);
	timer_counter_value_config(TIMER2,0);
	
	return temp;
}


//PD12 PD13
void TIM3_F450::Init(void)
{
	timer_ic_parameter_struct timer_icinitpara;
	timer_parameter_struct timer_initpara;

	rcu_periph_clock_enable(RCU_TIMER3);
	rcu_periph_clock_enable(RCU_GPIOD);

	gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12|GPIO_PIN_13);
	gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12|GPIO_PIN_13);                                
	gpio_af_set(GPIOD, GPIO_AF_2, GPIO_PIN_12|GPIO_PIN_13);

	timer_deinit(TIMER3);
	timer_initpara.prescaler         = 0;
	timer_initpara.alignedmode       = TIMER_COUNTER_CENTER_BOTH;
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;//向上计数
	timer_initpara.period            = 65535;
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER3,&timer_initpara);

	timer_icinitpara.icfilter = 0x03;
	timer_icinitpara.icpolarity = TIMER_IC_POLARITY_BOTH_EDGE;
	timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
	timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;

	timer_input_capture_config(TIMER3,TIMER_CH_0,&timer_icinitpara);
	timer_input_capture_config(TIMER3,TIMER_CH_1,&timer_icinitpara);

	timer_quadrature_decoder_mode_config(TIMER3,TIMER_ENCODER_MODE2,TIMER_IC_POLARITY_BOTH_EDGE,TIMER_IC_POLARITY_BOTH_EDGE);
	timer_counter_value_config(TIMER3,0);
	timer_interrupt_flag_clear(TIMER3, TIMER_INT_FLAG_CH0);
	timer_interrupt_flag_clear(TIMER3, TIMER_INT_FLAG_CH1);               
	timer_interrupt_enable(TIMER3, TIMER_INT_UP);
	timer_interrupt_enable(TIMER3, TIMER_INT_CH0 |TIMER_INT_CH1);
	timer_enable(TIMER3);
}

int16_t TIM3_F450::ReadCnt(void)
{
	int16_t temp = 0;
	
	temp = (int16_t)timer_counter_read(TIMER3);
	timer_counter_value_config(TIMER3,0);
	
	return -temp;
}

//PE5
void TIM8_F450::Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOE);
	gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
	gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
	gpio_af_set(GPIOE, GPIO_AF_3, GPIO_PIN_5);
	
	timer_oc_parameter_struct timer_ocintpara;
	timer_parameter_struct timer_initpara;
 
	rcu_periph_clock_enable(RCU_TIMER8);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
 
	if (flag == 0)
	{
		timer_deinit(TIMER8);
		flag = 1;
	}
	timer_primary_output_config(TIMER8,ENABLE);

	timer_initpara.prescaler         = 19999;
	timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;
	timer_initpara.period            = 99;
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER8,&timer_initpara);

	timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
	timer_channel_output_config(TIMER8,TIMER_CH_0,&timer_ocintpara);
	timer_channel_output_pulse_value_config(TIMER8,TIMER_CH_0,0);
	timer_channel_output_mode_config(TIMER8,TIMER_CH_0,TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER8,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);
	timer_auto_reload_shadow_enable(TIMER8);
	timer_enable(TIMER8);
}
 
void TIM8_F450::SetDUTY(int16_t duty)
{
  timer_channel_output_pulse_value_config(TIMER8,TIMER_CH_0,duty);
	timer_channel_output_mode_config(TIMER8,TIMER_CH_0,TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER8,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);
}

void TIM8_F450::SetFREQ(float freq)
{
	timer_parameter_struct timer_initpara;
	
	uint16_t buf=0;
	buf = sqrt(200000000/freq)-1;
	timer_initpara.prescaler         = buf;
	timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;
	timer_initpara.period            = buf;
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER8,&timer_initpara);
}

