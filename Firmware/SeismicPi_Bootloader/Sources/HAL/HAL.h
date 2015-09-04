/*
 * HAL.h
 *
 *  Created on: 12 Aug 2015
 *      Author: Steve
 */

#ifndef SOURCES_HAL_H_
#define SOURCES_HAL_H_

#include <PE_Types.h>

// UART
void UART_Start();
void UART_Print(char c);
void UART_Print(const char str[]);
void UART_Print(char str[]);
void UART_Print(char str[], uint8 strlen);
char UART_GetChar();
void UART_ClearTxBuffer();
void UART_Flush();

// SPI_SD
void SPI_SD_Start();
void SPI_SD_Stop();
void SPI_SD_SetLowSpeed();
void SPI_SD_SetHighSpeed();
void SPI_SD_Print(char c);
char SPI_SD_GetChar();
uint8 SPI_SD_IsTxDone();
uint8 SPI_SD_IsRxDone();
char SPI_SD_Transfer(char data);

// SD card
uint8 SD_Connect();
uint8 SD_IsCardReady();

// GPIO
void GPIO_Start();
void GPIO_Stop();
void SD_CS_Low();
void SD_CS_High();
void LED_Red_On();
void LED_Red_Off();
void LED_Red_Blink(uint32 delay);
void LED_Green_On();
void LED_Green_Off();
void LED_Green_Blink(uint32 delay);

// Timer
void Timer_Millis_Start();
void Timer_Millis_Stop();

// Delay
void DelayMs(uint16_t ms);

// Flash
void Flash_Start();
void Flash_Stop();
void Flash_Erase(uint32 addr, uint32 dataLen);
void Flash_Write(uint32 addr, uint8 *data, uint32 dataLen);
void Flash_Read(uint32 addr, uint8 *data, uint32 dataLen);

#endif /* SOURCES_HAL_H_ */
