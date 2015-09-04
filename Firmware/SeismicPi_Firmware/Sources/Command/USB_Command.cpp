/*
 * USB_Command.cpp
 *
 *  Created on: 14 Aug 2015
 *      Author: Jamie
 */

#include "Command.h"
#include "USB_Command.h"
#include "HAL.h"

#include "stdio.h"

void usbPutArray(uint8 val[], uint32 len){
	uint8 i = 0;
	for(i=0;i<len;i++){
		USB_SendByte(val[i]);
	}
}

void usbPutuint8(uint8 val){
	USB_SendByte(val);
}

void usbClearTx(){
	// nothing to do here
}

extern "C" void USB_COMMAND_ISR(){
	USB_COMMAND_CPP_ISR();
}

void USB_COMMAND_CPP_ISR(){
	uint8 val = USB_GetByte();

	char uart_str[5];
	sprintf(uart_str, "%d ", val);
	UART_Print(uart_str);

	Command_Process_Char(val, usbClearTx, usbPutuint8, usbPutArray);
}
