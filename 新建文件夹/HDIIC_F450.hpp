#pragma once
 
#include <stdint.h>
 
class IIC
{
    public:
    IIC(){}
    virtual void Init(void){}
    virtual void Write(uint8_t Slave_Address,uint8_t len,uint8_t *Data_tx){}
    virtual void Read(uint8_t SlaveAddress,uint8_t *Data){}
};
 
class IIC0_F450 : public IIC
{
public:
    IIC0_F450() {}
    void Init(void);
    void Write(uint8_t Slave_Address,uint8_t len,uint8_t *Data_tx);
    void Read(uint8_t SlaveAddress,uint8_t *Data_rx);
};

class IIC1_F450 : public IIC
{
public:
    IIC1_F450() {}
    void Init(void);
    void Write(uint8_t Slave_Address,uint8_t len,uint8_t *Data_tx);
    void Read(uint8_t SlaveAddress,uint8_t *Data_rx);
};