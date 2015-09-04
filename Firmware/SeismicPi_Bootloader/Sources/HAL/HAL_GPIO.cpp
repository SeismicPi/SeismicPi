/*
 * HAL_GPIO.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: Steve
 */

#include "HAL.h"

#include "SDCS.h"
#include "LEDRed.h"
#include "LEDGreen.h"

void GPIO_Start(){
	SDCS_Init(NULL);
	LEDRed_Init(NULL);
	LEDGreen_Init(NULL);
}

void GPIO_Stop(){
	SDCS_Deinit(NULL);
	LEDRed_Deinit(NULL);
	LEDGreen_Deinit(NULL);
}

void SD_CS_Low() {
	SDCS_ClearFieldBits(NULL, SD_CS, 1);
}

void SD_CS_High() {
	SDCS_SetFieldBits(NULL, SD_CS, 1);
}

void LED_Red_On(){
	LEDRed_ClearFieldBits(NULL, LED_RED, 1);
}

void LED_Red_Off(){
	LEDRed_SetFieldBits(NULL, LED_RED, 1);
}

void LED_Green_On(){
	LEDGreen_ClearFieldBits(NULL, LED_GREEN, 1);
}

void LED_Green_Off(){
	LEDGreen_SetFieldBits(NULL, LED_GREEN, 1);
}

void LED_Red_Blink(uint32 delay) {
	LED_Red_On();
	DelayMs(delay);
	LED_Red_Off();
	DelayMs(delay);
}

void LED_Green_Blink(uint32 delay) {
	LED_Green_On();
	DelayMs(delay);
	LED_Green_Off();
	DelayMs(delay);
}
