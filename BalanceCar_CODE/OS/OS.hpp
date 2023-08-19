#pragma once 
#include <stdint.h>
#include <rtthread.h>

typedef void (*mainFun_t)(void *); 
typedef void (*timeout_func)(void *);           /* ³¬Ê±º¯Êý */

class TASK
{
	 public:
	 mainFun_t func;
	 const char *name;
	 uint16_t stackSize;
	 uint8_t thread_prioroty;		 
};

class TIMER
{
	public:
	rt_timer_t timer_id;
	timeout_func func;
	const char *name;
	uint32_t   time;
	uint8_t  flag;		
};

class OS
{
    public:
		bool key_flag;
		bool flag_gyz;
		rt_thread_t thread_SCREEN;
		rt_thread_t thread_BALANCE;
		rt_thread_t thread_MUSIC;
		rt_thread_t thread_MPU;
    void Init();
    void start(void);
    void stop(void);
		void create_timer(TIMER *timer);
		void timer_start(TIMER *timer);
		void timer_stop(TIMER *timer);
    rt_thread_t newthread(TASK *task);
		void thread_start(rt_thread_t thread_id);
		void delete_thread(rt_thread_t thread_id);
    void delay_ms(uint64_t timeout);
		void delay_us(uint64_t timeout);
};
