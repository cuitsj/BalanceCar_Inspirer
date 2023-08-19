#include "TASK_BALANCE.hpp"


#define Zero_Angle 2.0f	// ��ɫ���
#define AcceRatio 	16384.0f
#define GyroRatio 	16.4f
#define Gyro_Gr		0.0010653	// ���ٶȱ�ɻ���	�˲�����Ӧ����2000��ÿ��
#define ACC_FILTER_NUM 5		// ���ٶȼ��˲����
#define GYRO_FILTER_NUM 1		// �������˲����

PID MOTOR_PID, Angle_PID, Ang_Vel_PID, Direct_PID, Turn_PID, Distance_PID;	//�������͵����PID�����ṹ��
float MOTOR[4]   = {25, 40/200, 40, 500};		// �ٶȻ�PID	���һ��Ϊ�����޷�
float Angle[4]   = {0.3, 0, 0.1, 500};		// �ǶȻ�PID
float Ang_Vel[4] = {0.25, 0.025, 0, 1000};		// ���ٶȻ�PID
float Direct[4]  = {0.017, 0.001, 0.023, 70};	// ת��PID λ��	0.017	0.02
float Turn[5][4] = {{100, 7, 7, 400},	// 130	// ת���⻷��̬PID	���߷�
					{100, 8, 8, 400},	// 140
					{100, 8, 8, 400},	// 150
					{100, 9, 9, 400},	// 160
					{100, 10, 10, 400}};	// 170

int32_t Speed_Left=0,Speed_Right=0;
int32_t Tar_Ang_Vel=0,Target_Angle=0;
int32_t ACC_X_BUF[ACC_FILTER_NUM], ACC_Y_BUF[ACC_FILTER_NUM], ACC_Z_BUF[ACC_FILTER_NUM];	// �˲���������
int32_t GYRO_X_BUF[GYRO_FILTER_NUM], GYRO_Y_BUF[GYRO_FILTER_NUM], GYRO_Z_BUF[GYRO_FILTER_NUM];
int16_t gyro_real[3],accel_real[3];
	  			/* ���ֱ�־λ���Ŷ�ʱ���н���ʱ����� */
char Speed_Flag, Angle_Flag, Ang_Velocity_Flag, DMP_Flag;

int32_t MOTOR_Duty_Left  = 0;
int32_t MOTOR_Duty_Right = 0;
					
int32_t 
	Speed_Now = 0,	// ��ǰʵ���ٶ�
	Speed_Min = 0,	// ������С�ٶ�
	Speed_Set = 0, 	// Ŀ���趨�ٶ�
	Theory_Duty = 0,// ����ֱ��ռ�ձ�
	Vel_Set = 0,	// Ŀ��ת����ٶ�
	Direct_Parameter = 0,// ת��ϵ��
	Direct_Last = 0,
	Radius = 0;		// Ŀ��ת��뾶����

uint8_t Point = 80;
int32_t Difference = 0;

/*
 * ��������Data_Filter
 * ����  �����ݻ����˲�
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Data_Filter(void)	// �����˲�
{
	uint8_t i;
	float ACC_Angle;
	int64_t temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0, temp6 = 0;
	
	ACC_X_BUF[0] = accel[0];	// ���»�����������
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

// ����ʽPID�������
int32_t PID_Increase(PID *sptr, float *PID, int32_t NowData, int32_t Point)
{
	//��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
	int32_t iError,	//��ǰ���
		Increase;	//���ó���ʵ������

	iError = Point - NowData;	// ���㵱ǰ���

	Increase =  PID[KP] * (iError - sptr->LastError)
			  + PID[KI] * iError
			  + PID[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	// ����ǰ�����
	sptr->LastError = iError;		  	// �����ϴ����
	sptr->LastData  = NowData;			// �����ϴ�����
	
	return Increase;	// ��������
}

/******** �޷����� *********/
int32_t range_protect(int32_t duty, int32_t min, int32_t max)//�޷�����
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

// λ��ʽPID����
int32_t PID_Realize(PID *sptr, float *PID, int32_t NowData, int32_t Point)
{
	//��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
	int32_t iError,	// ��ǰ���
		 Realize;	// ���ó���ʵ������

	iError = Point - NowData;	// ���㵱ǰ���
	sptr->SumError += PID[KI] * iError;	// ������
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
	sptr->PrevError = sptr->LastError;	// ����ǰ�����
	sptr->LastError = iError;		  	// �����ϴ����
	sptr->LastData  = NowData;			// �����ϴ�����

	return Realize;	// ����ʵ��ֵ
}

float Velocity_Kp = 50,		//�ٶȻ�Kp
	  Velocity_Ki = 50/200;			//�ٶȻ�Kd

//�ٶȻ�PI
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
/********************* ����ƽ����� *********************/
// Ƶ�ʿ����ڶ�ʱ��������
void Balance_Control(void)
{
	if (Ang_Velocity_Flag)	// ֱ�����ٶȻ�	2ms
	{
		Ang_Velocity_Flag = 0;
		
		MPU_Get_Gyroscope();
		MPU_Get_Accelerometer();		// ��ȡ����������
		Data_Filter();					// ��ԭʼ���ݻ����˲�												
												/* ���ٶȻ���Ϊ���ڻ�����ֱ�� */
		Theory_Duty += PID_Increase(&Ang_Vel_PID, Ang_Vel, (int32_t)(gyro_real[1]*10), (int32_t)(Tar_Ang_Vel));	// ����ֱ��PWM
		Theory_Duty = range_protect(Theory_Duty, -950, 950);
			
		if (0)
		{						/* ���ٶȻ���Ϊ���ڻ�����ת�� */									//Speed_Min
			Direct_Parameter = PID_Realize(&Direct_PID, Direct, (int32_t)(gyro_real[2]), 0);//Radius*Speed_Min);	// ת�������Ҹ�
			Direct_Parameter = range_protect(Direct_Parameter, -1200, 1200);
		}
		
		Direct_Last = Direct_Last*0.3 + Direct_Parameter*0.7;	// �����ϴν��ٶȻ����
		
		MOTOR_Duty_Left  = Theory_Duty - Direct_Last;	// ���ҵ������ת��ϵ����������
		MOTOR_Duty_Right = Theory_Duty + Direct_Last;	

//		gBSP->TIM0_MOTORL->SetDUTY(MOTOR_Duty_Left);
//		gBSP->TIM0_MOTORR->SetDUTY(MOTOR_Duty_Right);			//===��ֵ��PWM�Ĵ���
		
		Read_DMP();	// ʹ��DMPֱ�Ӷ�ȡŷ����
	}
	
	if (Angle_Flag)		// ֱ���ǶȻ�	10ms
	{
		Angle_Flag = 0;
		
		//				//===��ȡ��������ֵ
			Speed_Left = gBSP->TIM3_LENCODER->ReadCnt();
			Speed_Right = gBSP->TIM2_RENCODER->ReadCnt();// ��ȡ��ǰ�ٶ�
		Speed_Now = (Speed_Left+Speed_Right)/2;
											/* �ǶȻ��ӵ����ٶȻ��ϴ������� */
		Tar_Ang_Vel = PID_Realize(&Angle_PID, Angle, (int32_t)(-Pitch*100), (int32_t)Target_Angle);	// ���Ϊ�Ŵ�10����Ŀ����ٶ�	
		Tar_Ang_Vel = range_protect(Tar_Ang_Vel, -1500, 1500);	// ע��������
	}
	if (Speed_Flag)		// �ٶȻ�	100ms
	{
		Speed_Flag = 0;
												/* �ٶȻ��ӵ��ǶȻ��ϴ������� */
//		Target_Angle = Velocity_PI(Speed_Now);	// ���Ϊ�Ŵ�100����Ŀ��Ƕ�
		
		Target_Angle = -PID_Realize(&MOTOR_PID, MOTOR, Speed_Now, 0);	// ���Ϊ�Ŵ�100����Ŀ��Ƕ�
//		Target_Angle += Zero_Angle*100;	// Ŀ��Ƕȵ����������
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
	
	Ang_Velocity_Flag = 1;	// ���ٶ�2ms��ȡһ��
	
	if (Time_10ms == 5)
	{
		Time_10ms = 0;
		Angle_Flag = 1;		// ��̬�Ƕ�10ms����һ��	
	}
	
	if (Time_50ms == 25)
	{
		Time_50ms = 0;
		
//		Data_Send_Scope();//������Data_Scope��λ��������
//		Data_Send_Status();//������������λ��������
	}
	
	if (Time_100ms == 50)
	{
		Time_100ms = 0;
		Speed_Flag = 1;	// �ٶ�100ms����һ��
	}
	
	Balance_Control();	// ����ƽ�����
	
//		gBSP->TIM0_MOTORL->SetDUTY(motor1);
//		gBSP->TIM0_MOTORR->SetDUTY(motor2);			//===��ֵ��PWM�Ĵ���  
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