/*
 * Command.h
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <PE_Types.h>

extern uint8 COMMAND_START_LOGGING;
extern uint8 COMMAND_STOP_LOGGING;
extern uint8 COMMAND_INITIALIZE_CARD;
extern uint8 COMMAND_SAVE_SETTINGS;
extern uint32 COMMAND_SET_RTC_TIME;
extern uint8 COMMAND_RESET;

void Command_Process_Char(uint8 val, void clearFn(), void sendFn(uint8), void arrayFn(uint8[], uint32));

/* [] END OF FILE */
