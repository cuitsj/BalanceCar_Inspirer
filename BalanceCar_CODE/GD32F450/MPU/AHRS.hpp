#pragma once
#include "main.h"

extern float pitch,roll;

void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);
float invSqrt(float number);
void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az);
void CountTurns(float *newdata,float *olddata,short *turns);
void CalYaw(float *yaw,short *turns);
void CalibrateToZero(void);