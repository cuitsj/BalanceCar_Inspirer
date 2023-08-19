#pragma once

#include <stdint.h>

class IO
{
    public:
    IO(){}
		virtual void Set_level(bool level){}
    virtual void Set(void){}
    virtual void Reset(void){}
    virtual void Toggle(void){}
    virtual uint8_t Gets(void){return 0;}
    virtual void Init(void){}   
};

class IO_F450: public IO
{   
    private:
    uint32_t GPIOx;
    uint32_t io_pin;
    
    public:
    IO_F450(uint32_t _GPIOx, uint32_t _io_pin);
		void Set_level(bool level);
    void Set(void);
    void Reset(void);
    void Toggle(void);
    uint8_t Gets(void);
    void Init(void);   
};