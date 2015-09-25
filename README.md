# SeismicPi
4-Channel analog input board and standalone datalogger for Raspberry Pi

## Driver Installation
### Windows
- Plug in the SeismicPi to the computer. Windows will try and fail to install the driver.
- Download https://github.com/SeismicPi/SeismicPi/blob/master/Firmware/SeismicPi_Firmware/Documentation/cdc.inf.
- Open Device Manager, locate the SeismicPi device (usually under Ports, but possibly under Other Devices), right click and select Update Driver...
- Click Browse My Computer For Driver Software, then browse to the folder containing the cdc.inf you downloaded, and click Next.
- You may be asked to confirm the installation as the driver is unsigned, but click Continue Anyway.
- The driver should successfully install, and a COM port number should be assigned.

### Linux / Mac
- No driver is required - the SeismicPi should work as soon as you plug it in.

## COM Port Name
### Windows
Open Device Manager and locate the SeismicPi under the Ports category. The serial port name will be something like COMx where x is a number.

### Raspberry Pi
If the SeismicPi is connected to the GPIO port of the Raspberry Pi, use the serial port /dev/ttyAMA0. Otherwise, see the Linux instructions below.

### Linux / Mac
Run ls /dev at a terminal. The SeismicPi will have a name like /dev/ttyACMx, where x is a number.

## Required libraries
pyserial is required for the library to access the computer's serial port.
PyQt4 and pyQtGraph are also required only to run the demo applications and the settings GUI.
Platform-specific installation instructions for these libraries can be found on their respective websites. 

## Licensing

All code is provided under the MIT license (provided) unless listed here:
 - MCUOnEclipse USB-CDC Processor Expert Component, own license visible at https://github.com/ErichStyger/mcuoneclipse/blob/master/LICENSE.txt (https://github.com/ErichStyger/mcuoneclipse)
 - Arduino SD library, GNU-GPL license (https://github.com/arduino/Arduino/tree/master/libraries/SD)
 
All documentation and diagrams are provided under the Creative Commons Attribution-ShareAlike 4.0 license, https://creativecommons.org/licenses/by-sa/4.0/
 
All text and diagrams in iPython Notebooks are provided under the Creative Commons Attribution-ShareAlike 4.0 license, but any code examples contained within are provided under the MIT license.