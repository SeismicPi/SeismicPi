/*
 * HAL_GPIO.cpp
 *
 *  Created on: 3 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "SDCS.h"
#include "SDCD.h"
#include "ADCCS.h"
#include "LEDRed.h"
#include "LEDGreen.h"
#include "LEDBlue.h"
#include "ButtonStartStop.h"

void GPIO_Start(){
	SDCS_Init(NULL);
	SDCD_Init(NULL);
	ADCCS_Init(NULL);
	LEDRed_Init(NULL);
	LEDGreen_Init(NULL);
	LEDBlue_Init(NULL);
	ButtonStartStop_Init(NULL);
}

void SD_CS_Low(){
	SDCS_ClearFieldBits(NULL, SD_CS, 1);
}

void SD_CS_High(){
	SDCS_SetFieldBits(NULL, SD_CS, 1);
}

void ADC_CS_Low(){
	ADCCS_ClearFieldBits(NULL, ADC_CS, 1);
}

void ADC_CS_High(){
	ADCCS_SetFieldBits(NULL, ADC_CS, 1);
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

void LED_Green_Toggle(){
	LEDGreen_ToggleFieldBits(NULL, LED_GREEN, 1);
}

void LED_Blue_On(){
	LEDBlue_ClearFieldBits(NULL, LED_BLUE, 1);
}

void LED_Blue_Off(){
	LEDBlue_SetFieldBits(NULL, LED_BLUE, 1);
}

void LED_All_Sequence(){
	LED_Red_On();
	DelayMs(100);
	LED_Red_Off();
	LED_Green_On();
	DelayMs(100);
	LED_Green_Off();
	LED_Blue_On();
	DelayMs(100);
	LED_Blue_Off();
}
