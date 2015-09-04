/*
 * Command.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */
 
#include <Command.h>

#include <DataLogging_Control.h>
#include <Sensor_Control.h>
#include <Scheduling.h>
#include <Settings_Persist.h>
#include <main.h>
#include <HAL.h>

uint8 VERSION[] = "v1.0";

uint8 COMMAND_START_LOGGING = 0;
uint8 COMMAND_STOP_LOGGING = 0;
uint8 COMMAND_INITIALIZE_CARD = 0;
uint8 COMMAND_SAVE_SETTINGS = 0;
uint32 COMMAND_SET_RTC_TIME = 0;
uint8 COMMAND_RESET = 0;

#define CMD_GET_SENSOR_VALUES	0x01
#define CMD_SET_SENSOR_NAME		0x02
#define CMD_SET_SAMPLE_DELAY	0x03
#define CMD_START_LOGGING		0x04
#define CMD_STOP_LOGGING		0x05
#define CMD_INITIALISE_CARD		0x06
#define CMD_IS_CARD_READY		0x07
#define CMD_SET_RAW_FILETYPE	0x08
#define CMD_SET_CSV_FILETYPE	0x09
#define CMD_FIRMWARE_VERSION	0x11
#define CMD_GET_SENSOR_NAME		0x12
#define CMD_GET_SAMPLE_DELAY	0x13
#define CMD_GET_FILETYPE		0x14
#define CMD_ENABLE_SENSOR		0x15
#define CMD_DISABLE_SENSOR		0x16
#define CMD_GET_ENABLED_MASK	0x17
#define CMD_SET_SCHEDULED_START	0x18
#define CMD_SET_SCHEDULED_END	0x19
#define CMD_ENABLE_SCHEDULING	0x20
#define CMD_DISABLE_SCHEDULING	0x21
#define CMD_SET_RTC_TIME		0x22
#define CMD_GET_RTC_TIME		0x23
#define CMD_SAVE_SETTINGS		0x24
#define CMD_IS_SCHEDULING_ENABLED	0x25
#define CMD_GET_SCHEDULED_START	0x26
#define CMD_GET_SCHEDULED_END	0x27
#define CMD_SET_CHANNEL_GAIN	0x28
#define CMD_GET_CHANNEL_GAIN	0x29
#define CMD_GET_ACCEL_VALUES	0x30
#define CMD_RESET_PROCESSOR		0xF0

uint8 readingval_ = 0;
uint8 datalen_ = 0;
uint8 lenread_ = 0;
uint8 buf[21];
uint8 i = 0;

void sendInt24(uint32 val, void writeFn(uint8)) {
	writeFn((val >> 16) & 0xFF);
	writeFn((val >> 8) & 0xFF);
	writeFn(val & 0xFF);
}

void sendInt16(uint16_t val, void writeFn(uint8)){
	writeFn((val >> 8) & 0xFF);
	writeFn(val & 0xFF);
}

void Command_Process_Char(uint8 val, void clearFn(), void writeFn(uint8),
		void arrayFn(uint8[], uint32)) {
	if (readingval_ && (lenread_ != datalen_)) {
		if (lenread_ == 0) {
			if (val < 22) {
				datalen_ = val + 1;
			} else {
				datalen_ = 22;
			}
			lenread_ = 1;
		} else {
			buf[lenread_ - 1] = val;
			lenread_++;
			if (lenread_ == datalen_) {
				uint8 idx;
				uint32 ts;
				switch (readingval_) {
				case CMD_SET_SENSOR_NAME:
					Sensor_SetName_Raw(buf, datalen_ - 1);
					break;
				case CMD_SET_SAMPLE_DELAY:
					DataLogging_SetSampleDelay_Raw(buf, datalen_ - 1);
					break;
				case CMD_GET_SENSOR_NAME:
					clearFn();
					idx = buf[0];
					if (idx >= 7) {
						writeFn(0xFE);
						break;
					}
					uint8 dat[20];
					for (i = 0; i < 20; i++) {
						dat[i] = Sensor_Names[idx][i];
					}
					writeFn(sizeof(dat));
					arrayFn(dat, sizeof(dat));
					break;
				case CMD_ENABLE_SENSOR:
					idx = buf[0];
					if (idx < 7) {
						Sensor_Enable(idx);
					}
					break;
				case CMD_DISABLE_SENSOR:
					idx = buf[0];
					if (idx < 7) {
						Sensor_Disable(idx);
					}
					break;
				case CMD_SET_SCHEDULED_START:
					ts = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8)
							| buf[3];
					Scheduling_SetStartTimeUnix(ts);
					break;
				case CMD_SET_SCHEDULED_END:
					ts = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8)
							| buf[3];
					Scheduling_SetEndTimeUnix(ts);
					break;
				case CMD_SET_RTC_TIME:
					ts = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8)
							| buf[3];
					COMMAND_SET_RTC_TIME = ts;
					break;
				case CMD_SET_CHANNEL_GAIN:
					ADC_SetGain(buf[0], buf[1]);
					break;
				}
				readingval_ = 0;
			}
		}
	} else {
		uint32 tmp = 0;
		switch (val) {
		case CMD_GET_SENSOR_VALUES:
			clearFn(); // align the data to the first byte
			sendInt24(aval[0], writeFn);
			sendInt24(aval[1], writeFn);
			sendInt24(aval[2], writeFn);
			sendInt24(aval[3], writeFn);
			break;
		case CMD_SET_SENSOR_NAME:
			readingval_ = CMD_SET_SENSOR_NAME;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_SET_SAMPLE_DELAY:
			readingval_ = CMD_SET_SAMPLE_DELAY;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_START_LOGGING:
			COMMAND_START_LOGGING = 1;
			break;
		case CMD_STOP_LOGGING:
			COMMAND_STOP_LOGGING = 1;
			break;
		case CMD_INITIALISE_CARD:
			COMMAND_INITIALIZE_CARD = 1;
			break;
		case CMD_IS_CARD_READY:
			clearFn();
			writeFn(SD_IsCardReady());
			break;
		case CMD_SET_RAW_FILETYPE:
			DataLogging_SetFormat(FILETYPE_RAW);
			break;
		case CMD_SET_CSV_FILETYPE:
			DataLogging_SetFormat(FILETYPE_CSV);
			break;
		case 0x0A: // 0x0A - 0x0F RESERVED
			break;
		case CMD_FIRMWARE_VERSION:
			clearFn();
			writeFn(sizeof(VERSION));
			arrayFn(VERSION, sizeof(VERSION));
			break;
		case CMD_GET_SENSOR_NAME:
			readingval_ = CMD_GET_SENSOR_NAME;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_GET_SAMPLE_DELAY:
			clearFn();
			tmp = DataLogging_GetSampleDelay();
			writeFn((tmp >> 24) & 0xFF);
			writeFn((tmp >> 16) & 0xFF);
			writeFn((tmp >> 8) & 0xFF);
			writeFn(tmp & 0xFF);
			break;
		case CMD_GET_FILETYPE:
			clearFn();
			writeFn(DataLogging_GetFormat());
			break;
		case CMD_ENABLE_SENSOR:
			readingval_ = CMD_ENABLE_SENSOR;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_DISABLE_SENSOR:
			readingval_ = CMD_DISABLE_SENSOR;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_GET_ENABLED_MASK:
			clearFn();
			writeFn(Sensors_Enabled);
			break;
		case CMD_SET_SCHEDULED_START:
			readingval_ = CMD_SET_SCHEDULED_START;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_SET_SCHEDULED_END:
			readingval_ = CMD_SET_SCHEDULED_END;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_ENABLE_SCHEDULING:
			Scheduling_Enable();
			break;
		case CMD_DISABLE_SCHEDULING:
			Scheduling_Disable();
			break;
		case CMD_SET_RTC_TIME:
			readingval_ = CMD_SET_RTC_TIME;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_GET_RTC_TIME:
			tmp = RTC_MostRecentTime;
			clearFn();
			writeFn((tmp >> 24) & 0xFF);
			writeFn((tmp >> 16) & 0xFF);
			writeFn((tmp >> 8) & 0xFF);
			writeFn(tmp & 0xFF);
			break;
		case CMD_SAVE_SETTINGS:
			COMMAND_SAVE_SETTINGS = 1;
			break;
		case CMD_IS_SCHEDULING_ENABLED:
			clearFn();
			writeFn(Scheduling_IsEnabled() ? 1 : 0);
			break;
		case CMD_GET_SCHEDULED_START:
			clearFn();
			tmp = Scheduling_GetStartTimeUnix();
			writeFn((tmp >> 24) & 0xFF);
			writeFn((tmp >> 16) & 0xFF);
			writeFn((tmp >> 8) & 0xFF);
			writeFn(tmp & 0xFF);
			break;
		case CMD_GET_SCHEDULED_END:
			clearFn();
			tmp = Scheduling_GetEndTimeUnix();
			writeFn((tmp >> 24) & 0xFF);
			writeFn((tmp >> 16) & 0xFF);
			writeFn((tmp >> 8) & 0xFF);
			writeFn(tmp & 0xFF);
			break;
		case CMD_SET_CHANNEL_GAIN:
			readingval_ = CMD_SET_CHANNEL_GAIN;
			lenread_ = 0;
			datalen_ = 22;
			break;
		case CMD_GET_CHANNEL_GAIN:
			clearFn();
			writeFn(ADC_GetGain(0));
			writeFn(ADC_GetGain(1));
			writeFn(ADC_GetGain(2));
			writeFn(ADC_GetGain(3));
			break;
		case CMD_GET_ACCEL_VALUES:
			clearFn();
			sendInt16(accelval[0], writeFn);
			sendInt16(accelval[1], writeFn);
			sendInt16(accelval[2], writeFn);
			break;
		case CMD_RESET_PROCESSOR:
			COMMAND_STOP_LOGGING = 1;
			COMMAND_RESET = 1;
			break;
		}
	}
}

/* [] END OF FILE */
