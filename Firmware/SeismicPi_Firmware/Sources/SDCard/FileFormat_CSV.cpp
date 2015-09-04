/*
 * FileFormat_CSV.cpp
 *
 *  Created on: 28 Jul 2015
 *      Author: Jamie
 */
 
#include <FileFormat_CSV.h>
#include <datafile.h>
#include <Sensor_Control.h>
#include <DataLogging_Control.h>

void Datafile_Write_CSV(uint32 *data){
    char str[40];
    uint8 i=0;
    sprintf(str, "%lu", data[0]);
    dataFile.print(str);
    for(i=0;i<7;i++){
        if(Sensor_IsEnabled(i)){
            sprintf(str, ",%ld", (int32)data[i+1]);
            dataFile.print(str);
        }
    }
    dataFile.println();
}

bool Datafile_Open_CSV(){
    char name[12];
    DataLogging_GetNewFileName(name, "CSV");
    dataFile = SD.open(name, FILE_WRITE);
    if(!dataFile){
		return FALSE;
	}
    dataFile.print("Time");
    uint8 i=0;
    for(i=0;i<7;i++){
        if(Sensor_IsEnabled(i)){
            dataFile.print(",\""); // Wrap names in quotes
            dataFile.print(Sensor_Names[i]);
            dataFile.print("\"");
        }
    }
    dataFile.println();
    return TRUE;
}

/* [] END OF FILE */
