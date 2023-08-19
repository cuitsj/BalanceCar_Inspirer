#include "TASK_SCREEN.hpp"


extern OS_Timer1 *gOS_Timer1;

void TASK_SCREEN::SCREEN_FUN(void* parameter)
{
		float t=0;
	bool flag_show = 0;
	bool flag_const = 1;
	bool flag_clear = 1;
	bool flag_close = 0;
	bool test = 0;
	bool vol_err = 0;
	uint8_t off_cnt = 0;
	uint8_t g_cnt = 0;
	uint8_t ch0[]="Vol Low!";
	uint8_t ch1[]="Vol Err!";
	
	LCD_Init();//LCD初始化
//	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	for(;;)
	{
		gBSP->ADC0_VOL->PeriodRun();
		
		//5V
		if (gBSP->ADC0_VOL->VOLIN6_5V<=4.5 || gBSP->ADC0_VOL->VOLIN6_5V>5.5)
		{
			vol_err = 1;
		}
		//GD3.3
		if (gBSP->ADC0_VOL->VOLIN7_GD3V3<=2.8||gBSP->ADC0_VOL->VOLIN7_GD3V3>3.8)
		{
			vol_err = 1;
		}
		if (gBSP->ADC0_VOL->VOLIN4_BAT<=10.7||vol_err == 1)//电池电压过低自动关机
		{
			//关掉其他线程
			if (flag_close == 0)
			{
				flag_close = 1;
				gOS->delete_thread(gOS->thread_MUSIC);
				gOS->delete_thread(gOS->thread_BALANCE);
				gBSP->LED_G->Set();
				gBSP->LED_B->Set();
				if (vol_err == 1)
				{
//					OLED_ShowString(64,4,ch1,8);	
				}
				else
				{
//					OLED_ShowString(64,4,ch0,8);	
				}
			}
			//OLED显示低电量
			flag_show = 1;
			//蜂鸣器鸣叫5秒钟，红灯闪烁
			gBSP->TIM8_BEEP->SetDUTY(99);
			gBSP->TIM8_BEEP->SetFREQ(988);
			gBSP->LED_R->Toggle();
			gOS->delay_ms(200);
			gBSP->TIM8_BEEP->SetDUTY(0);
			off_cnt++;
			//关机
			if (off_cnt == 25)//5s
			{
				off_cnt = 0;
				gBSP->LED_R->Set();
				gBSP->LED_G->Set();
				gBSP->LED_B->Set();
				if (vol_err == 0)
				{
					while(1);
				}
			}
		}
		else
		{
			g_cnt++;
			if (g_cnt == 2)
			{
				g_cnt = 0;
				gBSP->LED_B->Toggle();
			}	
		}
		if (!gBSP->KEY_MODE->Gets()&&gOS->key_flag==0)
		{
			while(!gBSP->KEY_MODE->Gets()&&gOS->key_flag==0);
			flag_show = !flag_show;
			gOS->key_flag=1;
			gOS->timer_start(gOS_Timer1);
		}
		if (flag_show)
		{
			//***************************TEST*******************************//
//				gBSP->TIM0_MOTORL->SetDUTY(-300);
			
			gBSP->flag_debug = 0;
			//***************************TEST*******************************//
			
			if (flag_const)
			{
//				show_const();
				flag_const=0;
				flag_clear=1;
			}
//			OLED_ShowNum(24,1,(uint32_t)(gBSP->ADC0_VOL->VOLIN5_12V)%10,1,8);
//			OLED_ShowNum(36,1,(uint32_t)(gBSP->ADC0_VOL->VOLIN5_12V*10)%10,1,8);
//			OLED_ShowNum(42,1,(uint32_t)(gBSP->ADC0_VOL->VOLIN5_12V*100)%10,1,8);
//			OLED_ShowNum(24,4,(uint32_t)(gBSP->ADC0_VOL->VOLIN6_5V)%10,1,8);
//			OLED_ShowNum(36,4,(uint32_t)(gBSP->ADC0_VOL->VOLIN6_5V*10)%10,1,8);
//			OLED_ShowNum(42,4,(uint32_t)(gBSP->ADC0_VOL->VOLIN6_5V*100)%10,1,8);
//			OLED_ShowNum(88,1,(uint32_t)(gBSP->ADC0_VOL->VOLIN7_GD3V3)%10,1,8);
//			OLED_ShowNum(100,1,(uint32_t)(gBSP->ADC0_VOL->VOLIN7_GD3V3*10)%10,1,8);
//			OLED_ShowNum(106,1,(uint32_t)(gBSP->ADC0_VOL->VOLIN7_GD3V3*100)%10,1,8);
//			OLED_ShowNum(88,2,(uint32_t)(gBSP->ADC0_VOL->VOLIN4_BAT)/10,1,8);
//			OLED_ShowNum(94,2,(uint32_t)(gBSP->ADC0_VOL->VOLIN4_BAT)%10,1,8);
//			OLED_ShowNum(106,2,(uint32_t)(gBSP->ADC0_VOL->VOLIN4_BAT*10)%10,1,8);
//			OLED_ShowNum(112,2,(uint32_t)(gBSP->ADC0_VOL->VOLIN4_BAT*100)%10,1,8);
		}
		else
		{
			gBSP->flag_debug = 1;
			if (flag_clear)
			{
				flag_const=1;
				flag_clear = 0;
//				OLED_Clear(0);
			}
		}
		if (!gBSP->KEY_MODE->Gets()&&gOS->key_flag==1)
		{
			while(!gBSP->KEY_MODE->Gets());
			gOS->flag_gyz = !gOS->flag_gyz;
			flag_show = !flag_show;
		}
		


//		LCD_ShowIntNum(106,33,LCD_W,3,RED,WHITE,32);

//		LCD_ShowIntNum(106,66,LCD_H,3,RED,WHITE,32);
//		LCD_ShowFloatNum1(10,99,t,4,RED,WHITE,32);
//		t+=0.11;
		LCD_ShowPicture(160,95,40,40,gImage_1);
		
		gOS->delay_ms(5);
	}
}

TASK_SCREEN::TASK_SCREEN()
{
	func = (mainFun_t)SCREEN_FUN;
	stackSize = 1024;
	name = "TASK_SCREEN";
	thread_prioroty = 1;
}