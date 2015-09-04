/*
 * Time_Utils.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <Time_Utils.h>
#include <stdio.h>

#include "utility/SdFat.h"

#include "HAL.h"

uint32 RTC_MostRecentTime = 0;

uint8 isLeapYear(uint8 year){
    uint16 tmpYear = 2000 + year;
    if ((tmpYear%4) != 0) return 0;
    if ((tmpYear%100) != 0) return 1;
    if ((tmpYear%400) == 0) return 1;
    return 0;
}

void Time_TimeFromUnix(tm_elems *tm, uint32 timestamp){
    tm->year = (timestamp / 31536000) - 30;
    uint8 numLeapYears = ((2000+tm->year)-1969)/4;
    uint16 numDays = (timestamp / 86400);
    uint16 daysThisYear = (numDays - numLeapYears) % 365;
    if(isLeapYear(tm->year) && daysThisYear>59) daysThisYear++;
    uint8 i = 0;
    for(i=0;i<sizeof(RTC_DAYS_IN_MONTH);i++){
        if(daysThisYear < RTC_DAYS_IN_MONTH[i]) break;
        daysThisYear -= RTC_DAYS_IN_MONTH[i];
    }
    tm->date = daysThisYear+1;
    tm->month = i+1;
    uint32 secsThisDay = timestamp - (numDays * 86400);
    tm->hours = secsThisDay / 3600;
    uint16 minutesLeft = secsThisDay - (tm->hours * 3600);
    tm->minutes = minutesLeft/60;
    tm->seconds = minutesLeft - (tm->minutes * 60);
    tm->dow = (numDays+4)%7;
}

void Time_PrintTime(tm_elems *tm){
    char uart_str[30];
    uint32 ts = Time_UnixFromTime(tm);
    sprintf(uart_str, "Time is: %s %d/%d/%d %d:%d:%d\n\r", RTC_DAY_NAMES[tm->dow], tm->date, tm->month, tm->year, tm->hours, tm->minutes, tm->seconds);
    UART_Print(uart_str);
    sprintf(uart_str, "This is UNIX time: %lu\n\r", ts);
    UART_Print(uart_str);
}

uint32 Time_UnixFromTime(tm_elems *tm){
    uint32 timestamp = 0;
    uint8 numYears = (2000 + tm->year)-1970;
    uint8 numLeapYears = numYears / 4;
    uint16 numDays = numYears * 365;
    numDays += numLeapYears;
    uint8 i = 0;
    if(isLeapYear(tm->year) && tm->month>2) numDays += 1;
    for(i=0; i < (tm->month-1); i++){
        numDays += RTC_DAYS_IN_MONTH[i];
    }
    numDays += (tm->date-1);
    timestamp = numDays * 86400;
    timestamp += (tm->hours * 3600);
    timestamp += (tm->minutes * 60);
    timestamp += (tm->seconds);
    return timestamp;
}

int32 Time_TimeDifference(tm_elems *tm1, tm_elems *tm2){
    uint32 ts1 = Time_UnixFromTime(tm1);
    uint32 ts2 = Time_UnixFromTime(tm2);
    return ts2 - ts1;
}

uint8 Time_Equals(tm_elems *tm1, tm_elems *tm2){
    return tm1->year==tm2->year && tm1->month==tm2->month && tm1->date==tm2->date
        && tm1->hours==tm2->hours && tm1->minutes==tm2->minutes && tm1->seconds==tm2->seconds;
}

void Time_SdTime(uint16_t *date, uint16_t *time){
	tm_elems cur;
	Time_TimeFromUnix(&cur, RTC_MostRecentTime);
	*date = FAT_DATE(cur.year+2000, cur.month, cur.date);
	*time = FAT_TIME(cur.hours, cur.minutes, cur.seconds);
}

/* [] END OF FILE */
