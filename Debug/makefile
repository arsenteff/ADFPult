################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include Periph/subdir.mk
-include 1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/subdir.mk
-include 1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/subdir.mk
-include 1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/subdir.mk
-include 1986BE1T/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ADF32Pult.hex \

SECONDARY_SIZE += \
ADF32Pult.siz \


# All Target
all: ADF32Pult.elf secondary-outputs

# Tool invocations
ADF32Pult.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m1 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\startup\gcc\MDR1986VE1T.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"ADF32Pult.map" -o "ADF32Pult.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ADF32Pult.hex: ADF32Pult.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "ADF32Pult.elf"  "ADF32Pult.hex"
	@echo 'Finished building: $@'
	@echo ' '

ADF32Pult.siz: ADF32Pult.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "ADF32Pult.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) ADF32Pult.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
