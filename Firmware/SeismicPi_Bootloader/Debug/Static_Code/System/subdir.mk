################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Static_Code/System/CPU_Init.c \
../Static_Code/System/Peripherals_Init.c \
../Static_Code/System/Vectors.c 

OBJS += \
./Static_Code/System/CPU_Init.o \
./Static_Code/System/Peripherals_Init.o \
./Static_Code/System/Vectors.o 

C_DEPS += \
./Static_Code/System/CPU_Init.d \
./Static_Code/System/Peripherals_Init.d \
./Static_Code/System/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Static_Code/System/%.o: ../Static_Code/System/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/System" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Console" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\HAL" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\Arduino" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SD" -I"C:\Users\Steve\workspace.kds\SeismicPi_Bootloader\Sources\SPI" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/PDD" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Sources" -I"C:/Users/Steve/workspace.kds/SeismicPi_Bootloader/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


