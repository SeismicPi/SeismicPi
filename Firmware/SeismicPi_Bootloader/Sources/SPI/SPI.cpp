/*
* Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
* SPI Master library for arduino.
*
* This file is free software; you can redistribute it and/or modify
* it under the terms of either the GNU General Public License version 2
* or the GNU Lesser General Public License version 2.1, both as
* published by the Free Software Foundation.
*/
#include "SPI.h"
#include "HAL.h"

SPIClass SPI;
void SPIClass::begin() {
	SPI_SD_Start();
}
void SPIClass::end() {
	SPI_SD_Stop();
}
uint8 SPIClass::transfer(uint8 _data) {
	return SPI_SD_Transfer(_data);
}
void SPIClass::setBitOrder(uint8_t bitOrder)
{
}
void SPIClass::setDataMode(uint8_t mode)
{
}
void SPIClass::setClockDivider(uint8_t rate)
{
}
void SPIClass::attachInterrupt() {
}
void SPIClass::detachInterrupt() {
}
