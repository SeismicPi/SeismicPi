/*
 * Scheduling.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <Scheduling.h>
#include "HAL.h"

uint32 time_start;
uint32 time_end;

uint8 enabled_ = 0;

uint8 FLAG_SCHEDULING_CHECK = 0;

void Scheduling_SetStartTimeUnix(uint32 ts){
    time_start = ts;
}

void Scheduling_SetEndTimeUnix(uint32 ts){
    time_end = ts;
}

uint32 Scheduling_GetStartTimeUnix(){
    return time_start;
}

uint32 Scheduling_GetEndTimeUnix(){
    return time_end;
}

void Scheduling_Enable(){
    enabled_ = 1;
}

void Scheduling_Disable(){
    enabled_ = 0;
}

uint8 Scheduling_IsEnabled(){
    return enabled_;
}

uint8 Scheduling_Check(){
    tm_elems tm;
    RTC_Get(&tm);
    uint32 tNow = Time_UnixFromTime(&tm);
    RTC_MostRecentTime = tNow;
    if(!enabled_) return 0;
    if(time_end <= tNow){
        enabled_ = 0; // Disable scheduling so this doesnt keep being called
        return 2;
    }
    if(time_start <= tNow) return 1;
    return 0;
}

/* [] END OF FILE */
