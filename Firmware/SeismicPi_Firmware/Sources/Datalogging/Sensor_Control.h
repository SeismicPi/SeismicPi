/*
 * Sensor_Control.h
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <PE_Types.h>

extern char Sensor_Names[][20];
extern uint8 Sensors_Enabled;

void Sensor_SetName(uint8 index, char* name, uint8 nameLen);
void Sensor_SetName_Raw(uint8* buf, uint8 len);

void Sensor_Enable(uint8 index);
void Sensor_Disable(uint8 index);

uint8 Sensor_IsEnabled(uint8 index);

/* [] END OF FILE */
