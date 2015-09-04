# SeismicPi Communication Protocol

When connected to a computer via USB, or a Raspberry Pi via the GPIO connector, the SeismicPi presents a serial interface which can be used with the bundled Python API or a user-written communication wrapper.
This document serves to detail the supported commands so that communication APIs for the SeismicPi may be written in other languages.

### Command Format
Each command packet is sent as a single command byte followed by optional data for that command. Some commands require a data section to be sent to provide additional arguments for example. If a data section is required, it is transmitted as a simple stream of bytes, prefixed with the length of the data section (up to 22 bytes). The length calculation does not include the length byte itself. If no data section is required, only the command byte is sent.

Command Byte | Function | Data Section | Reply
-------------|----------|--------------|------
0x01|Get sensor values|*none*|byte 0-2: big-endian int24 with current value of sensor 1<br>byte 3-5: big-endian int24 with current value of sensor 2<br>byte 6-8: big-endian int24 with current value of sensor 3<br>byte 9-11: big-endian int24 with current value of sensor 4
0x02|Set sensor name|byte 0: sensor number (0-6)<br>byte 1+: name (ASCII, up to 20 chars)|*none*
0x03|Set sample delay|byte 0-3 big-endian int32 giving time between samples (in multiples of 10us)|*none*
0x04|Start logging|*none*|*none*
0x05|Stop logging|*none*|*none*
0x06|Initialize card|*none*|*none*
0x07|Is card ready?|*none*|byte 0: 1 if card is ready, 0 if not
0x08|Set Raw filetype|*none*|*none*
0x09|Set CSV filetype|*none*|*none*
0x0A-F|*Reserved for future file types*||
0x11|Report firmware version|*none*|byte 0: reply length<br> byte 1+: firmware version string
0x12|Get sensor name|byte 0: sensor number (0-6)|byte 0: reply length<br>byte 1+: sensor name string<br>*If sensor number is invalid, reply byte 0 is 0xFE*
0x13|Get sample delay|*none*|byte 0-3: big-endian int32, time between samples (as a multiple of 10us)
0x14|Get file type|*none*|byte 0: 1 for Raw, 2 for CSV
0x15|Enable sensor|byte 0: sensor number (0-6)|*none*
0x16|Disable sensor|byte 0: sensor number (0-6)|*none*
0x17|Get sensor enabled mask|*none*|byte 0: mask of enabled sensors - e.g. if sensor index 3 is enabled (Channel 4) then bit 3 will be set
0x18|Set scheduled start time|byte 0-3: big-endian int32 unix timestamp for scheduled datalogging start time|*none*
0x19|Set scheduled end time|byte 0-3: big-endian int32 unix timestamp for scheduled datalogging end time|*none*
0x20|Enable scheduling|*none*|*none*
0x21|Disable scheduling|*none*|*none*
0x22|Set RTC time|byte 0-3: big-endian int32 unix timestamp of current time|*none*
0x23|Get RTC time|*none*|byte 0-3: big-endian int32 unix timestamp of current RTC time as known by the board
0x24|Save settings to EEPROM|*none*|*none*
0x25|Is scheduling enabled|*none*|byte 0: 1 if scheduling is enabled, 0 if not
0x26|Get scheduled start time|*none*|byte 0-3: big-endian int32 of scheduled datalogging start time
0x27|Get scheduled end time|*none*|byte 0-3: big-endian int32 of scheduled datalogging end time
0x28|Set channel gain|byte 0: sensor number (0-3)<br>byte 1: gain (1-32, powers of 2 only)|*none*
0x29|Get channel gain|byte 0: sensor number(0-3)|byte 0: gain (1-32)
0x30|Get accelerometer values|*none*|byte 0-1: big-endian int16 with current value of x-acceleration<br>byte 2-3: big-endian int16 with current value of y-acceleration<br>byte 4-5: big-endian int16 with current value of z-acceleration
0xF0|Reset processor in 2 seconds|*none*|*none*