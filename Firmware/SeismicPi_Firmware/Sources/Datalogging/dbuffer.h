/*
 * dbuffer.h
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <PE_Types.h>

#define DBUFFER_SIZE 3072

uint16 dbufsize();
uint32 dbufread();
uint8 dbufwrite(uint32 val);

/* [] END OF FILE */
