#include "UART_F450.hpp"
#include "main.h"
 
#define USART0_DATA_ADDRESS      ((uint32_t)&USART_DATA(USART0))
#define USART1_DATA_ADDRESS      ((uint32_t)&USART_DATA(USART1))
#define USART2_DATA_ADDRESS      ((uint32_t)&USART_DATA(USART2))

/*****************************************UART_DEBUG********************************************/
//B6->AF7->TX->DMA1_CH7_PERIEN4    B7->AF7->RX->DMA1_CH2_PERIEN_4
void UART0_F450::Init(uint32_t baud)
{
	rcu_periph_clock_enable(RCU_DMA1);
	rcu_periph_clock_enable(RCU_USART0);
	rcu_periph_clock_enable(RCU_GPIOB);
	
	gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_6|GPIO_PIN_7);
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_6|GPIO_PIN_7);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_6|GPIO_PIN_7);
	
	usart_deinit(USART0);
	usart_oversample_config(USART0, USART_OVSMOD_8);
	usart_baudrate_set(USART0,baud);			          
	usart_parity_config(USART0, USART_PM_NONE);		  
	usart_word_length_set(USART0, USART_WL_8BIT);
	usart_stop_bit_set(USART0, USART_STB_1BIT);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
//	usart_interrupt_enable(USART0, USART_INT_IDLE);//¿ÕÏÐÖÐ¶Ï
	nvic_irq_enable(USART0_IRQn, 1, 1);
	usart_enable(USART0);
	usart_dma_receive_config(USART0, USART_DENR_ENABLE);
	usart_dma_transmit_config(USART0, USART_DENT_ENABLE);
	nvic_irq_enable(DMA1_Channel7_IRQn, 1, 1);
  nvic_irq_enable(DMA1_Channel2_IRQn, 1, 1);
	dma_single_data_parameter_struct dma_init_struct;
	dma_single_data_para_struct_init(&dma_init_struct);
	dma_deinit(DMA1, DMA_CH7);
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)0;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = 0;
	dma_init_struct.periph_addr = USART0_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA1, DMA_CH7, &dma_init_struct);
	dma_circulation_disable(DMA1, DMA_CH7);
	dma_channel_subperipheral_select(DMA1, DMA_CH7, DMA_SUBPERI4);
	dma_interrupt_enable(DMA1, DMA_CH7, DMA_CHXCTL_FTFIE);
	dma_channel_enable(DMA1, DMA_CH7);
	dma_deinit(DMA1, DMA_CH2);
	dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
	dma_init_struct.memory0_addr = (uint32_t)RxBuf;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.number = 32;
	dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART0);
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA1, DMA_CH2, &dma_init_struct);
	dma_circulation_disable(DMA1, DMA_CH2);
	dma_channel_subperipheral_select(DMA1, DMA_CH2, DMA_SUBPERI4);
	dma_interrupt_enable(DMA1, DMA_CH2, DMA_CHXCTL_FTFIE);
	dma_channel_enable(DMA1, DMA_CH2);
}

void UART0_F450::Write(uint8_t *buf, uint16_t len)
{
	dma_single_data_parameter_struct dma_init_struct;
	
	dma_single_data_para_struct_init(&dma_init_struct);
	dma_deinit(DMA1, DMA_CH7);
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)buf;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = len;
	dma_init_struct.periph_addr = USART0_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA1, DMA_CH7, &dma_init_struct);
	dma_channel_subperipheral_select(DMA1, DMA_CH7, DMA_SUBPERI4);
	dma_channel_enable(DMA1, DMA_CH7);
	while(!dma_flag_get(DMA1,DMA_CH7,DMA_FLAG_FTF));
}

uint16_t UART0_F450::GetRxLenth(void)
{
	return 32-dma_transfer_number_get(DMA1, DMA_CH2);
}

uint16_t UART0_F450::Read(uint8_t *buf)
{
	uint16_t len = 0;
	
	len = 32-dma_transfer_number_get(DMA1, DMA_CH2);
	if(len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			buf[i] = RxBuf[i];
		}
		dma_single_data_parameter_struct dma_init_struct;
		dma_deinit(DMA1, DMA_CH2);
		dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
		dma_init_struct.memory0_addr = (uint32_t)RxBuf;
		dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
		dma_init_struct.number = 32;
		dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART0);
		dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
		dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
		dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
		dma_single_data_mode_init(DMA1, DMA_CH2, &dma_init_struct);
		dma_circulation_disable(DMA1, DMA_CH2);
		dma_channel_subperipheral_select(DMA1, DMA_CH2, DMA_SUBPERI4);
		dma_channel_enable(DMA1, DMA_CH2);
	}
	return len;
}

/*****************************************UART1_BT********************************************/
//D5->AF7->TX->DMA0_CH6_PERIEN4    D6->AF7->RX->DMA0_CH5_PERIEN_4
void UART1_F450::Init(uint32_t baud)
{
	rcu_periph_clock_enable(RCU_DMA0);
	rcu_periph_clock_enable(RCU_USART1);
	rcu_periph_clock_enable(RCU_GPIOD);
	
	gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_5|GPIO_PIN_6);
	gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_5|GPIO_PIN_6);
	gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5|GPIO_PIN_6);
	
	usart_deinit(USART1);
	usart_oversample_config(USART1, USART_OVSMOD_8);
	usart_baudrate_set(USART1,baud);			          
	usart_parity_config(USART1, USART_PM_NONE);		  
	usart_word_length_set(USART1, USART_WL_8BIT);
	usart_stop_bit_set(USART1, USART_STB_1BIT);
	usart_receive_config(USART1, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
//	usart_interrupt_enable(USART1, USART_INT_IDLE);
	
	nvic_irq_enable(USART1_IRQn, 0, 0);
	usart_enable(USART1);
	usart_dma_receive_config(USART1, USART_DENR_ENABLE);
	usart_dma_transmit_config(USART1, USART_DENT_ENABLE);
	
	nvic_irq_enable(DMA0_Channel6_IRQn, 0, 0);
  nvic_irq_enable(DMA0_Channel5_IRQn, 0, 0);
	dma_single_data_parameter_struct dma_init_struct;
	dma_single_data_para_struct_init(&dma_init_struct);
	
	//TX
	dma_deinit(DMA0, DMA_CH6);
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)0;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = 0;
	dma_init_struct.periph_addr = USART1_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH6, &dma_init_struct);
	dma_circulation_disable(DMA0, DMA_CH6);
	dma_channel_subperipheral_select(DMA0, DMA_CH6, DMA_SUBPERI4);
	dma_interrupt_enable(DMA0, DMA_CH6, DMA_CHXCTL_FTFIE);
	dma_channel_enable(DMA0, DMA_CH6);
	
	//RX
	dma_deinit(DMA0, DMA_CH5);
	dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
	dma_init_struct.memory0_addr = (uint32_t)RxBuf;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.number = 32;
	dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART1);
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH5, &dma_init_struct);
	dma_circulation_disable(DMA0, DMA_CH5);
	dma_channel_subperipheral_select(DMA0, DMA_CH5, DMA_SUBPERI4);
	dma_interrupt_enable(DMA0, DMA_CH5, DMA_CHXCTL_FTFIE);
	dma_channel_enable(DMA0, DMA_CH5);
}

//D5->AF7->TX->DMA0_CH6_PERIEN4    D6->AF7->RX->DMA0_CH5_PERIEN_4
void UART1_F450::Write(uint8_t *buf, uint16_t len)
{
	dma_single_data_parameter_struct dma_init_struct;
	
	dma_single_data_para_struct_init(&dma_init_struct);
	dma_deinit(DMA0, DMA_CH6);
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)buf;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = len;
	dma_init_struct.periph_addr = USART1_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH6, &dma_init_struct);
	dma_channel_subperipheral_select(DMA0, DMA_CH6, DMA_SUBPERI4);
	dma_channel_enable(DMA0, DMA_CH6);
	while(!dma_flag_get(DMA0,DMA_CH6,DMA_FLAG_FTF));
}

uint16_t UART1_F450::GetRxLenth(void)
{
	return 32-dma_transfer_number_get(DMA0, DMA_CH5);
}

uint16_t UART1_F450::Read(uint8_t *buf)
{
	uint16_t len = 0;
	
	len = 32-dma_transfer_number_get(DMA0, DMA_CH5);
	if(len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			buf[i] = RxBuf[i];
		}
		dma_single_data_parameter_struct dma_init_struct;
		dma_deinit(DMA0, DMA_CH5);
		dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
		dma_init_struct.memory0_addr = (uint32_t)RxBuf;
		dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
		dma_init_struct.number = 32;
		dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART1);
		dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
		dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
		dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
		dma_single_data_mode_init(DMA0, DMA_CH5, &dma_init_struct);
		dma_circulation_disable(DMA0, DMA_CH5);
		dma_channel_subperipheral_select(DMA0, DMA_CH5, DMA_SUBPERI4);
		dma_channel_enable(DMA0, DMA_CH5);
	}
	return len;
}


/*****************************************UART2_LiDAR********************************************/

//D9->AF7->TX->DMA0_CH3_PERIEN4    D8->AF7->RX->DMA0_CH1_PERIEN_4
void UART2_F450::Init(uint32_t baud)
{
	rcu_periph_clock_enable(RCU_DMA0);
	rcu_periph_clock_enable(RCU_USART2);
	rcu_periph_clock_enable(RCU_GPIOD);
	
	gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_8|GPIO_PIN_9);
	gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_8|GPIO_PIN_9);
	gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_8|GPIO_PIN_9);
	
	usart_deinit(USART2);
	usart_oversample_config(USART2, USART_OVSMOD_8);
	usart_baudrate_set(USART2,baud);			          
	usart_parity_config(USART2, USART_PM_NONE);		  
	usart_word_length_set(USART2, USART_WL_8BIT);
	usart_stop_bit_set(USART2, USART_STB_1BIT);
	usart_receive_config(USART2, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
//	usart_interrupt_enable(USART2, USART_INT_IDLE);
	
	nvic_irq_enable(USART2_IRQn, 2, 1);
	usart_enable(USART2);
	usart_dma_receive_config(USART2, USART_DENR_ENABLE);
	usart_dma_transmit_config(USART2, USART_DENT_ENABLE);
	
	nvic_irq_enable(DMA0_Channel1_IRQn, 2, 1);
  nvic_irq_enable(DMA0_Channel3_IRQn, 2, 1);
	dma_single_data_parameter_struct dma_init_struct;
	dma_single_data_para_struct_init(&dma_init_struct);
	
	//TX
	dma_deinit(DMA0, DMA_CH3);
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)0;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = 0;
	dma_init_struct.periph_addr = USART2_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH3, &dma_init_struct);
	dma_circulation_disable(DMA0, DMA_CH3);
	dma_channel_subperipheral_select(DMA0, DMA_CH3, DMA_SUBPERI4);
	dma_interrupt_enable(DMA0, DMA_CH3, DMA_CHXCTL_FTFIE);
	dma_channel_enable(DMA0, DMA_CH3);
	
	//RX
	dma_deinit(DMA0, DMA_CH1);
	dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
	dma_init_struct.memory0_addr = (uint32_t)RxBuf;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.number = 32;
	dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART2);
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH1, &dma_init_struct);
	dma_circulation_disable(DMA0, DMA_CH1);
	dma_channel_subperipheral_select(DMA0, DMA_CH1, DMA_SUBPERI4);
	dma_interrupt_enable(DMA0, DMA_CH1, DMA_CHXCTL_FTFIE);
	dma_channel_enable(DMA0, DMA_CH1);
}

//D9->AF7->TX->DMA0_CH3_PERIEN4    D8->AF7->RX->DMA0_CH1_PERIEN_4
void UART2_F450::Write(uint8_t *buf, uint16_t len)
{
	dma_single_data_parameter_struct dma_init_struct;
	
	dma_single_data_para_struct_init(&dma_init_struct);
	dma_deinit(DMA0, DMA_CH3);
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)buf;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = len;
	dma_init_struct.periph_addr = USART2_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH3, &dma_init_struct);
	dma_channel_subperipheral_select(DMA0, DMA_CH3, DMA_SUBPERI4);
	dma_channel_enable(DMA0, DMA_CH3);
	while(!dma_flag_get(DMA0,DMA_CH3,DMA_FLAG_FTF));
}

uint16_t UART2_F450::GetRxLenth(void)
{
	return 32-dma_transfer_number_get(DMA0, DMA_CH1);
}

uint16_t UART2_F450::Read(uint8_t *buf)
{
	uint16_t len = 0;
	
	len = 32-dma_transfer_number_get(DMA0, DMA_CH1);
	if(len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			buf[i] = RxBuf[i];
		}
		dma_single_data_parameter_struct dma_init_struct;
		dma_deinit(DMA0, DMA_CH1);
		dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
		dma_init_struct.memory0_addr = (uint32_t)RxBuf;
		dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
		dma_init_struct.number = 32;
		dma_init_struct.periph_addr = (uint32_t)&USART_DATA(USART2);
		dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
		dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
		dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
		dma_single_data_mode_init(DMA0, DMA_CH1, &dma_init_struct);
		dma_circulation_disable(DMA0, DMA_CH1);
		dma_channel_subperipheral_select(DMA0, DMA_CH1, DMA_SUBPERI4);
		dma_channel_enable(DMA0, DMA_CH1);
	}
	return len;
}


