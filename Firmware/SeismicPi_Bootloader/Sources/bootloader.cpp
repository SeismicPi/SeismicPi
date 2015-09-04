/*
 * bootloader.cpp
 *
 *  Created on: 12 Aug 2015
 *      Author: Steve
 */

#include "Cpu.h"
#include "bootloader.h"
#include "main.h"
#include "HAL.h"

#include "BL_SW.h"
#include "WAIT1.h"
#include "MK22F12810.h"
#include "SD.h"
#include "Console.h"

uint32 millis_ = 0;

File fwfile;

#define APP_FLASH_VECTOR_START		0xA000
#define FLASH_SIZE					0x20000

static bool BL_CheckBootloaderMode(void) {
  /* let's check if the user presses the BTLD switch. Need to configure the pin first */
  /* PTB8 as input */
  /* clock all port pins */
  SIM_SCGC5   |= SIM_SCGC5_PORTA_MASK |
             SIM_SCGC5_PORTB_MASK |
             SIM_SCGC5_PORTC_MASK |
             SIM_SCGC5_PORTD_MASK |
             SIM_SCGC5_PORTE_MASK;
  /* Configure pin as input */
  (void)BitIoLdd1_Init(NULL); /* initialize the port pin */
  if (!BL_SW_GetVal()) { /* button pressed (has pull-up!) */
    //WAIT1_Waitms(50); /* wait to debounce */     // TODO this seems to cause some issue (wdt resets cpu somewhere in this call)
    //if (!BL_SW_GetVal()) { /* still pressed */
      return TRUE; /* go into bootloader mode */
    //}
  }
  /* BTLD switch not pressed, and we have a valid user application vector */
  return FALSE; /* do not enter bootloader mode */
}

void BL_CheckForUserApp(void) {
	uint32_t startup; /* assuming 32bit function pointers */

	startup = ((uint32_t*) APP_FLASH_VECTOR_START)[1]; /* this is the reset vector (__startup function) */
	if (startup != -1 && !BL_CheckBootloaderMode()) { /* we do have a valid application vector? -1/0xfffffff would mean flash erased */
		((void (*)(void)) startup)(); /* Jump to application startup code */
	}
}

void BL_Erase(){
	uint32 numsectors = (FLASH_SIZE - APP_FLASH_VECTOR_START) / 2048;
	char uart_str[40];
	for(uint8 i = 0; i < numsectors; i++){
		Flash_Erase(APP_FLASH_VECTOR_START + (i * 2048), 2048);
		LED_Green_Blink(10);
		sprintf(uart_str, "Erased %lu of %lu sectors...\n\r", i+1, numsectors);
		UART_Print(uart_str);
	}
}

void BL_Flash(char filename[]){
	fwfile = SD.open(filename, FILE_READ);

	uint32 nfilesize = fwfile.size(); //  number of bytes
	uint32 numblocks = (nfilesize/512); // number of 512-byte blocks
	if(nfilesize%512!=0) numblocks++; // if it isnt a round amount of blocks

	if(nfilesize + APP_FLASH_VECTOR_START > FLASH_SIZE){
		UART_Print("File too large to fit in Flash!\n\r");
		fwfile.close();
		return;
	}

	char uart_str[40];
	sprintf(uart_str, "File size: %lu bytes (%lu blocks)\n\r", nfilesize, numblocks);
	UART_Print(uart_str);

	static uint8 buf[512];
	int nread = fwfile.read(buf, sizeof(buf));
	uint32 addr = 0xA000;
	uint32 nBlocksDone = 0;
	while (nread > 0) {
		if((addr & 2047)==0){ // if we are at the boundary of a flash-erase block (2048 bytes)
			Flash_Erase(addr, 2048); // erase it
		}
		Flash_Write(addr, buf, nread);
		addr += nread;

		LED_Green_Blink(10);

		nBlocksDone++;

		sprintf(uart_str, "Flashed %lu of %lu blocks...\n\r", nBlocksDone, numblocks);
		UART_Print(uart_str);

		nread = fwfile.read(buf, sizeof(buf));
	}

	fwfile.close();

	UART_Print("Done!\n\r");
}

void nmain() {

	UART_Start();
	Timer_Millis_Start();
	GPIO_Start();
	SPI_SD_Start();
	Flash_Start();

	UART_Print("-----------------------------------\n\r");
	UART_Print("SeismicPi bootloader version 1.0...\n\r");
	UART_Print("-----------------------------------\n\r");
	UART_Print("\n\r");
	UART_Print("Looking for an SD Card...\n\r");

	if (SD_Connect()) {
		UART_Print("Found an SD card...\n\r");
		LED_Green_Blink(250);
		// check if there is a new firmware file on the sd card.
		if (SD.exists("firmware.bin")) {
			UART_Print("Found firmware.bin on SD card...\n\r");
			LED_Green_Blink(250);

			BL_Flash("firmware.bin");

			UART_Print("Resetting processor...\n\r");
			UART_Flush();
			DelayMs(500);

			Cpu_SystemReset(); // reset the system to load into the application

		} else {
			UART_Print("No firmware.bin file found...\n\r");
			LED_Red_Blink(250);
		}
	} else {
		UART_Print("No SD Card found!\n\r");
		LED_Red_Blink(1000);
	}

	Console_Prompt();

	for(;;){
		Console_Process();
	}

}

extern "C" void mainentry() {
	nmain();
}
