/*
 * Console.cpp
 *
 *  Created on: 20 Aug 2015
 *      Author: Steve
 */

#include "bootloader.h"
#include "Console.h"
#include "HAL.h"
#include "Command_Parser.h"
#include "Cpu.h"

#include <stdio.h>

#include "SD.h"

char linebuffer[64];
uint8 lbufsize = 0;

char cwd[64] = "/";
uint8 cwdlen = 1;

uint8 COMMAND_HELP = 0;
uint8 COMMAND_RESET = 0;
uint8 COMMAND_INITCARD = 0;
uint8 COMMAND_DIR = 0;
uint8 COMMAND_CD = 0;
uint8 COMMAND_FLASH = 0;
uint8 COMMAND_ERASE = 0;

void Console_Input_Char(){
	char c = UART_GetChar();
	if(c==10 || c==13){
		UART_Print("\n\r");
		Command_Parse(linebuffer, lbufsize);
		lbufsize = 0;
	}else if(c==127){ // backspace
		if(lbufsize>0){
			linebuffer[--lbufsize] = 0;
			UART_Print(c);
		}
	}else if(c >= 32){ // not a control-char
		if(lbufsize<sizeof(linebuffer)){
			linebuffer[lbufsize++] = c;
			UART_Print(c);
		}
	}
}

void Console_Process(){
	if(COMMAND_HELP){
		COMMAND_HELP = 0;
		Command_Help();
		Console_Prompt();
	}else if(COMMAND_RESET){
		COMMAND_RESET = 0;
		Command_Reset();
		Console_Prompt();
	}else if(COMMAND_INITCARD){
		COMMAND_INITCARD = 0;
		Command_InitCard();
		Console_Prompt();
	}else if(COMMAND_DIR){
		COMMAND_DIR = 0;
		Command_Dir();
		Console_Prompt();
	}else if(COMMAND_CD){
		COMMAND_CD = 0;
		Command_Cd();
		Console_Prompt();
	}else if(COMMAND_FLASH){
		COMMAND_FLASH = 0;
		Command_Flash();
		Console_Prompt();
	}else if(COMMAND_ERASE){
		COMMAND_ERASE = 0;
		Command_Erase();
		Console_Prompt();
	}
}

void Console_Prompt(){
	if(SD_IsCardReady()){
		UART_Print(cwd);
		UART_Print(" ");
	}else{
		UART_Print("<no card> ");
	}
	UART_Print("> ");
}

void Command_Help(){
	UART_Print("help             ; Shows this screen\n\r");
	UART_Print("reset            ; Resets the processor\n\r");
	UART_Print("initcard         ; Tries to initalise the SD card\n\r");
	UART_Print("dir              ; Lists files in current directory\n\r");
	UART_Print("cd [path]        ; Changes into folder [path]\n\r");
	UART_Print("                    if [path] is .., moves to parent\n\r");
	UART_Print("flash [file]     ; Flashes [file] into memory\n\r");
	UART_Print("erase            ; Erase the program memory\n\r");
}

void Command_Reset(){
	UART_Flush();
	DelayMs(100);
	Cpu_SystemReset();
}

void Command_InitCard(){
	if(SD_Connect()){
		UART_Print("Card initialised.\n\r");
		cwd[0] = '/';
		cwd[1] = 0;
		cwdlen = 1;
	}else{
		UART_Print("Failed!\n\r");
	}
}

void Command_Dir(){
	File dir = SD.open(cwd);
	dir.rewindDirectory(); // this line cures headaches

	char uart_str[32];
	while(true){
		File entry = dir.openNextFile();
		if(!entry) break;
		UART_Print(entry.name());
		if(!entry.isDirectory()){
			UART_Print("\t\t");
			sprintf(uart_str, "%lu", entry.size());
			UART_Print(uart_str);
		}
		UART_Print("\n\r");
		entry.close();
	}
	dir.close();
}

void Command_Cd(){
	char path[8];
	uint8 pathlen = Command_GetArg(0, path, sizeof(path));
	if(pathlen>8) pathlen = 8; // only 8.3 filenames are supported
	if(pathlen == 0){
		UART_Print("Usage: cd <path>\n\r");
	}else{
		if(pathlen==2 && path[0]=='.' && path[1]=='.'){
			while(cwd[cwdlen-1] != '/'){
				cwd[--cwdlen] = 0;
			}
			cwd[--cwdlen] = 0; // remove the trailing slash
			if(cwdlen==0){
				cwd[0] = '/';
				cwd[1] = 0;
				cwdlen = 1;
			}
		}else{
			char cwdtmp[sizeof(cwd)];
			if(cwdlen+pathlen>sizeof(cwdtmp)){
				UART_Print("Resultant path is too long!\n\r");
				return;
			}
			for(uint8 i=0;i<cwdlen;i++){
				cwdtmp[i] = cwd[i];
			}
			if(cwdlen>1){
				cwdtmp[cwdlen] = '/';
				cwdlen++;
			}
			for(uint8 i=0;i<pathlen;i++){
				cwdtmp[cwdlen+i] = path[i];
			}
			cwdtmp[cwdlen+pathlen] = 0; // ensure string is null-terminated
			if(SD.exists(cwdtmp)){
				File dir = SD.open(cwdtmp);
				if(dir.isDirectory()){
					for(uint8 i=0;i<sizeof(cwdtmp);i++){
						cwd[i] = cwdtmp[i];
					}
					cwdlen += pathlen;
				}else{
					UART_Print("Not a directory!\n\r");
				}
				dir.close();
			}else{
				UART_Print("Path not found!\n\r");
				if(cwdlen>1) cwdlen--;
			}
		}
	}
}

void Command_Flash(){
	char path[12];
	uint8 pathlen = Command_GetArg(0, path, sizeof(path));
	if(pathlen>12) pathlen = 12; // only 8.3 filenames are supported
	if(pathlen == 0){
		UART_Print("Usage: flash <firmware file>\n\r");
	}else{
		char pathtmp[sizeof(cwd)];
		if(cwdlen+pathlen>sizeof(pathtmp)){
			UART_Print("Resultant path is too long!\n\r");
			return;
		}
		for(uint8 i=0;i<cwdlen;i++){
			pathtmp[i] = cwd[i];
		}
		for(uint8 i=0;i<cwdlen;i++){
			pathtmp[i] = cwd[i];
		}
		if(cwdlen>1){
			pathtmp[cwdlen] = '/';
			cwdlen++;
		}
		for(uint8 i=0;i<pathlen;i++){
			pathtmp[cwdlen+i] = path[i];
		}
		if(cwdlen>1){
			cwdlen--;
		}
		pathtmp[cwdlen+pathlen] = 0; // ensure string is null-terminated
		if(SD.exists(pathtmp)){
			BL_Flash(pathtmp);
		}else{
			UART_Print("File not found!\n\r");
		}
	}
}


void Command_Erase(){
	BL_Erase();
}
