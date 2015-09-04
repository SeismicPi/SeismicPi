/*
 * Console.h
 *
 *  Created on: 20 Aug 2015
 *      Author: Steve
 */

#ifndef SOURCES_CONSOLE_CONSOLE_H_
#define SOURCES_CONSOLE_CONSOLE_H_

#include <PE_Types.h>

void Console_Input_Char();
void Console_Prompt();

void Console_Process();

extern uint8 COMMAND_HELP;
extern uint8 COMMAND_RESET;
extern uint8 COMMAND_INITCARD;
extern uint8 COMMAND_DIR;
extern uint8 COMMAND_CD;
extern uint8 COMMAND_FLASH;
extern uint8 COMMAND_ERASE;

void Command_Help();
void Command_InitCard();
void Command_Reset();
void Command_Dir();
void Command_Cd();
void Command_Flash();
void Command_Erase();

#endif /* SOURCES_CONSOLE_CONSOLE_H_ */
