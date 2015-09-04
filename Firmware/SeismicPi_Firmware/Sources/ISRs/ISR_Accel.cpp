/*
 * ISR_Accel.cpp
 *
 *  Created on: 12 Aug 2015
 *      Author: Jamie
 */

#include "ISR_Accel.h"
#include "main.h"
#include "HAL.h"

void ACCEL_CPP_ISR(){
	Accel_GetResults(accelval);
}

extern "C" void ACCEL_ISR(){
	ACCEL_CPP_ISR();
}
