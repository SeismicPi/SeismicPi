/*
 * HAL_Flash.cpp
 *
 *  Created on: 4 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "FLASH.h"
#include "CPU.h"

#define FLASH_BASE_ADDRESS 0x1F800

static uint8 buf[128];

void Flash_Start() {
	FLASH_Init();
}

void Flash_PutByte(uint8 addr, uint8 val) {
	buf[addr] = val;
}

uint8 Flash_GetByte(uint8 addr) {
	return buf[addr];
}

void Flash_PutLong(uint8 addr, uint32 val) {
	buf[addr] = (val >> 24) & 0xFF;
	buf[addr + 1] = (val >> 16) & 0xFF;
	buf[addr + 2] = (val >> 8) & 0xFF;
	buf[addr + 3] = val & 0xFF;
}

uint32 Flash_GetLong(uint8 addr) {
	return (buf[addr] << 24) + (buf[addr + 1] << 16) + (buf[addr + 2] << 8) + buf[addr + 3];
}

void Flash_Load() {
	FLASH_GetBlockFlash(FLASH_BASE_ADDRESS, buf, 128);
}

void Flash_Save() {
	USB_Stop();
	CPU_SetClockConfiguration(1); // Leave High-Speed Run mode (required for Flash-write)
	FLASH_SetBlockFlash(buf, FLASH_BASE_ADDRESS, 128);
	CPU_SetClockConfiguration(0); // Re-enter High-Speed Run mode
	LED_Green_On();
	DelayMs(100);
	LED_Green_Off();
	DelayMs(100);
	USB_Start();
}
