/*
 * Command_Parser.cpp
 *
 *  Created on: 20 Aug 2015
 *      Author: Jamie
 */

#include "Command_Parser.h"
#include "Console.h"
#include "HAL.h"

enum{
	STATE_WAITING_CMD,
	STATE_READING_CMD,
	STATE_WAITING_ARGS,
	STATE_READING_ARGS
} STATE = STATE_WAITING_CMD;

char cmd[16];
uint8 cmdlen = 0;
char args[64];
uint8 arglen = 0;

const char CMD_HELP[] = "help";
const char CMD_RESET[] = "reset";
const char CMD_INITCARD[] = "initcard";
const char CMD_DIR[] = "dir";
const char CMD_CD[] = "cd";
const char CMD_FLASH[] = "flash";
const char CMD_ERASE[] = "erase";

char toLower(char c){
	if(c>='A' && c<='Z') return c+32;
	return c;
}

uint8 Command_GetArg(uint8 searchstart, char result[], uint8 resultlen){
	bool foundstart = false;
	uint8 s = 0;
	for(uint8 i=searchstart;i<arglen;i++){
		if(args[i]!=' ' && args[i]!='\0'){
			if(!foundstart){
				foundstart = true;
			}
			if(s < resultlen){
				result[s] = args[i];
			}
			s++;
		}else{
			if(foundstart){
				break;
			}
		}
	}
	return s;
}

bool matches(char val[], const char check[], uint8 len){
	for(uint8 i=0; i<len; i++){
		if(val[i] != check[i]) return false;
	}
	return true;
}

void Command_Parse(char buf[], uint8 buflen){
	uint8 i = 0;
	STATE = STATE_WAITING_CMD;
	cmdlen = 0;
	arglen = 0;
	for(i=0; i<buflen; i++){
		char c = buf[i];
		if(STATE == STATE_WAITING_CMD){
			if(c!=' '){
				STATE = STATE_READING_CMD;
				cmd[cmdlen++] = toLower(c);
			}
		}else if(STATE == STATE_READING_CMD){
			if(c!=' '){
				if(cmdlen<sizeof(cmd)){
					cmd[cmdlen++] = toLower(c);
				}
			}else{
				STATE = STATE_WAITING_ARGS;
			}
		}else if(STATE == STATE_WAITING_ARGS){
			if(c!=' '){
				STATE = STATE_READING_ARGS;
				args[arglen++] = toLower(c);
			}
		}else if(STATE == STATE_READING_ARGS){
			args[arglen++] = toLower(c);
		}
	}
	if(cmdlen>0){
		if(cmdlen==4 && matches(cmd, CMD_HELP, cmdlen)){
			COMMAND_HELP = 1;
		}else if(cmdlen==5 && matches(cmd, CMD_RESET, cmdlen)){
			COMMAND_RESET = 1;
		}else if(cmdlen==8 && matches(cmd, CMD_INITCARD, cmdlen)){
			COMMAND_INITCARD = 1;
		}else if(cmdlen==3 && matches(cmd, CMD_DIR, cmdlen)){
			COMMAND_DIR = 1;
		}else if(cmdlen==2 && matches(cmd, CMD_CD, cmdlen)){
			COMMAND_CD = 1;
		}else if(cmdlen==5 && matches(cmd, CMD_FLASH, cmdlen)){
			COMMAND_FLASH = 1;
		}else if(cmdlen==5 && matches(cmd, CMD_ERASE, cmdlen)){
			COMMAND_ERASE = 1;
		}else{
			UART_Print("Invalid command, use 'help' for help\n\r");
			Console_Prompt();
		}
	}else{
		Console_Prompt();
	}
}
