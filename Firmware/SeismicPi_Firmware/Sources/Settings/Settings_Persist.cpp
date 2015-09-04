/*
 * Settings_Persist.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <SD.h>
#include <Settings_Persist.h>
#include <DataLogging_Control.h>
#include <Sensor_Control.h>
#include <Settings_FileRead.h>
#include <Scheduling.h>
#include "HAL.h"

File configFile;

char CONFIG_FILENAME[] = "config.txt";

uint8 Settings_LoadFromCard() {
	if (SD_IsCardReady()) {
		if (SD.exists(CONFIG_FILENAME)) {
			UART_Print("Loading config.txt from card...\n\r");
			configFile = SD.open("config.txt", FILE_READ);
			uint8 buf[32];
			uint8 nread = configFile.read(buf, sizeof(buf));
			while (nread > 0) {
				Settings_ProcessBuffer(buf, nread);
				nread = configFile.read(buf, sizeof(buf));
			}
			buf[0] = '\n';
			Settings_ProcessBuffer(buf, 1);
			configFile.close();
			UART_Flush();
			DelayMs(50); // Allow UART to clear
			Settings_Save();
			return 1;
		}
	}
	return 0;
}

void Settings_Load() {
	Flash_Load();
	if (Flash_GetByte(127) != 0xFF) { // Presence byte
		for (uint8 i = 0; i < 80; i++) {
			Sensor_Names[i / 20][i % 20] = Flash_GetByte(i);
		}
		DataLogging_SetFormat(Flash_GetByte(80));

		DataLogging_SetSampleDelay(Flash_GetLong(81));

		Sensors_Enabled = Flash_GetByte(85);

		Scheduling_SetStartTimeUnix(Flash_GetLong(86));
		Scheduling_SetEndTimeUnix(Flash_GetLong(90));
		if (Flash_GetByte(94)) {
			Scheduling_Enable();
		} else {
			Scheduling_Disable();
		}

		for (uint8 i = 0; i < 4; i++) {
			ADC_SetGain(i, Flash_GetByte(95 + i));
		}
	}
}

uint8 Settings_Save() {

	uint8 i = 0;
	for (i = 0; i < 80; i++) {
		Flash_PutByte(i, Sensor_Names[i / 20][i % 20]);
	}
	Flash_PutByte(80, DataLogging_GetFormat());

	Flash_PutLong(81, DataLogging_GetSampleDelay());

	Flash_PutByte(85, Sensors_Enabled);

	Flash_PutLong(86, Scheduling_GetStartTimeUnix());
	Flash_PutLong(90, Scheduling_GetEndTimeUnix());
	Flash_PutByte(94, Scheduling_IsEnabled());

	for (i = 0; i < 4; i++) {
		Flash_PutByte(95 + i, ADC_GetGain(i));
	}

	Flash_PutByte(127, 1); // Presence byte

	Flash_Save();
	return 0;
}

/* [] END OF FILE */
