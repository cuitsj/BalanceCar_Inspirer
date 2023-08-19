#pragma once
#include "main.h"

class TASK_MPU: public TASK
{
public:
	TASK_MPU();
	static void MPU_FUN(void* parameter);
};
