/*
 * HAL_Accel.cpp
 *
 *  Created on: 12 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "ADC_Accel.h"

bool ACCEL_INITIALISED = FALSE;

void Accel_Start(){
	ADC_Accel_Init();
	ACCEL_INITIALISED = TRUE;
}

void Accel_Measure(){
	if(!ACCEL_INITIALISED) return;
	ADC_Accel_Measure(FALSE);
}

void Accel_GetResults(uint16_t buf[]){
	ADC_Accel_GetValue16(buf);
}
