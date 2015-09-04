/*
 * HAL_USB.cpp
 *
 *  Created on: 14 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"

extern "C"{
#include "USB1.h"
#include "CDC1.h"
}

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];

void USB_Start(){
	USB1_Init();
}

void USB_Stop(){
	USB1_Deinit();
}

void USB_Update(){
	CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer));
}

uint8 USB_GetRxBufSize(){
	return CDC1_GetCharsInRxBuf();
}

static uint8 c = 0;

uint8 USB_GetByte(){
	CDC1_GetChar(&c);
	return c;
}

void USB_SendByte(uint8 b){
	CDC1_SendChar(b);
}
