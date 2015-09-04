/*
 * DataLogging_Control.h
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <PE_Types.h>

#define FILETYPE_RAW 0x01
#define FILETYPE_CSV 0x02

void DataLogging_SetFormat(uint8 format);

uint8 DataLogging_GetFormat();

void DataLogging_SetSampleDelay(uint32 delay);
void DataLogging_SetSampleDelay_Raw(uint8* buf, uint8 len);
uint32 DataLogging_GetSampleDelay();

void DataLogging_Start();
void DataLogging_Stop();

void DataLogging_Write(uint32 data[]);

void DataLogging_GetNewFileName(char *name, char ending[]);

/* [] END OF FILE */
