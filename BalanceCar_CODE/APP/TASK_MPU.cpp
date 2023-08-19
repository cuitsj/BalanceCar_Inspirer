#include "TASK_MPU.hpp"

#include "mpu9250.hpp"


void TASK_MPU::MPU_FUN(void* parameter)
{
//	float pitch,roll,yaw;
//	int PWM_out;
//	int Voltage;
//	int16_t Encoder_Left=0,Encoder_Right=0;
//	uint8_t t[20]={0};
//	
////	MPU_Init();
////	mpu_dmp_init();
//	MPU9250_Init();
//	MPU9250_Init();
//	DMP_Init();
	for(;;)
	{
//	        //===倾倒停车
// 		gBSP->TIM0_MOTORL->SetDUTY(Moto1);
//		gBSP->TIM0_MOTORR->SetDUTY(Moto1);			//===赋值给PWM寄存器 
			
//		MPU_Get_Gyroscope();
//		MPU_Get_Accelerometer();
//		MPU_Get_Temperature();
//		MPU_Get_Magnetometer();
//		AHRSupdate(gyro[0],gyro[1],gyro[2],accel[0],accel[1],accel[2],magnet[0],magnet[1],magnet[2],&roll,&pitch,&yaw);
//				
//		
////		Voltage=gBSP->ADC0_VOL->VOLIN4_BAT;

//		t[0] = (uint16_t)roll>>8;
//		t[1] = (uint16_t)roll;
//		t[2] = (uint16_t)pitch>>8;
//		t[3] = (uint16_t)pitch;
////		t[4] = (uint16_t)yaw>>8;
////		t[5] = (uint16_t)yaw;
////		t[6] = gyro[0]>>8;
////		t[7] = gyro[0];
////		t[8] = gyro[1]>>8;
////		t[9] = gyro[1];
////		t[10] = gyro[2]>>8;
////		t[11] = gyro[2];
////		t[12] = magnet[0]>>8;
////		t[13] = magnet[0];
////		t[14] = magnet[1]>>8;
////		t[15] = magnet[1];
////		t[16] = magnet[2]>>8;
////		t[17] = magnet[2];
////				t[12] = Temperature>>8;
////				t[13] = Temperature;
////				t[14] = BUF[0];
////				t[15] = BUF[1];
////				t[16] = BUF[2];
////				t[17] = BUF[3];
////				t[18] = BUF[4];
////				t[19] = BUF[5];
////				t[14] = Encoder_Left>>8;
////				t[15] = Encoder_Left;
////				t[16] = Encoder_Right>>8;
////				t[17] = Encoder_Right;
////				t[18] = Voltage>>8;
////				t[19] = Voltage;

//				//===读取编码器的值
//			Encoder_Left = gBSP->TIM3_LENCODER->ReadCnt();
//			Encoder_Right = gBSP->TIM2_RENCODER->ReadCnt();
//			
////			measure = (Encoder_Left + Encoder_Right);		//将编码器速度给测量值
////			mpu_dmp_get_data(&Pitch, &Roll, &Yaw);				//角度
////			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);			//角速度
//			
////			Vertical_out = Vertical_PD(Pitch, gyroy);				//直立环计算
////			Velocity_out = Velocity_PI(measure);				//速度环计算
////			Turn_out = Turn(gyroz);
//			
////			PWM_out = Vertical_out + Velocity_out;				//PWM输出
////			motor1 = PWM_out - Turn_out;
////			motor2 = PWM_out + Turn_out;
////			Limit(&motor1, &motor2);							//PWM限幅
////			if(Turn_Off(Pitch) == 0)
//			
//			
//			
//			
////				t[14] = Encoder_Left>>8;
////				t[15] = Encoder_Left;
////				t[16] = Encoder_Right>>8;
////				t[17] = Encoder_Right;
//			


////		gBSP->TIM0_MOTORL->SetDUTY(motor1);
////		gBSP->TIM0_MOTORR->SetDUTY(motor2);			//===赋值给PWM寄存器  
////			
//		gBSP->UART0_DEBUG->Write(t,4);
		gOS->delay_ms(5);
	}
	
}

TASK_MPU::TASK_MPU()
{
	func = (mainFun_t)MPU_FUN;
	stackSize = 1024;
	name = "TASK_MPU";
	thread_prioroty = 1;
}
