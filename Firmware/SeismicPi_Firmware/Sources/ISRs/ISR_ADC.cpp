/*
 * ISR_ADC.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <ISR_ADC.h>
#include <main.h>
#include <dbuffer.h>
#include "HAL.h"

void ADC_CPP_ISR(){
    
	ADC_GetResults(aval);
    
}

extern "C" void ADC_ISR(){
	ADC_CPP_ISR();
}

/* [] END OF FILE */
