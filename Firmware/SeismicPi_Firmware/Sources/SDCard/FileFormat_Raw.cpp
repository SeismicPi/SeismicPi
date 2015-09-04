/*
 * FileFormat_Raw.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */

#include <FileFormat_Raw.h>
#include <datafile.h>
#include <Sensor_Control.h>
#include <DataLogging_Control.h>

void Datafile_Write_Raw(uint32 *data){
    uint8 i = 0;
    // Millis timestamp
    dataFile.write((data[0]>>24) & 0xFF);
    dataFile.write((data[0]>>16) & 0xFF);
    dataFile.write((data[0]>>8) & 0xFF);
    dataFile.write(data[0] & 0xFF);
    // 24-bit values
    for(i=1;i<5;i++){
        if(Sensor_IsEnabled(i-1)){
            uint32 val = data[i];
            dataFile.write((val>>16)&0xFF);
            dataFile.write((val>>8)&0xFF);
            dataFile.write(val & 0xFF);
        }
    }
    // 16-bit values
    for(i=5;i<8;i++){
    	if(Sensor_IsEnabled(i-1)){
			uint32 val = data[i];
			dataFile.write((val>>8)&0xFF);
			dataFile.write(val & 0xFF);
		}
    }
}

bool Datafile_Open_Raw(){
    char name[12];
    DataLogging_GetNewFileName(name, "BIN");
    dataFile = SD.open(name, FILE_WRITE);
    if(!dataFile){
    	return FALSE;
    }
    uint8 i = 0;
    uint8 j = 0;
    dataFile.write(Sensors_Enabled);
    for(i=0;i<7;i++){
        if(Sensor_IsEnabled(i)){
            for(j=0;j<20;j++){
                dataFile.write(Sensor_Names[i][j]);
            }
        }
    }
    return TRUE;
}

/* [] END OF FILE */
