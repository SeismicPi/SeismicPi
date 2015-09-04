################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/RTC/Scheduling.cpp \
../Sources/RTC/Time_Utils.cpp 

OBJS += \
./Sources/RTC/Scheduling.o \
./Sources/RTC/Time_Utils.o 

CPP_DEPS += \
./Sources/RTC/Scheduling.d \
./Sources/RTC/Time_Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/RTC/%.o: ../Sources/RTC/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/Desktop/Firmware/Static_Code/System" -I"C:\Users\Steve\Desktop\Firmware\Sources\HAL" -I"C:\Users\Steve\Desktop\Firmware\Sources\Command" -I"C:\Users\Steve\Desktop\Firmware\Sources\Datalogging" -I"C:\Users\Steve\Desktop\Firmware\Sources\ISRs" -I"C:\Users\Steve\Desktop\Firmware\Sources\RTC" -I"C:\Users\Steve\Desktop\Firmware\Sources\SDCard" -I"C:\Users\Steve\Desktop\Firmware\Sources\Settings" -I"C:\Users\Steve\Desktop\Firmware\Sources\Arduino" -I"C:\Users\Steve\Desktop\Firmware\Sources\SD" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/PDD" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/Desktop/Firmware/Sources" -I"C:/Users/Steve/Desktop/Firmware/Generated_Code" -I"C:/Users/Steve/Desktop/Firmware/Static_Code/Peripherals" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


