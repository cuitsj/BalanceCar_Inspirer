#include "IO_F450.hpp"
#include "main.h"

IO_F450::IO_F450(uint32_t _GPIOx, uint32_t _io_pin)
{
	GPIOx = _GPIOx;
	io_pin = _io_pin;
}

void IO_F450::Set_level(bool level)
{
	gpio_bit_write(GPIOx,io_pin,level?SET:RESET);
}

void IO_F450::Set(void)
{
	gpio_bit_write(GPIOx,io_pin,SET);
}

void IO_F450::Reset(void)
{
	gpio_bit_write(GPIOx,io_pin,RESET);
}

void IO_F450::Toggle(void)
{
	gpio_bit_toggle(GPIOx,io_pin);
}

uint8_t IO_F450::Gets(void)
{
	return gpio_input_bit_get(GPIOx, io_pin);
}

void IO_F450::Init(void)
{
	//E13-->OK°´¼ü E14-->MODE°´¼ü
	rcu_periph_clock_enable(RCU_GPIOE);
	gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_13|GPIO_PIN_14);
	
	//MPU9250: B8-->IIC0_SCL,B9-->IIC0_SDA
	rcu_periph_clock_enable(RCU_GPIOB);
	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_8|GPIO_PIN_9);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8|GPIO_PIN_9);
	gpio_bit_write(GPIOB,GPIO_PIN_8|GPIO_PIN_9,SET);
	
	//IPS: B12-->SPI_SCL,B13-->SPI_SDA,B14-->SPI_DC,B15-->SPI_RES
	rcu_periph_clock_enable(RCU_GPIOB);
	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	
	//RGB: A0->G A1->R A2->B
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
	gpio_bit_write(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,SET);
}