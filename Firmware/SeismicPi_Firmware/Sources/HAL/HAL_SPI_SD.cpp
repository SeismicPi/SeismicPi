/*
 * HAL_SPI_SD.cpp
 *
 *  Created on: 31 Jul 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "main.h"
#include "SPI_SD.h"

LDD_TDeviceDataPtr SPI_SD;

uint8 DUMMYBLOCK[512];

void SPI_SD_Start(){
	SPI_SD = SPI_SD_Init(NULL);
	for(uint16 i =0; i<sizeof(DUMMYBLOCK); i++){
		DUMMYBLOCK[i] = 0xff;
	}
}

void SPI_SD_SetLowSpeed(){
	SPI_SD_SelectConfiguration(SPI_SD, 0, 1);
}

void SPI_SD_SetHighSpeed(){
	SPI_SD_SelectConfiguration(SPI_SD, 0, 0);
}

void SPI_SD_Stop(){
	// NOTHING TO DO HERE
}

static uint8 buf[1];
void SPI_SD_Send(char c){
	buf[0] = c;
	SPI_SD_SendBlock(SPI_SD, buf, 1);
	while(!SPI_SD_GetBlockSentStatus(SPI_SD));
}

unsigned char c = '\0';
char SPI_SD_Recv(){
	SPI_SD_ReceiveBlock(SPI_SD, &c, 1);
	SPI_SD_SendBlock(SPI_SD, DUMMYBLOCK, 1);
	while(!SPI_SD_GetBlockReceivedStatus(SPI_SD));
	return c;
}

char SPI_SD_Transfer(char snd){
	buf[0] = snd;
	SPI_SD_ReceiveBlock(SPI_SD, &c, 1);
	SPI_SD_SendBlock(SPI_SD, buf, 1);
	while (!SPI_SD_GetBlockSentStatus(SPI_SD));
	return c;
}

void SPI_SD_BlockSend(uint8 block[], uint16_t blocklen){
	SPI_SD_SendBlock(SPI_SD, block, blocklen);
	while(!SPI_SD_GetBlockSentStatus(SPI_SD));
}

void SPI_SD_BlockRead(uint8 block[], uint16_t blocklen){
	for(uint16_t i = 0; i<blocklen; i++){
		block[i] = SPI_SD_Transfer(0xFF);
	}
}
