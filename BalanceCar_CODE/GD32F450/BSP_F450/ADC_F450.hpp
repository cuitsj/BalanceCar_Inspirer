#pragma once
 
#include <stdint.h>

class ADC
{
    public:
		ADC(){}
		
    uint32_t adcValue[4];
		float VOLIN4_BAT;
		float VOLIN5_12V;
		float VOLIN6_5V;
		float VOLIN7_GD3V3;
    virtual void Init(void){}
    virtual void PeriodRun(){}
};

class ADC0_F450:public ADC
{
    public:
    ADC0_F450(){}
	 void Init(void);
	 void PeriodRun();
};