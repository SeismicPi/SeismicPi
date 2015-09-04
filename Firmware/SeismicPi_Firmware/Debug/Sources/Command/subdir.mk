################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/Command/Command.cpp \
../Sources/Command/UART_Command.cpp \
../Sources/Command/USB_Command.cpp 

OBJS += \
./Sources/Command/Command.o \
./Sources/Command/UART_Command.o \
./Sources/Command/USB_Command.o 

CPP_DEPS += \
./Sources/Command/Command.d \
./Sources/Command/UART_Command.d \
./Sources/Command/USB_Command.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Command/%.o: ../Sources/Command/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/Desktop/Firmware/Static_Code/System" -I"C:\Users\Steve\Desktop\Firmware\Sources\HAL" -I"C:\Users\Steve\Desktop\Firmware\Sources\Command" -I"C:\Users\Steve\Desktop\Firmware\Sources\Datalogging" -I"C:\Users\Steve\Desktop\Firmware\Sources\ISRs" -I"C:\Users\Steve\Desktop\Firmware\Sources\RTC" -I"C:\Users\Steve\Desktop\Firmware\Sources\SDCard" -I"C:\Users\Steve\Desktop\Firmware\Sources\Settings" -I"C:\Users\Steve\Desktop\Firmware\Sources\Arduino" -I"C:\Users\Steve\Desktop\Firmware\Sources\SD" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/PDD" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/Desktop/Firmware/Sources" -I"C:/Users/Steve/Desktop/Firmware/Generated_Code" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/Peripherals" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


