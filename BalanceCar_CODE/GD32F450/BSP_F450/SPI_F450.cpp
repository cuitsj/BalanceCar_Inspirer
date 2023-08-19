#include "SPI_F450.hpp"
#include "main.h"
 
 
void SPI1_F450::Init(void)
{
	/* peripheral clock enable */
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_DMA0);
	rcu_periph_clock_enable(RCU_SPI1);
	/* GPIO config */
	/* SPI1 GPIO config */
	/* SPI1_CLK(PB13), SPI1_MISO(PB14) */
	/* SPI1_CLK(PB13), SPI1_MISO(PB14) */
	gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_13|GPIO_PIN_14);
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13|GPIO_PIN_14);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13|GPIO_PIN_14);
 
	dma_single_data_parameter_struct dma_init_struct;
	/* DMA config */
	dma_deinit(DMA0,DMA_CH3);
	dma_init_struct.periph_addr         = (uint32_t)&SPI_DATA(SPI1);
	dma_init_struct.memory0_addr        = (uint32_t)0;
	dma_init_struct.direction           = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.priority            = DMA_PRIORITY_LOW;
	dma_init_struct.number              = 0;
	dma_init_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.circular_mode       = DMA_CIRCULAR_MODE_DISABLE;
	dma_single_data_mode_init(DMA0,DMA_CH3,&dma_init_struct);
	dma_channel_subperipheral_select(DMA0,DMA_CH3,DMA_SUBPERI3);
 
	/* SPI config */
	spi_parameter_struct spi_init_struct;
 
	/* SPI1 parameter config */
	spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
	spi_init_struct.device_mode          = SPI_MASTER;
	spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
	spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
	spi_init_struct.nss                  = SPI_NSS_SOFT;
	spi_init_struct.prescale             = SPI_PSC_32;
	spi_init_struct.endian               = SPI_ENDIAN_MSB;
	spi_init(SPI1, &spi_init_struct);
 
	spi_crc_polynomial_set(SPI1, 10);
	
	/* SPI enable */
	spi_enable(SPI1);
 
	/* DMA channel enable */
		dma_channel_enable(DMA0,DMA_CH3);
 
	/* SPI DMA enable */
	spi_dma_enable(SPI1, SPI_DMA_TRANSMIT);
//	while(!dma_flag_get(DMA1,DMA_CH3,DMA_FLAG_FTF));
}
void SPI1_F450::Write(uint8_t *buf, uint16_t len)
{
	dma_single_data_parameter_struct dma_init_struct;
	/* DMA config */
	dma_deinit(DMA0,DMA_CH3);
	dma_init_struct.periph_addr         = (uint32_t)&SPI_DATA(SPI1);
	dma_init_struct.memory0_addr        = (uint32_t)buf;
	dma_init_struct.direction           = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.priority            = DMA_PRIORITY_LOW;
	dma_init_struct.number              = len;
	dma_init_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.circular_mode       = DMA_CIRCULAR_MODE_DISABLE;
	dma_single_data_mode_init(DMA0,DMA_CH3,&dma_init_struct);
	dma_channel_subperipheral_select(DMA0,DMA_CH3,DMA_SUBPERI3);
 
	/* DMA channel enable */
	dma_channel_enable(DMA0,DMA_CH3);
	while(!dma_flag_get(DMA0,DMA_CH3,DMA_FLAG_FTF));
 
}
 
void SPI1_F450::Read(uint8_t *buf, uint16_t *len)
{
}
