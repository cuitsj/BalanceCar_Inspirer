#include "IIC_F450.hpp"
#include "main.h"

#define I2C0_SLAVE_ADDRESS7    0x82
#define I2C1_SLAVE_ADDRESS7    0x72
#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))
#define I2C0_DATA_ADDRESS        0x40005410
#define I2C1_DATA_ADDRESS        0x40005810
#define BUFFER_SIZE             (ARRAYNUM(i2c1_buff_tx)-1)
uint8_t i2c1_buff_tx[] = "I2C DMA test";
uint8_t i2c0_buff_rx[BUFFER_SIZE];

void IIC0_F450::Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_I2C0);
	rcu_periph_clock_enable(RCU_DMA0);

	gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_8|GPIO_PIN_9);
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8|GPIO_PIN_9);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_8|GPIO_PIN_9);
	
	/* configure I2C0 clock */
	i2c_clock_config(I2C0, 100000, I2C_DTCY_2);
	/* configure I2C0 address */
	i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C0_SLAVE_ADDRESS7);
	/* enable I2C0 */
	i2c_enable(I2C0);
	/* enable acknowledge */
	i2c_ack_config(I2C0, I2C_ACK_ENABLE);

	dma_single_data_parameter_struct dma_init_struct;
	/* TX */
	dma_deinit(DMA0, DMA_CH6);

	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)0;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = 0;
	dma_init_struct.periph_addr = I2C0_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH6, &dma_init_struct);
	
	/* configure DMA mode */
	dma_circulation_disable(DMA0, DMA_CH6);
	dma_channel_subperipheral_select(DMA0, DMA_CH6, DMA_SUBPERI1);
		
	/* RX */
	dma_deinit(DMA0, DMA_CH0);
	dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
	dma_init_struct.memory0_addr = (uint32_t)0;
	dma_init_struct.periph_addr = I2C0_DATA_ADDRESS;
	dma_init_struct.priority = DMA_PRIORITY_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH0, &dma_init_struct);
	
	/* configure DMA mode */
	dma_circulation_disable(DMA0, DMA_CH0);
	dma_channel_subperipheral_select(DMA0, DMA_CH0, DMA_SUBPERI1);
}
void IIC0_F450::Write(uint8_t Slave_Address,uint8_t len,uint8_t *Data_tx)
{
	while(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY));
	i2c_start_on_bus(I2C0);
	while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
  i2c_master_addressing(I2C0, Slave_Address, I2C_TRANSMITTER);
	i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
	
	dma_single_data_parameter_struct dma_init_struct;
	/* initialize DMA0 channe6 */
	dma_deinit(DMA0, DMA_CH6);

	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)Data_tx;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = len;
	dma_init_struct.periph_addr = I2C0_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH6, &dma_init_struct);
	
	i2c_dma_enable(I2C0, I2C_DMA_ON);
	dma_channel_enable(DMA0, DMA_CH6);
	while(!dma_flag_get(DMA0, DMA_CH6, DMA_FLAG_FTF));
	i2c_stop_on_bus(I2C0);
	while(I2C_CTL0(I2C0)&0x0200);
  while(!i2c_flag_get(I2C0, I2C_FLAG_STPDET));
}
 
void IIC0_F450::Read(uint8_t Slave_Address,uint8_t *Data_rx)
{
	while(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY));
	i2c_start_on_bus(I2C0);
	while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
  i2c_master_addressing(I2C0, Slave_Address, I2C_TRANSMITTER);
	i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
	 
	dma_single_data_parameter_struct dma_init_struct;
	/* initialize DMA0 channe6 */
	 /* initialize DMA0 channe2 */
	dma_deinit(DMA0, DMA_CH0);
	dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
	dma_init_struct.memory0_addr = (uint32_t)Data_rx;
	dma_init_struct.periph_addr = I2C0_DATA_ADDRESS;
	dma_init_struct.priority = DMA_PRIORITY_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH0, &dma_init_struct);
	
	i2c_dma_enable(I2C0, I2C_DMA_ON);
	dma_channel_enable(DMA0, DMA_CH0);
	while(!dma_flag_get(DMA0, DMA_CH0, DMA_FLAG_FTF));
	i2c_stop_on_bus(I2C0);
	while(I2C_CTL0(I2C0)&0x0200);
  while(!i2c_flag_get(I2C0, I2C_FLAG_STPDET));
}


void IIC1_F450::Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_I2C1);
	rcu_periph_clock_enable(RCU_DMA0);

	gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_10|GPIO_PIN_11);
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10|GPIO_PIN_11);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10|GPIO_PIN_11);
	
	/* configure I2C0 clock */
	i2c_clock_config(I2C1, 100000, I2C_DTCY_2);
	/* configure I2C0 address */
	i2c_mode_addr_config(I2C1, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, I2C0_SLAVE_ADDRESS7);
	/* enable I2C0 */
	i2c_enable(I2C1);
	/* enable acknowledge */
	i2c_ack_config(I2C1, I2C_ACK_ENABLE);

	dma_single_data_parameter_struct dma_init_struct;
	/* TX */
	dma_deinit(DMA0, DMA_CH7);

	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)0;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = 0;
	dma_init_struct.periph_addr = I2C1_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH7, &dma_init_struct);
	
	/* configure DMA mode */
	dma_circulation_disable(DMA0, DMA_CH7);
	dma_channel_subperipheral_select(DMA0, DMA_CH7, DMA_SUBPERI7);
		
	/* RX */
	dma_deinit(DMA0, DMA_CH2);
	dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
	dma_init_struct.memory0_addr = (uint32_t)0;
	dma_init_struct.periph_addr = I2C1_DATA_ADDRESS;
	dma_init_struct.priority = DMA_PRIORITY_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH2, &dma_init_struct);
	
	/* configure DMA mode */
	dma_circulation_disable(DMA0, DMA_CH2);
	dma_channel_subperipheral_select(DMA0, DMA_CH2, DMA_SUBPERI7);
}
void IIC1_F450::Write(uint8_t Slave_Address,uint8_t len,uint8_t *Data_tx)
{
	while(i2c_flag_get(I2C1, I2C_FLAG_I2CBSY));
	i2c_start_on_bus(I2C1);
	while(!i2c_flag_get(I2C1, I2C_FLAG_SBSEND));
  i2c_master_addressing(I2C1, Slave_Address, I2C_TRANSMITTER);
	i2c_flag_clear(I2C1, I2C_FLAG_ADDSEND);
	
	dma_single_data_parameter_struct dma_init_struct;
	/* initialize DMA0 channe6 */
	dma_deinit(DMA0, DMA_CH7);

	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.memory0_addr = (uint32_t)Data_tx;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.number = len;
	dma_init_struct.periph_addr = I2C1_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
	dma_single_data_mode_init(DMA0, DMA_CH7, &dma_init_struct);
	
	i2c_dma_enable(I2C1, I2C_DMA_ON);
	dma_channel_enable(DMA0, DMA_CH7);
	while(!dma_flag_get(DMA0, DMA_CH7, DMA_FLAG_FTF));
	i2c_stop_on_bus(I2C1);
	while(I2C_CTL0(I2C1)&0x0200);
  while(!i2c_flag_get(I2C1, I2C_FLAG_STPDET));
}
 
void IIC1_F450::Read(uint8_t Slave_Address,uint8_t *Data_rx)
{
	
}
