/*
 * HAL_Delay.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: Steve
 */

#include "HAL.h"
#include "Arduino.h"

void DelayMs(uint16_t ms){
	uint16_t t0 = millis();
	while((millis()-t0)<ms);
}
