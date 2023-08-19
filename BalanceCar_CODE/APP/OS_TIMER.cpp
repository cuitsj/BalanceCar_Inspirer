#include "OS_TIMER.hpp"

extern OS_Timer1 *gOS_Timer1;

void OS_Timer1::OS_Timer1_FUN(void* parameter)
{
	gOS->key_flag=0;
	gOS->timer_stop(gOS_Timer1);
}

OS_Timer1::OS_Timer1()
{
	func = (timeout_func)OS_Timer1_FUN;
	name = "TIMER1";
	time = 500;//500ms
	flag = RT_TIMER_FLAG_PERIODIC;//RT_TIMER_FLAG_ONE_SHOT
}