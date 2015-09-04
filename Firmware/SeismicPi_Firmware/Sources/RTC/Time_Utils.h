/*
 * Time_Utils.h
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#ifndef SOURCES_RTC_TIME_UTILS_H_
#define SOURCES_RTC_TIME_UTILS_H_

#include <PE_Types.h>

typedef struct{
    uint8 hours     : 5; // 0-23, 5 bits
    uint8 minutes   : 6; // 0-59, 6 bits
    uint8 seconds   : 6; // 0-59, 6 bits
    uint8 date      : 5; // 1-31, 5 bits
    uint8 month     : 4; // 1-12, 4 bits
    uint8 year      : 7; // 0-99, 7 bits
    uint8 dow       : 3; // 0-7,  3 bits
} tm_elems;

const uint8 RTC_DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char RTC_DAY_NAMES[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

extern uint32 RTC_MostRecentTime;

void Time_TimeFromUnix(tm_elems *tm, uint32 timestamp);
uint32 Time_UnixFromTime(tm_elems *tm);
void Time_PrintTime(tm_elems *tm);
int32 Time_TimeDifference(tm_elems *tm1, tm_elems *tm2);
uint8 Time_Equals(tm_elems *tm1, tm_elems *tm2);
void Time_SdTime(uint16_t *date, uint16_t *time);

/* [] END OF FILE */

#endif
