################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/HAL/HAL_Delay.cpp \
../Sources/HAL/HAL_Flash.cpp \
../Sources/HAL/HAL_GPIO.cpp \
../Sources/HAL/HAL_SD.cpp \
../Sources/HAL/HAL_Timer_Millis.cpp \
../Sources/HAL/HAL_UART.cpp 

OBJS += \
./Sources/HAL/HAL_Delay.o \
./Sources/HAL/HAL_Flash.o \
./Sources/HAL/HAL_GPIO.o \
./Sources/HAL/HAL_SD.o \
./Sources/HAL/HAL_Timer_Millis.o \
./Sources/HAL/HAL_UART.o 

CPP_DEPS += \
./Sources/HAL/HAL_Delay.d \
./Sources/HAL/HAL_Flash.d \
./Sources/HAL/HAL_GPIO.d \
./Sources/HAL/HAL_SD.d \
./Sources/HAL/HAL_Timer_Millis.d \
./Sources/HAL/HAL_UART.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/HAL/%.o: ../Sources/HAL/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/System" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Console" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\HAL" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Arduino" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SD" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SPI" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/PDD" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Sources" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Generated_Code" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


