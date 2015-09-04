/*
 * HAL_Flash.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: Steve
 */

#include "HAL.h"

#include "FLASH.h"

LDD_TDeviceDataPtr FLASH;

void Flash_Start(){
	FLASH = FLASH_Init(NULL);
}

void Flash_Stop(){
	FLASH_Deinit(FLASH);
}

void Flash_Erase(uint32 addr, uint32 dataLen){
	volatile uint8 test = FLASH_Erase(FLASH, addr, dataLen);
	test++;
	uint8 status = FLASH_GetOperationStatus(FLASH);
	while(status != LDD_FLASH_IDLE){
		if(status == LDD_FLASH_FAILED){
			LED_Red_On();
			break;
		}
		FLASH_Main(FLASH);
		status = FLASH_GetOperationStatus(FLASH);
	}
}

void Flash_Write(uint32 addr, uint8 *data, uint32 dataLen){
	FLASH_Write(FLASH, data, addr, dataLen);
	uint8 status = FLASH_GetOperationStatus(FLASH);
	while(status != LDD_FLASH_IDLE){
		if(status==LDD_FLASH_FAILED){
			LED_Red_On();
			for(;;){
				asm(" nop\n");
			}
		}
		FLASH_Main(FLASH);
		status = FLASH_GetOperationStatus(FLASH);
	}
}

void Flash_Read(uint32 addr, uint8 *data, uint32 dataLen){
	FLASH_Read(FLASH, addr, data, dataLen);
	while(FLASH_GetOperationStatus(FLASH) != LDD_FLASH_IDLE){
		FLASH_Main(FLASH);
	}
}
