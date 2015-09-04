/*
 * ISR_SD_CD.cpp
 *
 *  Created on: 17 Aug 2015
 *      Author: Jamie
 */

#include "ISR_SD_CD.h"
#include "HAL.h"
#include "Command.h"

void SDCD_CPP_ISR(){
	COMMAND_INITIALIZE_CARD = 1;
}

extern "C" void SDCD_ISR(){
	SDCD_CPP_ISR();
}


