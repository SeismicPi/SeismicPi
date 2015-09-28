# Config.txt Format

When the SeismicPi boots with an SD card inserted, it will check for a config.txt on the card, and can configure itself using the settings in this file. This is useful to automatically configure the board when it is being used as a standalone datalogger, or to ensure that a number of boards have the same configuration.

Once the configuration settings have been loaded, they are saved into the memory of the SeismicPi itself, so when the board is powered on next time, it will remember the configuration, even if the SD card is no longer present.

The settings in the file are merged with the 'default' settings, so if something is not specified in the config.txt file, its value is restored to default. (This has the side-effect that a blank config.txt may be used to restore all the configuration settings to their defaults)

This document details the settings which may be configured from the config.txt file.

### Settings format
Each line of the file may either be a comment or a setting, or blank. Comment lines and blank lines are ignored by the SeismicPi, and may be used to explain the configuration settings present in the file.

Each setting is made of a key and a value on a single line, separated by some white space (such as a space or tab). The end of a line marks the end of a particular setting. Some settings no not require a value.

Setting Name | Key | Value | Notes
-------------|-----|-------|------
Input channel names|channel_1_name<br>channel_2_name<br>channel_3_name<br>channel_4_name|1-20 characters|Value must start with a letter, number or underscore
Input channel gain|channel_1_gain<br>channel_2_gain<br>channel_3_gain<br>channel_4_gain|1-32|Sets the input gain on this channel.<br>powers of 2 only, so 1/2/4/8/16/32 are valid
Input channel enable|channel_1_enable<br>channel_2_enable<br>channel_3_enable<br>channel_4_enable|*none*|Enables this channel to be recorded when datalogging
Accelerometer channel enable|accel_x_enable<br>accel_y_enable<br>accel_z_enable|*none*|Enables this accelerometer axis to be recorded when datalogging
Sample delay|sample_delay|100-4294967295|Value is 100,000 / sample rate per second<br>This is the delay between datalog samples, in multiples of 10us. The smallest value corresponds to 1ms delay, or 1000 samples/second
Datalog file format|file_format|*csv* or *raw*|*csv* will record to a .CSV file which can be opened directly in a spreadsheet package.<br>*raw* will record to a raw binary file for lower power usage and smaller file size, but will need to be converted using the [Raw_Binary_Converter](https://github.com/SeismicPi/SeismicPi/tree/master/Firmware/Raw_Binary_Converter)
Scheduled start time|start_time|YYYY-MM-DD HH:MM:SS|The date/time to automatically start recording
Scheduled end time|end_time|YYYY-MM-DD HH:MM:SS|The date/time to automaticallt stop recording
Scheduling enable|scheduling_enable|*none*|Enables scheduled recording

### Comments
Comment lines start with a hash (#) and are ignored by the SeismicPi. These can be used to make the config.txt file more readable.

### Example

```raw
# Channel 1 settings
# Enable channel 1 with 8x gain, name it 'Geophone 1'
channel_1_name    Geophone 1
channel_1_gain    8
channel_1_enable

# Channel 2 settings
# Enable channel 2 with 2x gain, name it 'Sensor 2'
channel_2_name    Sensor 2
channel_2_gain    2
channel_2_enable

# Accelerometer settings
# Enable all 3 axes of accelerometer data
accel_x_enable
accel_y_enable
accel_z_enable

# Set sample rate to be 500 samples per second
# This value is 100,000 / 500 = 200
sample_delay      200

# Set file type to raw-binary
file_format       raw

# Setup a scheduled recording
# Start recording at 2:30pm on 27th July
# Stop recording at 3:30pm on 27th July
start_time        2015-07-27 14:30:00
end_time          2015-07-27 15:30:00
scheduling_enable
```