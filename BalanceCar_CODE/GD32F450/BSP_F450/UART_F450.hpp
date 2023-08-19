#pragma once

#include <stdint.h>

class UART
{
    public:
			virtual void Init(uint32_t baud = 115200){}
			virtual void Write(uint8_t *buf, uint16_t len){}
			virtual uint16_t Read(uint8_t *buf){}
			virtual uint16_t GetRxLenth(void){}
			uint8_t RxBuf[32];
			uint8_t TxBuf[32];
};
 
class UART0_F450: public UART
{
public:
	UART0_F450(){}
	void Init(uint32_t baud = 115200);
	void Write(uint8_t *buf, uint16_t len);
	uint16_t Read(uint8_t *buf);
	uint16_t GetRxLenth(void);		
};

class UART1_F450: public UART
{
public:
	UART1_F450(){}
	void Init(uint32_t baud = 115200);
	void Write(uint8_t *buf, uint16_t len);
	uint16_t Read(uint8_t *buf);
	uint16_t GetRxLenth(void);		
};

class UART2_F450: public UART
{
public:
	UART2_F450(){}
	void Init(uint32_t baud = 115200);
	void Write(uint8_t *buf, uint16_t len);
	uint16_t Read(uint8_t *buf);
	uint16_t GetRxLenth(void);		
};
