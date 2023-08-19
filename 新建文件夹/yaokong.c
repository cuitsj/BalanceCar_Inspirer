//void TASK_BALANCE::BALANCE_FUN(void* parameter)
//{
//	bool dec_flag = 0;
//	bool inc_flag = 0;
//	uint8_t rxdata = 0;
//	uint16_t len = 0;
//	int16_t set_speed = 30;
//	int16_t Lset_speed = 0;	//目标速度
//	int16_t Rset_speed = 0;	//目标速度
//	int16_t Lnow_speed = 0;		//当前速度
//	int16_t Rnow_speed = 0;
//	int16_t Lnow_err = 0;			//当前误差
//	int16_t Rnow_err = 0;			//当前误差
//	int16_t Llast1_err = 0;		//上次误差
//	int16_t Rlast1_err = 0;		//上次误差
//	int16_t Llast2_err = 0;		//上上次误差
//	int16_t Rlast2_err = 0;		//上上次误差
//	int16_t Left_duty = 0;		//输出占空比
//	int16_t Right_duty = 0;
//	
//	for(;;)
//	{
//		/*****************************************手机遥控*****************************************/
//		if (gBSP->UART1_BT->GetRxLenth() >=  1)
//		{
//			gBSP->UART1_BT->Read(&rxdata);
//		}
//		switch (rxdata)
//		{
//			//前进
//			case 0x11:
//				dec_flag=0;
//				inc_flag=0;
//				Lset_speed = set_speed;
//				Rset_speed = set_speed;
//				break;
//			//后退
//			case 0x22:
//				dec_flag=0;
//				inc_flag=0;
//				Lset_speed = -set_speed;
//				Rset_speed = -set_speed;
//				break;
//			//左转
//			case 0x33:
//				dec_flag=0;
//				inc_flag=0;
//				Lset_speed = -set_speed;
//				Rset_speed = set_speed;
//				break;
//			//右转
//			case 0x44:
//				dec_flag=0;
//				inc_flag=0;
//				Lset_speed = set_speed;
//				Rset_speed = -set_speed;
//				break;
//			//加速
//			case 0x55:
//				if(inc_flag == 0)
//				{
//					inc_flag=1;
//					set_speed=set_speed+10;
//					if(set_speed>80)set_speed=80;
//				}
//				break;
//			//减速
//			case 0x66:
//				if (dec_flag == 0)
//				{
//					dec_flag=1;
//					set_speed=set_speed-10;
//					if(set_speed<0)set_speed=0;
//				}
//				break;
//			//停止
//			case 0x00:
//				dec_flag=0;
//				inc_flag=0;
//				Lset_speed = 0;
//				Rset_speed = 0;
//				break;
//			//停止
//			default:
//				Lset_speed = 0;
//				Rset_speed = 0;
//				break;
//		}

//		/*****************************************手机遥控*****************************************/
//		/*****************************************增量式PID速度控制*****************************************/
//		//1读取当前速度
//		Lnow_speed = gBSP->TIM3_LENCODER->ReadCnt();
//		Rnow_speed = gBSP->TIM2_RENCODER->ReadCnt();

//		//2计算当前误差
//		Lnow_err = (Lset_speed - Lnow_speed);
//		Rnow_err = (Rset_speed - Rnow_speed);
//		
//		//3迟滞消除扰动
//		if(Lnow_err<6&&Lnow_err>-6)
//		{
//			Lnow_err=0;
//		}
//		if(Rnow_err<6&&Rnow_err>-6)
//		{
//			Rnow_err=0;
//		}
//		
//		//4增量式PID
//		Left_duty +=  0.1*(Lnow_err-Llast1_err) + 0.8*Lnow_err + 0*(Lnow_err - 2*Llast1_err + Llast2_err);
//		Right_duty +=  0.1*(Rnow_err-Rlast1_err) + 0.8*Rnow_err + 0*(Rnow_err - 2*Rlast1_err + Rlast2_err);
//		
//		//5限幅
//		if (Left_duty > 900)
//		{
//			Left_duty = 900;
//		}
//		if (Left_duty < -900) 
//		{
//			Left_duty = -900; 
//		}
//		if (Right_duty > 900)
//		{
//			Right_duty = 900;
//		}
//		if (Right_duty < -900) 
//		{
//			Right_duty = -900; 
//		}
//		
//		//4记录上一次差
//		Llast2_err = Llast1_err;
//		Llast1_err = Lnow_err;
//		
//    //5输出
////		gBSP->TIM0_MOTORL->SetDUTY(Left_duty);
////		gBSP->TIM0_MOTORR->SetDUTY(Right_duty);
//		/*****************************************增量式PID速度控制*****************************************/
//		
//		/*****************************************DataScope*****************************************/

//	    		    				 
////		DataScope_Get_Channel_Data( Lset_speed , 1 );  //将数据 1.0  写入通道 1
////		DataScope_Get_Channel_Data( Lnow_speed , 2 );  //将数据 2.0  写入通道 2
////		DataScope_Get_Channel_Data( Lnow_err , 3 );  //将数据 3.0  写入通道 3
////		DataScope_Get_Channel_Data( Llast2_err , 4 );  //将数据 4.0  写入通道 4
////		DataScope_Get_Channel_Data( Left_duty , 5 );  //将数据 5.0  写入通道 5
////    
////		gBSP->UART2_BT->Write(DataScope_OutPut_Buffer,DataScope_Data_Generate(5));
//		
//		/*****************************************DataScope*****************************************/
//		gOS->delay_ms(10);
//	}
//}

//TASK_BALANCE::TASK_BALANCE()
//{
//	func = (mainFun_t)BALANCE_FUN;
//	stackSize = 1024;
//	name = "TASK_BALANCE";
//	thread_prioroty = 1;
//}

//float Med_Angle = 0;						//机械中值
//float Vertical_Kp = 20,		//直立环Kp
//	  Vertical_Kd = 0.03;		//直立环Kd

//float Velocity_Kp = 110,		//速度环Kp
//	  Velocity_Ki = 0.55;			//速度环Kd

//float Turn_Kp = 40,
//	  Turn_Kd = 0;

//int Vertical_out,Velocity_out,Turn_out;		//输出变量

//extern float Med_Angle;						//机械中值
//int measure;								//编码器速度测量值
//int motor1, motor2;

//int Vertical_PD(float measure, float Gyro);
//int Velocity_PI(int Speed_measure);
//int Turn(int gyro_Z);
//void Limit(int *motoA,int *motoB);