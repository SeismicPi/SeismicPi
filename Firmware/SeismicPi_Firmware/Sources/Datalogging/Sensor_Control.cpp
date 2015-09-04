/*
 * Sensor_Control.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <Sensor_Control.h>
#include <Settings_Persist.h>

#define NUM_CHANNELS 4
#define NUM_SENSORS 7 // 4 Channels + 3 Axes acceleration

char Sensor_Names[NUM_SENSORS][20] = {{"Sensor 1"}, {"Sensor 2"}, {"Sensor 3"}, {"Sensor 4"}, {"X-Acceleration"}, {"Y-Acceleration"}, {"Z-Acceleration"}};

uint8 Sensors_Enabled = 0x7F; // Enable all by default

void Sensor_SetName(uint8 index, char* name, uint8 nameLen){
    if(index<0 || index>=NUM_CHANNELS) return;
    uint8 i = 0;
    for(i=0;i<20;i++){
        if(i<nameLen){
            Sensor_Names[index][i] = name[i];
        }else{
            Sensor_Names[index][i] = 0;
        }
    }
}

void Sensor_SetName_Raw(uint8* buf, uint8 len){
    uint8 i = 0;
    uint8 sensNum = buf[0];
    char name[len-1];
    for(i=1;i<len;i++){
        if(buf[i]==0) break;
        name[i-1] = buf[i];
    }
    Sensor_SetName(sensNum, name, i-1);
}

void Sensor_Enable(uint8 index){
    if(index<0 || index>=NUM_SENSORS) return;
    Sensors_Enabled |= (1<<index);
}

void Sensor_Disable(uint8 index){
    if(index<0 || index>=NUM_SENSORS) return;
    Sensors_Enabled &= ~(1<<index);
}

uint8 Sensor_IsEnabled(uint8 index){
    return Sensors_Enabled & (1<<index);
}

/* [] END OF FILE */
