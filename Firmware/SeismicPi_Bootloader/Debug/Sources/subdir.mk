################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/bootloader.cpp 

C_SRCS += \
../Sources/Events.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/bootloader.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/main.d 

CPP_DEPS += \
./Sources/bootloader.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/System" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Console" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\HAL" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Arduino" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SD" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SPI" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/PDD" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Sources" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/System" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Console" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\HAL" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Arduino" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SD" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SPI" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/PDD" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Sources" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Generated_Code" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


