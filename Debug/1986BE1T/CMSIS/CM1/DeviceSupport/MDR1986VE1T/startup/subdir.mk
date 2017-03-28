################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/system_MDR1986VE1T.c 

OBJS += \
./1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/system_MDR1986VE1T.o 

C_DEPS += \
./1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/system_MDR1986VE1T.d 


# Each subdirectory must supply rules for building sources it contributes
1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/%.o: ../1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m1 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__STARTUP_CLEAR_BSS -I../inc -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\CoreSupport" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\startup" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc\USB_Library" -I"D:\Job\eclipse\workspace\ADF32Pult\Periph" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


