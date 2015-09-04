/*
 * HAL_SD.cpp
 *
 *  Created on: 17 Aug 2015
 *      Author: Jamie
 */

#include "HAL.h"
#include "SD.h"

uint8 cardReady_ = 0;

uint8 SD_Connect(){

    uint8 retVal = 1;

    SPI_SD_SetLowSpeed(); // Set the clock down to 375kHz for card init

    // Connect to SD Card
    if(!SD.begin()){
        retVal = 0;
    }

    SPI_SD_SetHighSpeed(); // Set the clock back to 20MHz

    cardReady_ = retVal;

    return retVal;
}

uint8 SD_IsCardReady(){
    return cardReady_;
}


