/*
 * HAL_RTC.cpp
 *
 *  Created on: 3 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "RTC.h"

LDD_TDeviceDataPtr RTC;

void RTC_Start(){
	if(RTC_SR == RTC_SR_TCE_MASK){ // If RTC clock is already running
		RTC = RTC_Init(NULL, true); // Initialise the RTC softly
	}else{
		RTC = RTC_Init(NULL, false); // Initialise the RTC hard (reset time/date etc.)
		for(uint8 i = 0; i < 4; i++){
			LED_Red_On();
			DelayMs(500);
			LED_Red_Off();
			DelayMs(500);
		}
	}
}

void RTC_Set(tm_elems *tm){
    LDD_RTC_TTime ttime;
    ttime.Day = tm->date;
    ttime.DayOfWeek = tm->dow;
    ttime.Hour = tm->hours;
    ttime.Minute = tm->minutes;
    ttime.Month = tm->month;
    ttime.Second = tm->seconds;
    ttime.Year = tm->year + 2000;

    RTC_SetTime(RTC, &ttime);
}

void RTC_Get(tm_elems *tm){
    LDD_RTC_TTime ttime;
    RTC_GetTime(RTC, &ttime);

    tm->date = ttime.Day;
    tm->dow = ttime.DayOfWeek;
    tm->hours = ttime.Hour;
    tm->minutes = ttime.Minute;
    tm->month = ttime.Month;
    tm->seconds = ttime.Second;
    tm->year = ttime.Year - 2000;
}
