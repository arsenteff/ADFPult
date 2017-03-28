################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Periph/Font.c \
../Periph/Keyboard.c \
../Periph/LCD.c \
../Periph/LCDMain.c \
../Periph/LCD_b.c \
../Periph/LCDcfg.c \
../Periph/Menu.c \
../Periph/string.c 

OBJS += \
./Periph/Font.o \
./Periph/Keyboard.o \
./Periph/LCD.o \
./Periph/LCDMain.o \
./Periph/LCD_b.o \
./Periph/LCDcfg.o \
./Periph/Menu.o \
./Periph/string.o 

C_DEPS += \
./Periph/Font.d \
./Periph/Keyboard.d \
./Periph/LCD.d \
./Periph/LCDMain.d \
./Periph/LCD_b.d \
./Periph/LCDcfg.d \
./Periph/Menu.d \
./Periph/string.d 


# Each subdirectory must supply rules for building sources it contributes
Periph/%.o: ../Periph/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m1 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__STARTUP_CLEAR_BSS -I../inc -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\CoreSupport" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\startup" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc\USB_Library" -I"D:\Job\eclipse\workspace\ADF32Pult\Periph" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


