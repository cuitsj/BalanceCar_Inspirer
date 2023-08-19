#include "TASK_BALANCE.hpp"


#define Zero_Angle 2.0f	// 蓝色电池
#define AcceRatio 	16384.0f
#define GyroRatio 	16.4f
#define Gyro_Gr		0.0010653	// 角速度变成弧度	此参数对应陀螺2000度每秒
#define ACC_FILTER_NUM 5		// 加速度计滤波深度
#define GYRO_FILTER_NUM 1		// 陀螺仪滤波深度

PID MOTOR_PID, Angle_PID, Ang_Vel_PID, Direct_PID, Turn_PID, Distance_PID;	//定义舵机和电机的PID参数结构体
float MOTOR[4]   = {25, 40/200, 40, 500};		// 速度环PID	最后一项为积分限幅
float Angle[4]   = {0.3, 0, 0.1, 500};		// 角度环PID
float Ang_Vel[4] = {0.25, 0.025, 0, 1000};		// 角速度环PID
float Direct[4]  = {0.017, 0.001, 0.023, 70};	// 转向环PID 位置	0.017	0.02
float Turn[5][4] = {{100, 7, 7, 400},	// 130	// 转向外环动态PID	中线法
					{100, 8, 8, 400},	// 140
					{100, 8, 8, 400},	// 150
					{100, 9, 9, 400},	// 160
					{100, 10, 10, 400}};	// 170

int32_t Speed_Left=0,Speed_Right=0;
int32_t Tar_Ang_Vel=0,Target_Angle=0;
int32_t ACC_X_BUF[ACC_FILTER_NUM], ACC_Y_BUF[ACC_FILTER_NUM], ACC_Z_BUF[ACC_FILTER_NUM];	// 滤波缓存数组
int32_t GYRO_X_BUF[GYRO_FILTER_NUM], GYRO_Y_BUF[GYRO_FILTER_NUM], GYRO_Z_BUF[GYRO_FILTER_NUM];
int16_t gyro_real[3],accel_real[3];
	  			/* 各种标志位，放定时器中进行时序控制 */
char Speed_Flag, Angle_Flag, Ang_Velocity_Flag, DMP_Flag;

int32_t MOTOR_Duty_Left  = 0;
int32_t MOTOR_Duty_Right = 0;
					
int32_t 
	Speed_Now = 0,	// 当前实际速度
	Speed_Min = 0,	// 左右最小速度
	Speed_Set = 0, 	// 目标设定速度
	Theory_Duty = 0,// 理论直立占空比
	Vel_Set = 0,	// 目标转向角速度
	Direct_Parameter = 0,// 转向系数
	Direct_Last = 0,
	Radius = 0;		// 目标转向半径倒数

uint8_t Point = 80;
int32_t Difference = 0;

/*
 * 函数名：Data_Filter
 * 描述  ：数据滑动滤波
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Data_Filter(void)	// 数据滤波
{
	uint8_t i;
	float ACC_Angle;
	int64_t temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0, temp6 = 0;
	
	ACC_X_BUF[0] = accel[0];	// 更新滑动窗口数组
	ACC_Y_BUF[0] = accel[1];
	ACC_Z_BUF[0] = accel[2];
	GYRO_X_BUF[0] = gyro[0];
	GYRO_Y_BUF[0] = gyro[1];
	GYRO_Z_BUF[0] = gyro[2];
	
	for(i=0;i<ACC_FILTER_NUM;i++)
	{
		temp1 += ACC_X_BUF[i];
		temp2 += ACC_Y_BUF[i];
		temp3 += ACC_Z_BUF[i];
		
	}
	for(i=0;i<GYRO_FILTER_NUM;i++)
	{
		temp4 += GYRO_X_BUF[i];
		temp5 += GYRO_Y_BUF[i];
		temp6 += GYRO_Z_BUF[i];
	}
	
	accel_real[0] = temp1 / ACC_FILTER_NUM / AcceRatio;
	accel_real[1] = temp2 / ACC_FILTER_NUM / AcceRatio;
	accel_real[2] = temp3 / ACC_FILTER_NUM / AcceRatio;
	gyro_real[0] = temp4 / GYRO_FILTER_NUM / GyroRatio;
	gyro_real[1] = temp5 / GYRO_FILTER_NUM / GyroRatio;
	gyro_real[2] = temp6 / GYRO_FILTER_NUM / GyroRatio;
	
	for(i = 0; i < ACC_FILTER_NUM - 1; i++)
	{
		ACC_X_BUF[ACC_FILTER_NUM-1-i] = ACC_X_BUF[ACC_FILTER_NUM-2-i];
		ACC_Y_BUF[ACC_FILTER_NUM-1-i] = ACC_Y_BUF[ACC_FILTER_NUM-2-i];
		ACC_Z_BUF[ACC_FILTER_NUM-1-i] = ACC_Z_BUF[ACC_FILTER_NUM-2-i];
		
	}
	for(i = 0; i < GYRO_FILTER_NUM - 1; i++)
	{
		GYRO_X_BUF[GYRO_FILTER_NUM-1-i] = GYRO_X_BUF[GYRO_FILTER_NUM-2-i];
		GYRO_Y_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Y_BUF[GYRO_FILTER_NUM-2-i];
		GYRO_Z_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Z_BUF[GYRO_FILTER_NUM-2-i];
	}
}

// 增量式PID电机控制
int32_t PID_Increase(PID *sptr, float *PID, int32_t NowData, int32_t Point)
{
	//当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
	int32_t iError,	//当前误差
		Increase;	//最后得出的实际增量

	iError = Point - NowData;	// 计算当前误差

	Increase =  PID[KP] * (iError - sptr->LastError)
			  + PID[KI] * iError
			  + PID[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	// 更新前次误差
	sptr->LastError = iError;		  	// 更新上次误差
	sptr->LastData  = NowData;			// 更新上次数据
	
	return Increase;	// 返回增量
}

/******** 限幅保护 *********/
int32_t range_protect(int32_t duty, int32_t min, int32_t max)//限幅保护
{
	if (duty >= max)
	{
		return max;
	}
	if (duty <= min)
	{
		return min;
	}
	else
	{
		return duty;
	}
}

// 位置式PID控制
int32_t PID_Realize(PID *sptr, float *PID, int32_t NowData, int32_t Point)
{
	//当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
	int32_t iError,	// 当前误差
		 Realize;	// 最后得出的实际增量

	iError = Point - NowData;	// 计算当前误差
	sptr->SumError += PID[KI] * iError;	// 误差积分
	if (sptr->SumError >= PID[KT])
	{
		sptr->SumError = PID[KT];
	}
	else if (sptr->SumError <= -PID[KT])
	{
		sptr->SumError = -PID[KT];
	}

	Realize = PID[KP] * iError
			+ sptr->SumError
			+ PID[KD] * (iError - sptr->LastError);
	sptr->PrevError = sptr->LastError;	// 更新前次误差
	sptr->LastError = iError;		  	// 更新上次误差
	sptr->LastData  = NowData;			// 更新上次数据

	return Realize;	// 返回实际值
}

float Velocity_Kp = 50,		//速度环Kp
	  Velocity_Ki = 50/200;			//速度环Kd

//速度环PI
int Velocity_PI(int Speed_measure)
{
	static int Encoder_err, Encoder_err_low, Encoder_err_low_last, Encoder_sum, Movement;
	static int PWM_out;
	static float Target_Velocity = 200;
	
//	if(Flag_front == 1)			Movement = Target_Velocity / 2;
//	else if(Flag_back == 1)    	Movement = -Target_Velocity / 2;
//	else if(Flag_jingzhi == 1)	Movement = 0;
//	else if(1 == Flag_Quick)	Movement = Target_Velocity;

//	else 
		Movement = 0;
	
	Encoder_err = 0 - Speed_measure;
	Encoder_err_low = 0.3 * Encoder_err + 0.7 * Encoder_err_low_last;
	Encoder_err_low_last = Encoder_err_low;
	Encoder_sum += Encoder_err_low;
	Encoder_sum = Encoder_sum + Movement;
	if(Encoder_sum > 10000) Encoder_sum = 10000;
	if(Encoder_sum < -10000) Encoder_sum = -10000;
	
	PWM_out = Velocity_Kp*Encoder_err + Velocity_Ki*Encoder_sum;
	
//	if(Turn_Off(Pitch) == 1) Encoder_sum = 0;
		
	return PWM_out;
}
/********************* 串级平衡控制 *********************/
// 频率控制在定时器中设置
void Balance_Control(void)
{
	if (Ang_Velocity_Flag)	// 直立角速度环	2ms
	{
		Ang_Velocity_Flag = 0;
		
		MPU_Get_Gyroscope();
		MPU_Get_Accelerometer();		// 读取陀螺仪数据
		Data_Filter();					// 对原始数据滑动滤波												
												/* 角速度环作为最内环控制直立 */
		Theory_Duty += PID_Increase(&Ang_Vel_PID, Ang_Vel, (int32_t)(gyro_real[1]*10), (int32_t)(Tar_Ang_Vel));	// 计算直立PWM
		Theory_Duty = range_protect(Theory_Duty, -950, 950);
			
		if (0)
		{						/* 角速度环作为最内环控制转向 */									//Speed_Min
			Direct_Parameter = PID_Realize(&Direct_PID, Direct, (int32_t)(gyro_real[2]), 0);//Radius*Speed_Min);	// 转向环左正右负
			Direct_Parameter = range_protect(Direct_Parameter, -1200, 1200);
		}
		
		Direct_Last = Direct_Last*0.3 + Direct_Parameter*0.7;	// 更新上次角速度环结果
		
		MOTOR_Duty_Left  = Theory_Duty - Direct_Last;	// 左右电机根据转向系数调整差速
		MOTOR_Duty_Right = Theory_Duty + Direct_Last;	

//		gBSP->TIM0_MOTORL->SetDUTY(MOTOR_Duty_Left);
//		gBSP->TIM0_MOTORR->SetDUTY(MOTOR_Duty_Right);			//===赋值给PWM寄存器
		
		Read_DMP();	// 使用DMP直接读取欧拉角
	}
	
	if (Angle_Flag)		// 直立角度环	10ms
	{
		Angle_Flag = 0;
		
		//				//===读取编码器的值
			Speed_Left = gBSP->TIM3_LENCODER->ReadCnt();
			Speed_Right = gBSP->TIM2_RENCODER->ReadCnt();// 获取当前速度
		Speed_Now = (Speed_Left+Speed_Right)/2;
											/* 角度环加到角速度环上串级控制 */
		Tar_Ang_Vel = PID_Realize(&Angle_PID, Angle, (int32_t)(-Pitch*100), (int32_t)Target_Angle);	// 结果为放大10倍的目标角速度	
		Tar_Ang_Vel = range_protect(Tar_Ang_Vel, -1500, 1500);	// 注意正负号
	}
	if (Speed_Flag)		// 速度环	100ms
	{
		Speed_Flag = 0;
												/* 速度环加到角度环上串级控制 */
//		Target_Angle = Velocity_PI(Speed_Now);	// 结果为放大100倍的目标角度
		
		Target_Angle = -PID_Realize(&MOTOR_PID, MOTOR, Speed_Now, 0);	// 结果为放大100倍的目标角度
//		Target_Angle += Zero_Angle*100;	// 目标角度叠加在零点上
//		Target_Angle = range_protect((int32_t)Target_Angle, -1700, 800);	// -44 22

		Speed_Min = Speed_Min * 0.1 + Speed_Now * 0.9;
		if (Speed_Min < 40)
		{
			Speed_Min = 40;
		}
	}
}


void TASK_BALANCE::BALANCE_FUN(void* parameter)
{
	static uint8_t Time_10ms = 0;
	static uint8_t Time_50ms = 0;
	static uint8_t Time_100ms = 0;
	static uint8_t Time_200ms = 0;
	
	MPU9250_Init();
	DMP_Init();
	for(;;)
	{
		Time_10ms++;
		Time_50ms++;
		Time_100ms++;
		Time_200ms++;
	
//	if (Annulus_Delay)
//	{
//		Annulus_Delay--;
//	}
	
	Ang_Velocity_Flag = 1;	// 角速度2ms获取一次
	
	if (Time_10ms == 5)
	{
		Time_10ms = 0;
		Angle_Flag = 1;		// 姿态角度10ms控制一次	
	}
	
	if (Time_50ms == 25)
	{
		Time_50ms = 0;
		
//		Data_Send_Scope();//发送至Data_Scope上位机看波形
//		Data_Send_Status();//发送至匿名上位机看波形
	}
	
	if (Time_100ms == 50)
	{
		Time_100ms = 0;
		Speed_Flag = 1;	// 速度100ms控制一次
	}
	
	Balance_Control();	// 车身平衡控制
	
//		gBSP->TIM0_MOTORL->SetDUTY(motor1);
//		gBSP->TIM0_MOTORR->SetDUTY(motor2);			//===赋值给PWM寄存器  
//			
//		gBSP->UART0_DEBUG->Write(t,17);
		gOS->delay_ms(2);
	}
}

TASK_BALANCE::TASK_BALANCE()
{
	func = (mainFun_t)BALANCE_FUN;
	stackSize = 1024;
	name = "TASK_BALANCE";
	thread_prioroty = 0;
}