#pragma once

#include <stdint.h>

class TIM
{
    public:
    TIM(){}
    uint16_t fullPwm;
    uint16_t pwmfq;
    virtual void Init(void){}
    virtual void SetDUTY(int16_t duty){}
		virtual void SetFREQ(float freq){}
		virtual int16_t ReadCnt(void){}
};

class TIM0_F450 : public TIM
{
	private:
		uint8_t motor_id;
	public:
			TIM0_F450(uint8_t motor_id);
			void Init(void);
			void SetDUTY(int16_t duty);
};

class TIM8_F450 : public TIM
{
public:
    TIM8_F450() {}
    void Init(void);	
    void SetDUTY(int16_t duty);
		void SetFREQ(float freq);
};

class TIM2_F450 : public TIM
{
public:
	TIM2_F450(){}
	void Init(void);	
	int16_t ReadCnt(void);
};

class TIM3_F450 : public TIM
{
public:
	TIM3_F450(){}
	void Init(void);	
	int16_t ReadCnt(void);
};