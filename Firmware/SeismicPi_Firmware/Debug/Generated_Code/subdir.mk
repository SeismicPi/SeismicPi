################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ADCCS.c \
../Generated_Code/ADC_Accel.c \
../Generated_Code/ADC_DR.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/ButtonStartStop.c \
../Generated_Code/CDC1.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/DMA1.c \
../Generated_Code/FLASH.c \
../Generated_Code/IntFlashLdd1.c \
../Generated_Code/LEDBlue.c \
../Generated_Code/LEDGreen.c \
../Generated_Code/LEDRed.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/RTC.c \
../Generated_Code/Rx1.c \
../Generated_Code/SDCD.c \
../Generated_Code/SDCS.c \
../Generated_Code/SPI_ADC.c \
../Generated_Code/SPI_SD.c \
../Generated_Code/TU1.c \
../Generated_Code/TimerMillis.c \
../Generated_Code/Tx1.c \
../Generated_Code/UART.c \
../Generated_Code/USB1.c \
../Generated_Code/pin_mux.c \
../Generated_Code/usb_cdc.c \
../Generated_Code/usb_cdc_pstn.c \
../Generated_Code/usb_class.c \
../Generated_Code/usb_dci_kinetis.c \
../Generated_Code/usb_descriptor.c \
../Generated_Code/usb_driver.c \
../Generated_Code/usb_framework.c \
../Generated_Code/wdt_kinetis.c 

OBJS += \
./Generated_Code/ADCCS.o \
./Generated_Code/ADC_Accel.o \
./Generated_Code/ADC_DR.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/ButtonStartStop.o \
./Generated_Code/CDC1.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/DMA1.o \
./Generated_Code/FLASH.o \
./Generated_Code/IntFlashLdd1.o \
./Generated_Code/LEDBlue.o \
./Generated_Code/LEDGreen.o \
./Generated_Code/LEDRed.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/RTC.o \
./Generated_Code/Rx1.o \
./Generated_Code/SDCD.o \
./Generated_Code/SDCS.o \
./Generated_Code/SPI_ADC.o \
./Generated_Code/SPI_SD.o \
./Generated_Code/TU1.o \
./Generated_Code/TimerMillis.o \
./Generated_Code/Tx1.o \
./Generated_Code/UART.o \
./Generated_Code/USB1.o \
./Generated_Code/pin_mux.o \
./Generated_Code/usb_cdc.o \
./Generated_Code/usb_cdc_pstn.o \
./Generated_Code/usb_class.o \
./Generated_Code/usb_dci_kinetis.o \
./Generated_Code/usb_descriptor.o \
./Generated_Code/usb_driver.o \
./Generated_Code/usb_framework.o \
./Generated_Code/wdt_kinetis.o 

C_DEPS += \
./Generated_Code/ADCCS.d \
./Generated_Code/ADC_Accel.d \
./Generated_Code/ADC_DR.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/ButtonStartStop.d \
./Generated_Code/CDC1.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/DMA1.d \
./Generated_Code/FLASH.d \
./Generated_Code/IntFlashLdd1.d \
./Generated_Code/LEDBlue.d \
./Generated_Code/LEDGreen.d \
./Generated_Code/LEDRed.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/RTC.d \
./Generated_Code/Rx1.d \
./Generated_Code/SDCD.d \
./Generated_Code/SDCS.d \
./Generated_Code/SPI_ADC.d \
./Generated_Code/SPI_SD.d \
./Generated_Code/TU1.d \
./Generated_Code/TimerMillis.d \
./Generated_Code/Tx1.d \
./Generated_Code/UART.d \
./Generated_Code/USB1.d \
./Generated_Code/pin_mux.d \
./Generated_Code/usb_cdc.d \
./Generated_Code/usb_cdc_pstn.d \
./Generated_Code/usb_class.d \
./Generated_Code/usb_dci_kinetis.d \
./Generated_Code/usb_descriptor.d \
./Generated_Code/usb_driver.d \
./Generated_Code/usb_framework.d \
./Generated_Code/wdt_kinetis.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/Desktop/Firmware/Static_Code/System" -I"C:\Users\Steve\Desktop\Firmware\Sources\HAL" -I"C:\Users\Steve\Desktop\Firmware\Sources\Arduino" -I"C:\Users\Steve\Desktop\Firmware\Sources\SD" -I"C:\Users\Steve\Desktop\Firmware\Sources\Command" -I"C:\Users\Steve\Desktop\Firmware\Sources\Datalogging" -I"C:\Users\Steve\Desktop\Firmware\Sources\ISRs" -I"C:\Users\Steve\Desktop\Firmware\Sources\RTC" -I"C:\Users\Steve\Desktop\Firmware\Sources\SDCard" -I"C:\Users\Steve\Desktop\Firmware\Sources\Settings" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/PDD" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/Desktop/Firmware/Sources" -I"C:/Users/Steve/Desktop/Firmware/Generated_Code" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


