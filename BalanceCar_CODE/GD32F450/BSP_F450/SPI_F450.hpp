#pragma once
 
#include <stdint.h>
 
class SPI
{
    public:
    SPI(){}
    virtual void Init(void){}
    virtual void Write(uint8_t *buf, uint16_t len){}
    virtual void Read(uint8_t *buf, uint16_t *len){}
};
 
class SPI1_F450 : public SPI
{
public:
    SPI1_F450() {}
    void Init(void);
    void Write(uint8_t *buf, uint16_t len);
    void Read(uint8_t *buf, uint16_t *len);
};