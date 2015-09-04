/*
 * UART_Command.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <Command.h>
#include <UART_Command.h>
#include <HAL.h>

static word snd;

void uartPutArray(uint8 val[], uint32 len){
	uint8 i = 0;
	for(i=0;i<len;i++){
		UART_Print((char)val[i]);
	}
}

void uartPutuint8(uint8 val){
	UART_Print(val);
}

extern "C" void UART_COMMAND_ISR(){
	UART_COMMAND_CPP_ISR();
}

void UART_COMMAND_CPP_ISR(){
	uint8 val = UART_GetChar();
    
	Command_Process_Char(val, UART_ClearTxBuffer, uartPutuint8, uartPutArray);
}

/* [] END OF FILE */
