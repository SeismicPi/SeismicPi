/*
 * Command_Parser.h
 *
 *  Created on: 20 Aug 2015
 *      Author: Steve
 */

#ifndef SOURCES_CONSOLE_COMMAND_PARSER_H_
#define SOURCES_CONSOLE_COMMAND_PARSER_H_

#include <PE_Types.h>

uint8 Command_GetArg(uint8 searchstart, char result[], uint8 resultlen);
void Command_Parse(char buf[], uint8 buflen);

#endif /* SOURCES_CONSOLE_COMMAND_PARSER_H_ */
