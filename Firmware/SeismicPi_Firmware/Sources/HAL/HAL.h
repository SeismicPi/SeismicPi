/*
 * HAL.h
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#ifndef SOURCES_HAL_HAL_H_
#define SOURCES_HAL_HAL_H_

#include <PE_Types.h>
#include "Time_Utils.h"

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
void SPI_SD_SetLowSpeed();
void SPI_SD_SetHighSpeed();
void SPI_SD_Stop();
void SPI_SD_BlockSend(uint8 block[], uint16_t blocklen);
void SPI_SD_BlockRead(uint8 block[], uint16_t blocklen);
void SPI_SD_Send(char c);
char SPI_SD_Recv();
char SPI_SD_Transfer(char c);

// SD Card
uint8 SD_Connect();
uint8 SD_IsCardReady();

// Timer_Millis
void Timer_Millis_Start();

// GPIOS
void GPIO_Start();
void SD_CS_Low();
void SD_CS_High();
void ADC_CS_Low();
void ADC_CS_High();
void LED_Red_On();
void LED_Red_Off();
void LED_Green_On();
void LED_Green_Off();
void LED_Green_Toggle();
void LED_Blue_On();
void LED_Blue_Off();
void LED_All_Sequence();

// RTC
void RTC_Start();
void RTC_Set(tm_elems *tm);
void RTC_Get(tm_elems *tm);

// ADC
void ADC_Start();
void ADC_GetResults(uint32 buf[]);
void ADC_InterruptEnable();
void ADC_SetGain(uint8 chan, uint8 gain);
uint8 ADC_GetGain(uint8 chan);

// Accelerometer
void Accel_Start();
void Accel_Measure();
void Accel_GetResults(uint16_t buf[]);

// Delay
void DelayMs(uint16_t ms);

// Flash
void Flash_Start();
void Flash_PutByte(uint8 addr, uint8 val);
uint8 Flash_GetByte(uint8 addr);
void Flash_PutLong(uint8 addr, uint32 val);
uint32 Flash_GetLong(uint8 addr);
void Flash_Load();
void Flash_Save();

// USB
void USB_Start();
void USB_Stop();
void USB_Update();
uint8 USB_GetRxBufSize();
uint8 USB_GetByte();
void USB_SendByte(uint8 b);

#endif /* SOURCES_HAL_HAL_H_ */
