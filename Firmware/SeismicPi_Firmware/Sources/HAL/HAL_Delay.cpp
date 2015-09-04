/*
 * HAL_Delay.cpp
 *
 *  Created on: 4 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "Arduino.h"

void DelayMs(uint16_t ms){
	uint16_t t0 = millis();
	while((uint16_t)(millis()-t0) < ms){
		;
	}
}


