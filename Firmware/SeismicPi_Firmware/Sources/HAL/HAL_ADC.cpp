/*
 * HAL_ADC.cpp
 *
 *  Created on: 3 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "SPI_ADC.h"
#include "ADC_DR.h"

LDD_TDeviceDataPtr SPI_ADC;
byte sndbuf[32];
byte recvbuf[32];

byte statuscom[3];
byte config0[3];
byte config1[3];
byte gainreg[3];

byte gains[4];

void ADC_ReadRegs(uint8 addr, uint8 *buf, uint8 numRegisters) {

	sndbuf[0] = 0b01000001 | ((addr & 0x1F) << 1);
	for(uint8 i = 0; i < (numRegisters*3); i++){
		sndbuf[i+1] = 0x00; // fill the remaining buffer with zeroes
	}

	SPI_ADC_SendBlock(SPI_ADC, sndbuf, 1 + (numRegisters*3));
	SPI_ADC_ReceiveBlock(SPI_ADC, recvbuf, 1 + (numRegisters*3));

	ADC_CS_Low();

	for (uint8 i = 0; i < (2 + (numRegisters*3)); i++) {
		SPI_ADC_Main(SPI_ADC);
	}

	ADC_CS_High();
	for(uint8 i = 0; i < (numRegisters*3); i++){
		buf[i] = recvbuf[i+1];
	}
}

void ADC_WriteReg(uint8 addr, uint8 *buf) {
	ADC_CS_Low();

	sndbuf[0] = 0b01000000 | ((addr & 0x1F) << 1);
	sndbuf[1] = buf[0];
	sndbuf[2] = buf[1];
	sndbuf[3] = buf[2];

	SPI_ADC_SendBlock(SPI_ADC, sndbuf, 4);
	SPI_ADC_ReceiveBlock(SPI_ADC, recvbuf, 4);

	for (uint8 i = 0; i < 5; i++) {
		SPI_ADC_Main(SPI_ADC);
	}

	ADC_CS_High();
}

void ADC_Start() {
	SPI_ADC = SPI_ADC_Init(NULL);

	ADC_ReadRegs(0x0B, gainreg, 1); // Read GAIN
	ADC_ReadRegs(0x0C, statuscom, 1); // Read STATUSCOM
	ADC_ReadRegs(0x0D, config0, 1); // Read CONFIG0
	ADC_ReadRegs(0x0E, config1, 1); // Read CONFIG1

	uint32 gtmp = (gainreg[0]<<16) | (gainreg[1]<<8) | (gainreg[2]);
	gains[3] = (gtmp >> 9) & 0x03;
	gains[2] = (gtmp >> 6) & 0x03;
	gains[1] = (gtmp >> 3) & 0x03;
	gains[0] = (gtmp     ) & 0x03;

	statuscom[0] |= 0b00010000; // Set the DR_HIZ bit to enable the DR output
	ADC_WriteReg(0x0C, statuscom);

	config0[1] = 0b11000000; // Set OSR to 110 (2048x OSR)
	ADC_WriteReg(0x0D, config0);

	config1[2] &= ~(0b01000000); // Clear the CLKEXT bit to enable the internal oscillator
	ADC_WriteReg(0x0E, config1);
}

byte tmp[12];

void ADC_GetResults(uint32 buf[]) {
	ADC_ReadRegs(0x00, tmp, 4);
	for(uint8 i = 0; i<4; i++){
		buf[i] = (tmp[3*i]<<16) | (tmp[(3*i)+1]<<8) | (tmp[(3*i)+2]);
	}
}

void ADC_InterruptEnable(){
	ADC_DR_Init(NULL);
}

uint8 gain_log2(uint8 gain){
	switch(gain){
	case 32: return 5;
	case 16: return 4;
	case 8: return 3;
	case 4: return 2;
	case 2: return 1;
	case 1: return 0;
	}
	return 0;
}

void ADC_SetGain(uint8 chan, uint8 gain){
	gains[chan] = gain_log2(gain);
	uint32 gtmp = (gains[3] << 9) | (gains[2] << 6) | (gains[1] << 3) | (gains[0]);
	gainreg[0] = (gtmp >> 16) & 0xFF;
	gainreg[1] = (gtmp >> 8 ) & 0xFF;
	gainreg[2] = (gtmp      ) & 0xFF;
	ADC_WriteReg(0x0B, gainreg);
}

uint8 ADC_GetGain(uint8 chan){
	return (1 << gains[chan]);
}
