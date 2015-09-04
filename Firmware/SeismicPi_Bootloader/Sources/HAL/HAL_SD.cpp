/*
 * HAL_SD.cpp
 *
 *  Created on: 12 Aug 2015
 *      Author: Steve
 */

#include "HAL.h"
#include "SPI_SD.h"
#include "SD.h"
#include "Arduino.h"

uint8 cardReady_ = 0;

LDD_TDeviceDataPtr SPI_SD;

typedef struct {
  bool EnMode;                         /* Enable/Disable device in clock configuration */
  uint32_t TxCommand;                  /* Current Tx command */
  LDD_SPIMASTER_TError ErrFlag;        /* Error flags */
  uint16_t InpRecvDataNum;             /* The counter of received characters */
  uint8_t *InpDataPtr;                 /* The buffer pointer for received characters */
  uint16_t InpDataNumReq;              /* The counter of characters to receive by ReceiveBlock() */
  uint16_t OutSentDataNum;             /* The counter of sent characters */
  uint8_t *OutDataPtr;                 /* The buffer pointer for data to be transmitted */
  uint16_t OutDataNumReq;              /* The counter of characters to be send by SendBlock() */
  uint8_t CurrentAttributeSet;         /* Current attribute set */
  LDD_TUserData *UserData;             /* User device data structure */
} SPI_SD_TDeviceData;                  /* Device data structure type */

typedef SPI_SD_TDeviceData* SPI_SD_TDeviceDataPtr ; /* Pointer to the device data structure. */

void SPI_SD_Start(){
	SPI_SD = SPI_SD_Init(NULL);
}

void SPI_SD_SetLowSpeed(){
	SPI_SD_SelectConfiguration(SPI_SD, 0, 1);
}

void SPI_SD_SetHighSpeed(){
	SPI_SD_SelectConfiguration(SPI_SD, 0, 0);
}

void SPI_SD_Stop(){
	SPI_SD_Deinit(SPI_SD);
}

static uint8 buf[2];

void SPI_SD_Print(char c){
	buf[0] = c;
	SPI_SD_SendBlock(SPI_SD, buf, 1);
}

char c = '\0';

char SPI_SD_GetChar(){
	SPI_SD_ReceiveBlock(SPI_SD, &c, 1);
	while (!SPI_SD_IsRxDone());
	return c;
}

char SPI_SD_Transfer(char snd){
	buf[0] = snd;
	SPI_SD_SendBlock(SPI_SD, buf, 1);
	SPI_SD_ReceiveBlock(SPI_SD, &c, 1);
	while (!SPI_SD_IsTxDone());
	return c;
}

uint8 SPI_SD_IsTxDone(){
	return ((SPI_SD_TDeviceDataPtr)SPI_SD)->OutDataNumReq == 0x00U;
}

uint8 SPI_SD_IsRxDone(){
	return ((SPI_SD_TDeviceDataPtr)SPI_SD)->InpDataNumReq == 0;
}

uint8 SD_Connect() {

	uint8 retVal = 1;

	SPI_SD_SetLowSpeed(); // Set the clock down to 375kHz for card init

	// Connect to SD Card
	if (!SD.begin()) {
		retVal = 0;
	}

	SPI_SD_SetHighSpeed(); // Set the clock back to 20MHz

	cardReady_ = retVal;

	return retVal;
}

uint8 SD_IsCardReady() {
	return cardReady_;
}
