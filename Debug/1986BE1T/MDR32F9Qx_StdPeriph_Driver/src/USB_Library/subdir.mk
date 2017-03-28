################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/MDR32F9Qx_usb_CDC.c \
../1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/MDR32F9Qx_usb_device.c 

OBJS += \
./1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/MDR32F9Qx_usb_CDC.o \
./1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/MDR32F9Qx_usb_device.o 

C_DEPS += \
./1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/MDR32F9Qx_usb_CDC.d \
./1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/MDR32F9Qx_usb_device.d 


# Each subdirectory must supply rules for building sources it contributes
1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/%.o: ../1986BE1T/MDR32F9Qx_StdPeriph_Driver/src/USB_Library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m1 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__STARTUP_CLEAR_BSS -I../inc -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\CoreSupport" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\startup" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc\USB_Library" -I"D:\Job\eclipse\workspace\ADF32Pult\Periph" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


