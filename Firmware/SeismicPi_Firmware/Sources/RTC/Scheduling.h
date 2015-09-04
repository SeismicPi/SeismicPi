/*
 * Scheduling.h
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <PE_Types.h>

extern uint8 FLAG_SCHEDULING_CHECK;

#include <Time_Utils.h>

void Scheduling_SetStartTimeUnix(uint32 ts);
void Scheduling_SetEndTimeUnix(uint32 ts);
uint32 Scheduling_GetStartTimeUnix();
uint32 Scheduling_GetEndTimeUnix();
void Scheduling_Enable();
void Scheduling_Disable();
uint8 Scheduling_IsEnabled();
uint8 Scheduling_Check();

/* [] END OF FILE */
