################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/HAL/HAL_ADC.cpp \
../Sources/HAL/HAL_Accel.cpp \
../Sources/HAL/HAL_Delay.cpp \
../Sources/HAL/HAL_Flash.cpp \
../Sources/HAL/HAL_GPIO.cpp \
../Sources/HAL/HAL_RTC.cpp \
../Sources/HAL/HAL_SD.cpp \
../Sources/HAL/HAL_SPI_SD.cpp \
../Sources/HAL/HAL_Timer_Millis.cpp \
../Sources/HAL/HAL_UART.cpp \
../Sources/HAL/HAL_USB.cpp 

OBJS += \
./Sources/HAL/HAL_ADC.o \
./Sources/HAL/HAL_Accel.o \
./Sources/HAL/HAL_Delay.o \
./Sources/HAL/HAL_Flash.o \
./Sources/HAL/HAL_GPIO.o \
./Sources/HAL/HAL_RTC.o \
./Sources/HAL/HAL_SD.o \
./Sources/HAL/HAL_SPI_SD.o \
./Sources/HAL/HAL_Timer_Millis.o \
./Sources/HAL/HAL_UART.o \
./Sources/HAL/HAL_USB.o 

CPP_DEPS += \
./Sources/HAL/HAL_ADC.d \
./Sources/HAL/HAL_Accel.d \
./Sources/HAL/HAL_Delay.d \
./Sources/HAL/HAL_Flash.d \
./Sources/HAL/HAL_GPIO.d \
./Sources/HAL/HAL_RTC.d \
./Sources/HAL/HAL_SD.d \
./Sources/HAL/HAL_SPI_SD.d \
./Sources/HAL/HAL_Timer_Millis.d \
./Sources/HAL/HAL_UART.d \
./Sources/HAL/HAL_USB.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/HAL/%.o: ../Sources/HAL/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/Desktop/Firmware/Static_Code/System" -I"C:\Users\Steve\Desktop\Firmware\Sources\HAL" -I"C:\Users\Steve\Desktop\Firmware\Sources\Command" -I"C:\Users\Steve\Desktop\Firmware\Sources\Datalogging" -I"C:\Users\Steve\Desktop\Firmware\Sources\ISRs" -I"C:\Users\Steve\Desktop\Firmware\Sources\RTC" -I"C:\Users\Steve\Desktop\Firmware\Sources\SDCard" -I"C:\Users\Steve\Desktop\Firmware\Sources\Settings" -I"C:\Users\Steve\Desktop\Firmware\Sources\Arduino" -I"C:\Users\Steve\Desktop\Firmware\Sources\SD" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/PDD" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/Desktop/Firmware/Sources" -I"C:/Users/Steve/Desktop/Firmware/Generated_Code" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/Peripherals" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


