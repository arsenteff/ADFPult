################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/startup_MDR1986VE1T.S 

OBJS += \
./1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/startup_MDR1986VE1T.o 

S_UPPER_DEPS += \
./1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/startup_MDR1986VE1T.d 


# Each subdirectory must supply rules for building sources it contributes
1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/%.o: ../1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m1 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -D__STARTUP_CLEAR_BSS -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


