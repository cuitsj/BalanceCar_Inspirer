#pragma once

#include "main.h"

#define KP 0
#define KI 1
#define KD 2
#define KT 3
#define KB 4
#define KF 5

typedef struct PID
{
	float SumError;	//误差累计	
	int32_t LastError;	//Error[-1]
	int32_t PrevError;	//Error[-2]	
	int32_t LastData;	//Speed[-1]
} PID;

extern PID MOTOR_PID, Angle_PID, Ang_Vel_PID, Direct_PID, Turn_PID, Distance_PID;	//定义舵机和电机的PID参数结构体
extern float MOTOR[4], Angle[4], Ang_Vel[4], Direct[4], Turn[5][4], Distance[4];
extern int16_t gyro_real[3],accel_real[3];

class TASK_BALANCE: public TASK
{
public:
	TASK_BALANCE();
	static void BALANCE_FUN(void* parameter);
};
