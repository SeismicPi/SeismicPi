/*
 * HAL_Timer_Millis.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: Steve
 */

#include "HAL.h"

#include "TimerMillis.h"

LDD_TDeviceDataPtr TIMER_MILLIS;

void Timer_Millis_Start(){
	TIMER_MILLIS = TimerMillis_Init(NULL);
}

void Timer_Millis_Stop(){
	TimerMillis_Deinit(TIMER_MILLIS);
}
