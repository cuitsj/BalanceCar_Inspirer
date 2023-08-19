#include "main.h"

#ifdef  GD32F450
	BSP_F450 BSP;
	BSP_F450 *gBSP = &BSP;
#else
#error "Please define your chip!"
#endif

OS iOS;
OS *gOS = &iOS;
OS_Timer1 iOS_Timer1;
OS_Timer1 *gOS_Timer1 = &iOS_Timer1;

TASK_SCREEN iTASK_SCREEN;
TASK_BALANCE iTASK_BALANCE;
TASK_MUSIC iTASK_MUSIC;
TASK_MPU iTASK_MPU;


//	/* 定时器 1 超时函数 */
//static void timeout1(void *parameter)
//{
//	rt_timer_stop(timer1);
//}

int main(void)
{
	gOS->Init();
	gBSP->Init();
	gOS->thread_SCREEN = gOS->newthread(&iTASK_SCREEN);
	gOS->thread_start(gOS->thread_SCREEN);
	gOS->thread_MUSIC = gOS->newthread(&iTASK_MUSIC);
	gOS->thread_start(gOS->thread_MUSIC);
	gOS->thread_BALANCE = gOS->newthread(&iTASK_BALANCE);
	gOS->thread_start(gOS->thread_BALANCE);
	gOS->thread_MPU = gOS->newthread(&iTASK_MPU);
	gOS->thread_start(gOS->thread_MPU);
	gOS->create_timer(gOS_Timer1);
//	gBSP->TIM1_LED->SetPWM(1,50);
	//gBSP->TIM0_MOTORR->SetPWM(200);
//gBSP->TIM0_MOTORR->SetPWM(500);
	for(;;)
	{
		gOS->delay_ms(1000);
	}
}
