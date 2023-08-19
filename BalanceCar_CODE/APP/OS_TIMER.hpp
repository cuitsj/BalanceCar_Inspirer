#pragma once

#include "main.h"

class OS_Timer1: public TIMER
{
public:
	OS_Timer1();
	static void OS_Timer1_FUN(void* parameter);
};
