/*
 * Settings_FileRead.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <Settings_FileRead.h>
#include <Sensor_Control.h>
#include <DataLogging_Control.h>
#include <Scheduling.h>
#include <HAL.h>

#define STATE_IN_KEY 1
#define STATE_WAITING_VALUE 2
#define STATE_IN_VALUE 3
#define STATE_WAITING_KEY 4
#define STATE_IN_COMMENT 5

/* Keys:
 * channel_x_name <1-20 chars>
 * channel_x_gain <1-32>
 * channel_x_enable
 * sample_delay <100-4294967295>
 * file_format <raw/csv>
 * scheduling_enable
 * start_time yyyy-mm-dd hh:mm:ss
 * end_time yyyy-mm-dd hh:mm:ss
 */

const uint8 STR_CHANNEL_x_NAME[] = {'c','h','a','n','n','e','l','_',1,'_','n','a','m','e',};
const uint8 STR_CHANNEL_x_GAIN[] = {'c','h','a','n','n','e','l','_',1,'_','g','a','i','n',};
const uint8 STR_CHANNEL_x_ENABLE[] = {'c','h','a','n','n','e','l','_',1,'_','e','n','a','b','l','e'};
const uint8 STR_ACCEL_X_ENABLE[] = "accel_x_enable";
const uint8 STR_ACCEL_Y_ENABLE[] = "accel_y_enable";
const uint8 STR_ACCEL_Z_ENABLE[] = "accel_z_enable";
const uint8 STR_DATE_FORMAT[] = {1,1,1,1,'-',1,1,'-',1,1,' ',1,1,':',1,1,':',1,1};
const uint8 STR_SAMPLE_DELAY[] = "sample_delay";
const uint8 STR_FILE_FORMAT[] = "file_format";
const uint8 STR_START_TIME[] = "start_time";
const uint8 STR_END_TIME[] = "end_time";
const uint8 STR_SCHEDULING_ENABLE[] = "scheduling_enable";
const uint8 STR_RAW[] = "raw";
const uint8 STR_CSV[] = "csv";

char key[20];
char value[20];
uint8 state = STATE_WAITING_KEY;
uint8 keylen = 0;
uint8 valuelen = 0;

uint8 is_number(uint8 c){
    return (c>='0' && c<='9');
}

uint8 is_alpha(uint8 c){
    return (c>='0' && c<='9') || (c>='A' && c<='Z') || (c>='a' && c<='z') || (c=='_');
}

uint32 ctoi(char c[], uint8 len){
    uint32 tmp = 0;
    uint8 i = 0;
    for(i=0;i<len;i++){
        tmp *= 10;
        tmp += c[i]-48;
    }
    return tmp;
}

uint8 matches(char st1[], const uint8 st2[], uint8 len){
    uint8 i = 0;
    for(i=0;i<len;i++){
        if(!(st2[i]==1 && is_number(st1[i])) && !(st2[i]==st1[i] || st2[i]==(st1[i]+32))) return 0;
    }
    return 1;
}

void process_scheduling_enable(){
    Scheduling_Enable();
}

void process_channel_enable(uint8 idx){
    Sensor_Enable(idx);
}

void process_accel_enable(uint8 idx){
	Sensor_Enable(4 + idx);
}

void process_channel_name(uint8 idx){
    Sensor_SetName(idx, value, valuelen);
}

void process_channel_gain(uint8 idx){
	ADC_SetGain(idx, ctoi(value, valuelen));
}

void process_sample_delay(){
    DataLogging_SetSampleDelay(ctoi(value, valuelen));
}

void process_file_format(){
    if(valuelen==3){
        if(matches(value, STR_RAW, valuelen)){
            DataLogging_SetFormat(FILETYPE_RAW);
        }else if(matches(value, STR_CSV, valuelen)){
            DataLogging_SetFormat(FILETYPE_CSV);
        }
    }
}

void read_time(tm_elems *tm){
    char sYear[4];
    char sMonth[2];
    char sDate[2];
    char sHour[2];
    char sMinute[2];
    char sSecond[2];
    uint8 i = 0;
    for(i=0;i<4;i++){ sYear[i] = value[i]; }
    for(i=0;i<2;i++){ sMonth[i] = value[i+5]; }
    for(i=0;i<2;i++){ sDate[i] = value[i+8]; }
    for(i=0;i<2;i++){ sHour[i] = value[i+11]; }
    for(i=0;i<2;i++){ sMinute[i] = value[i+14]; }
    for(i=0;i<2;i++){ sSecond[i] = value[i+17]; }
    tm->year = ctoi(sYear, 4)-2000;
    tm->month = ctoi(sMonth, 2);
    tm->date = ctoi(sDate, 2);
    tm->hours = ctoi(sHour, 2);
    tm->minutes = ctoi(sMinute, 2);
    tm->seconds = ctoi(sSecond, 2);
}

void process_start_time(){
    if(!matches(value, STR_DATE_FORMAT, valuelen)) return;
    tm_elems tm;
    read_time(&tm);
    Scheduling_SetStartTimeUnix(Time_UnixFromTime(&tm));
}

void process_end_time(){
    if(!matches(value, STR_DATE_FORMAT, valuelen)) return;
    tm_elems tm;
    read_time(&tm);
    Scheduling_SetEndTimeUnix(Time_UnixFromTime(&tm));
}

uint8 process_keyvalue(){
    if(keylen==17){
        if(!matches(key, STR_SCHEDULING_ENABLE, keylen)) return 1;
        process_scheduling_enable();
    }else if(keylen==16){
        if(!matches(key, STR_CHANNEL_x_ENABLE, keylen)) return 1;
        process_channel_enable(key[8]-48 - 1);
    }else if(keylen==14){
        if(matches(key, STR_CHANNEL_x_NAME, keylen)){
        	if(valuelen==0) return 2;
        	process_channel_name(key[8]-48 - 1);
        }else if(matches(key, STR_CHANNEL_x_GAIN, keylen)){
        	if(valuelen==0) return 2;
        	process_channel_gain(key[8]-48 - 1);
        }else if(matches(key, STR_ACCEL_X_ENABLE, keylen)){
        	process_accel_enable(0);
        }else if(matches(key, STR_ACCEL_Y_ENABLE, keylen)){
        	process_accel_enable(1);
        }else if(matches(key, STR_ACCEL_Z_ENABLE, keylen)){
        	process_accel_enable(2);
        }else{
        	return 1;
        }
    }else if(keylen==12){
        if(!matches(key, STR_SAMPLE_DELAY, keylen)) return 1;
        if(valuelen==0) return 2;
        process_sample_delay();
    }else if(keylen==11){
        if(!matches(key, STR_FILE_FORMAT, keylen)) return 1;
        if(valuelen==0) return 2;
        process_file_format();
    }else if(keylen==10){
        if(!matches(key, STR_START_TIME, keylen)) return 1;
        if(valuelen==0) return 2;
        process_start_time();
    }else if(keylen==8){
        if(!matches(key, STR_END_TIME, keylen)) return 1;
        if(valuelen==0) return 2;
        process_end_time();
    }else{
    	return 1;
    }
    return 0;
}

void process_char(uint8 c){
	static char uart_str[50];
    if(c=='\n' || c == '\r'){
        if(keylen>0){
        	uint8 ret = process_keyvalue();
        	if(ret == 0){
        		UART_Print("Read ");
        		for(uint8 i=0;i<keylen;i++){
        			UART_Print(key[i]);
        		}
        		UART_Print(" ");
        		for(uint8 i=0;i<valuelen;i++){
        			UART_Print(value[i]);
        		}
        		UART_Print("\n\r");
        	}else if(ret==1){
        		UART_Print("Unrecognised key: \"");
        		for(uint8 i=0;i<keylen;i++){
					UART_Print(key[i]);
				}
        		UART_Print("\"\n\r");
        	}else if(ret==2){
        		UART_Print("Expected value after key: \"");
        		for(uint8 i=0;i<keylen;i++){
					UART_Print(key[i]);
				}
				UART_Print("\"\n\r");
        	}
        }
        keylen = valuelen = 0;
        state = STATE_WAITING_KEY;
    }else{
        if(state == STATE_WAITING_KEY){
            if(c=='#'){
                state = STATE_IN_COMMENT;
            }else if(is_alpha(c)){
                key[keylen++] = c;
                state = STATE_IN_KEY;
            }
        }else if(state == STATE_IN_KEY){
            if(is_alpha(c)){
                if(keylen<sizeof(key)) key[keylen++] = c;
            }else{
                state = STATE_WAITING_VALUE;
                valuelen = 0;
            }
        }else if(state == STATE_WAITING_VALUE){
            if(is_alpha(c)){
                value[valuelen++] = c;
                state = STATE_IN_VALUE;
            }
        }else if(state == STATE_IN_VALUE){
            if(valuelen<sizeof(value)) value[valuelen++] = c;
        }
    }
}

void Settings_ProcessBuffer(uint8 buf[], uint8 buflen){
    uint8 i = 0;
    for(i=0;i<buflen;i++){
        process_char(buf[i]);
    }
}

/* [] END OF FILE */
