/*
 * ISR_Button_StartStop.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <ISR_Button_StartStop.h>
#include <main.h>
#include "Command.h"
#include <DataLogging_Control.h>

uint32 lastPressedTime = 0;

void BUTTON_STARTSTOP_CPP_ISR(){
	if(pendingReset) return;
    if((millis_ - lastPressedTime) > 500){
        if(bLogging){
        	COMMAND_STOP_LOGGING = 1;
        }else{
        	COMMAND_START_LOGGING = 1;
        }
    }
    lastPressedTime = millis_;
}

extern "C" void BUTTON_STARTSTOP_ISR(){
	BUTTON_STARTSTOP_CPP_ISR();
}

/* [] END OF FILE */
