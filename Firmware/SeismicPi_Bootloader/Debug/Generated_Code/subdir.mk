################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/BL_SW.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/Cpu.c \
../Generated_Code/FLASH.c \
../Generated_Code/LEDGreen.c \
../Generated_Code/LEDRed.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/SDCS.c \
../Generated_Code/SPI_SD.c \
../Generated_Code/TU1.c \
../Generated_Code/TimerMillis.c \
../Generated_Code/UART.c \
../Generated_Code/WAIT1.c \
../Generated_Code/pin_mux.c 

OBJS += \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/BL_SW.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/Cpu.o \
./Generated_Code/FLASH.o \
./Generated_Code/LEDGreen.o \
./Generated_Code/LEDRed.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SDCS.o \
./Generated_Code/SPI_SD.o \
./Generated_Code/TU1.o \
./Generated_Code/TimerMillis.o \
./Generated_Code/UART.o \
./Generated_Code/WAIT1.o \
./Generated_Code/pin_mux.o 

C_DEPS += \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/BL_SW.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/Cpu.d \
./Generated_Code/FLASH.d \
./Generated_Code/LEDGreen.d \
./Generated_Code/LEDRed.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/SDCS.d \
./Generated_Code/SPI_SD.d \
./Generated_Code/TU1.d \
./Generated_Code/TimerMillis.d \
./Generated_Code/UART.d \
./Generated_Code/WAIT1.d \
./Generated_Code/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/System" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Console" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\HAL" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Arduino" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SD" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SPI" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/PDD" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Sources" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


