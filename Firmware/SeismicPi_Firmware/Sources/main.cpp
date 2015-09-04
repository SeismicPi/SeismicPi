/* ###################################################################
 **     Filename    : main.cpp
 **     Project     : SeismicPi_Bootloader
 **     Processor   : MK22FN128VLH10
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-07-28, 17:44, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.cpp
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "pin_mux.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "SD.h"
#include "Settings_Persist.h"
#include "Command.h"
#include "Scheduling.h"
#include "Datalogging_Control.h"
#include "dbuffer.h"
#include "HAL.h"

uint32 millis_ = 0;

uint32 aval[4];
uint16_t accelval[3];

File dataFile;

uint8 bLogging = 0;

uint8 pendingReset = 0;
uint32 resetTime = 0;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	// Start the USB interface
	USB_Start();

	// Start the timer which tracks millis()
	Timer_Millis_Start();

	// Initialise the GPIOs
	GPIO_Start();
	LED_All_Sequence();

	// Start the RTC
	RTC_Start();

	// Start the ADC
	ADC_Start();

	// Start the Flash Memory
	Flash_Start();

	// Start the Accelerometer
	Accel_Start();

	// Start UART
	UART_Start();

	UART_Print("+-------------------------------------------------------------+\n\r");
	UART_Print("|  ___  ___ ___   ___       _        _                        |\n\r");
	UART_Print("| | _ )/ __/ __| |   \\ __ _| |_ __ _| |___  __ _ __ _ ___ _ _ |\n\r");
	UART_Print("| | _ \\ (_ \\__ \\ | |) / _` |  _/ _` | / _ \\/ _` / _` / -_) '_||\n\r");
	UART_Print("| |___/\\___|___/ |___/\\__,_|\\__\\__,_|_\\___/\\__, \\__, \\___|_|  |\n\r");
	UART_Print("|                                          |___/|___/         |\n\r");
	UART_Print("+-------------------------------------------------------------+\n\r");
	UART_Print("|  ___           _            _      __      __            _  |\n\r");
	UART_Print("| | _ )_  _   _ | |__ _ _ __ (_)___  \\ \\    / /__  ___  __| | |\n\r");
	UART_Print("| | _ \\ || | | || / _` | '  \\| / -_)  \\ \\/\\/ / _ \\/ _ \\/ _` | |\n\r");
	UART_Print("| |___/\\_, |  \\__/\\__,_|_|_|_|_\\___|   \\_/\\_/\\___/\\___/\\__,_| |\n\r");
	UART_Print("|  __ _|__/  __| | \\ \\ / (_)_ _  __ _  | |  (_)_  _           |\n\r");
	UART_Print("| / _` | ' \\/ _` |  \\ V /| | ' \\/ _` | | |__| | || |          |\n\r");
	UART_Print("| \\__,_|_||_\\__,_|   |_| |_|_||_\\__, | |____|_|\\_,_|          |\n\r");
	UART_Print("|                               |___/                         |\n\r");
	UART_Print("+-------------------------------------------------------------+\n\r");

	// Start the SD Card SPI interface
	SPI_SD_Start();

	// Connect to the SD Card
	if (SD_Connect()) {
		UART_Print("Found a card!\n\r");
		if (!Settings_LoadFromCard()) {
			Settings_Load();
		} else {
			LED_Blue_On(); // Blink blue LED to indicate successful load from card
			DelayMs(100);
			LED_Blue_Off();
		}
	} else {
		UART_Print("Card failed or missing!\n\r");
		Settings_Load();
	}

	// Begin sampling the ADC
	ADC_InterruptEnable();

	// Start main loop
	for (;;) {
		if (FLAG_SCHEDULING_CHECK) {
			FLAG_SCHEDULING_CHECK = 0;
			uint8 ret = Scheduling_Check();
			if (ret == 1) {
				COMMAND_START_LOGGING = 1;
			} else if (ret == 2) {
				COMMAND_STOP_LOGGING = 1;
			}
		}

		if (COMMAND_SET_RTC_TIME) {
			tm_elems tm;
			Time_TimeFromUnix(&tm, COMMAND_SET_RTC_TIME);
			RTC_Set(&tm);
			COMMAND_SET_RTC_TIME = 0;
		}
		if (COMMAND_SAVE_SETTINGS && !bLogging) { // Don't allow saving to EEPROM while recording
			COMMAND_SAVE_SETTINGS = 0;
			Settings_Save();
		}
		if (COMMAND_START_LOGGING) {
			COMMAND_START_LOGGING = 0;
			DataLogging_Start();
		}
		if (COMMAND_STOP_LOGGING) {
			COMMAND_STOP_LOGGING = 0;
			DataLogging_Stop();
		}
		if (COMMAND_INITIALIZE_CARD) {
			COMMAND_INITIALIZE_CARD = 0;
			SD_Connect();
		}
		if (COMMAND_RESET) {
			COMMAND_RESET = 0;
			pendingReset = 1;
			resetTime = millis_ + 5000;
		}

		// While there is data in the write buffer
		while (dbufsize() >= 8) {
			uint8 i = 0;
			uint32 tmp[8];
			for (i = 0; i < 8; i++) {
				tmp[i] = dbufread();
			}
			DataLogging_Write(tmp);
		}

		// If we aren't logging but the file is open
		if (!bLogging && dataFile) {
			UART_Print("Stopping logging...\n\r");
			dataFile.close(); // Close the file and write it to the disk
		}
	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START(); /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	for (;;) {
	}
	/*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
