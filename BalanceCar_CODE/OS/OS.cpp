#include "OS.hpp"
#include "main.h"

void OS::Init()
{
	key_flag=0;
	flag_gyz=0;
	thread_SCREEN = RT_NULL;
	thread_BALANCE = RT_NULL;
	thread_MUSIC = RT_NULL;
	thread_MPU = RT_NULL;
}

void OS::thread_start(rt_thread_t thread_id)
{  
	if (thread_id != RT_NULL) rt_thread_startup(thread_id);
}
void OS::delete_thread(rt_thread_t thread_id)
{
	if (thread_id != RT_NULL) rt_thread_delete(thread_id);
}
rt_thread_t OS::newthread(TASK *task)
{
	return rt_thread_create(task->name, (mainFun_t)task->func, RT_NULL, task->stackSize, task->thread_prioroty, 1);
}
void OS::delay_ms(uint64_t timeout)
{
	rt_thread_mdelay(timeout);
}

void OS::delay_us(uint64_t timeout)
{
	rt_thread_delay(timeout);
}

void OS::create_timer(TIMER *timer)
{
    timer->timer_id = rt_timer_create(timer->name, (timeout_func)timer->func,RT_NULL, timer->time,timer->flag);
}

void OS::timer_start(TIMER *timer)
{
	if (timer->timer_id != RT_NULL) rt_timer_start(timer->timer_id);
}

void OS::timer_stop(TIMER *timer)
{
	if (timer->timer_id != RT_NULL) rt_timer_stop(timer->timer_id);
}



