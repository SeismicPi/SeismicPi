# SeismicPi Bootloader

The SeismicPi board comes installed with a bootloader which makes loading new firmware updates (or switching between firmwares) very easy. It will attempt to automatically perform a firmware upgrade if possible, otherwise it will start a serial console which allows manual control of the bootloader functions.

### Starting the bootloader

Hold down the button on the board and apply power to load into the bootloader. This is easiest performed if the board is not connected to a Raspberry Pi, since the USB cable is easier to unplug then the GPIO connector.

#### Bootloader Sequence and LED codes
1. Detect SD Card - if successful blink green LED; else light red LED, goto console.
2. Search for firmware.bin - if found, blink green LED; else blink red LED, goto console.
3. Flash firmware.bin - blink green LED once for each 512-byte block read from SD card. Once complete, restart board to boot into new application.
4. Serial console: Start a serial terminal on the Raspberry Pi GPIO interface, (see Serial Console section)

###### Example LED codes and meanings:
- Blink green, blink red: SD Card found, but firmware.bin not found (serial console starts)
- Blink red for 1-second: no sd-card found, or SD Card failed to start (serial console starts)
- Blink green twice, then blink green rapidly: Card found, firmware.bin found, loading application (board will then reboot into application)

### Serial console
The serial console is started if no firmware.bin file can be automatically installed from the card. It provides a basic terminal-like interface for the bootloader which allows manual control over the bootloader functions.
##### Commands supported
```sh
> help      # displays the list of commands and basic summaries
> reset     # resets the processor to load into the application
> initcard  # attempts to initialise an SD card
> dir       # lists files in the current directory on the card
> cd [dir]  # moves in to the folder called [dir]
> flash [file] # attemps to install the application [file]
> erase     # erases the whole program memory
```
The serial console can be used to flash files which are not in the root of the SD card, or are not called firmware.bin. This is useful if switching between firmwares for example.

### Creating Bootloadable Applications
The bootloader occupies the lowest 40kB (40960 bytes) of the Flash memory on the SeismicPi's processor. This leaves 88kB (90112 bytes) for the user application.

The application must therefore be designed to be run from base address 0xA000, rather than 0x0. If developing in Kinetis Design Studio and using Processor Expert, the following steps must be taken:
1. Open the CPU component's settings, then go to the Build Options tab, and the Generate Linker File section
2. Change the Address of the m_interrupts section to 0xA000, rather than 0x0
3. Change the Address of the m_text section to 0xA410, rather than 0x410
4. Change the Size of the m_text section to 0x15BF0, rather than 0x1FBF0
5. Generate Processer Expert files
6. Open the Linker File (Project_Settings/Linker_Files/ProcessorExpert.ld) and change the address of the m_cfmprotrom section to 0xa400 rather than 0x400 (this step will need to be performed each time Processor Expert files are generated)

The projet will need to be build and exported as a raw-binary file, which can be done by changing the build settings:
1. Open the project properties menu (*Project -> Properties*)
2. Navigate to *C/C++ Build*, then *Settings*
3. In the *Toolchains* tab, check *Create flash image* at the bottom
4. In the *Tool Settings* tab, under *Cross ARM GNU Create Flash Image*, in the *General* section, change the *Output file format* to *Raw binary*

When the project is built, a [ProjectName].bin firmware image will be created in the Debug folder. This file should be copied to the SD card to be used with the bootloader.