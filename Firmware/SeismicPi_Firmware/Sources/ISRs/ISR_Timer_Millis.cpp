/*
 * ISR_Timer_Millis.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <ISR_Timer_Millis.h>
#include "Cpu.h"
#include <main.h>
#include <DataLogging_Control.h>
#include <Scheduling.h>
#include "HAL.h"
#include "USB_Command.h"
#include <stdio.h>

#include "dbuffer.h"

uint16 subcount_ = 0;
uint32 logintervalcount_ = 0;

char uart_str[30];

void TIMER_MILLIS_CPP_ISR(){

    subcount_++;
    if(subcount_>=100){
        subcount_ = 0;
        millis_++;

        if(pendingReset){
        	if(millis_ % 100 == 0) LED_Green_Toggle();
        	if(resetTime < millis_) Cpu_SystemReset();
        }
        LED_Red_On();
        USB_Update();
        LED_Red_Off();

        if(USB_GetRxBufSize()>0){
        	USB_COMMAND_CPP_ISR();
        }

        Accel_Measure();
        if((millis_%1000)==0){
            FLAG_SCHEDULING_CHECK = 1;
        }
    }
    
    if(bLogging){
        logintervalcount_ ++;
        if (logintervalcount_ >= DataLogging_GetSampleDelay()){
            logintervalcount_ = 0;
            //bTimeToLog = 0x01;

            //if(bTimeToLog){
			//	bTimeToLog = 0;

				sprintf(uart_str, "%lu\n\r", dbufsize());
				UART_Print(uart_str);

				if(dbufsize() < (DBUFFER_SIZE-8)){ // room for all vals
					dbufwrite(millis_);
					dbufwrite(aval[0]);
					dbufwrite(aval[1]);
					dbufwrite(aval[2]);
					dbufwrite(aval[3]);
					dbufwrite(accelval[0]);
					dbufwrite(accelval[1]);
					dbufwrite(accelval[2]);
				}else{
					UART_Print("DBUFFER FULL! ABORTING!\n\r");
					DataLogging_Stop();
				}
			//}

        }
    }
}

extern "C" void TIMER_MILLIS_ISR(){
	TIMER_MILLIS_CPP_ISR();
}

/* [] END OF FILE */
