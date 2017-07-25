################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/arinc429.c \
../src/capture.c \
../src/cfg.c \
../src/controls.c \
../src/cpu.c \
../src/fraquency.c \
../src/indikator.c \
../src/iwdg.c \
../src/main.c \
../src/memory.c \
../src/signal.c \
../src/starts.c \
../src/state.c \
../src/status.c \
../src/timer.c 

OBJS += \
./src/adc.o \
./src/arinc429.o \
./src/capture.o \
./src/cfg.o \
./src/controls.o \
./src/cpu.o \
./src/fraquency.o \
./src/indikator.o \
./src/iwdg.o \
./src/main.o \
./src/memory.o \
./src/signal.o \
./src/starts.o \
./src/state.o \
./src/status.o \
./src/timer.o 

C_DEPS += \
./src/adc.d \
./src/arinc429.d \
./src/capture.d \
./src/cfg.d \
./src/controls.d \
./src/cpu.d \
./src/fraquency.d \
./src/indikator.d \
./src/iwdg.d \
./src/main.d \
./src/memory.d \
./src/signal.d \
./src/starts.d \
./src/state.d \
./src/status.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m1 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D__STARTUP_CLEAR_BSS -I../inc -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\inc" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\CoreSupport" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\CMSIS\CM1\DeviceSupport\MDR1986VE1T\startup" -I"D:\Job\eclipse\workspace\ADF32Pult\1986BE1T\MDR32F9Qx_StdPeriph_Driver\inc\USB_Library" -I"D:\Job\eclipse\workspace\ADF32Pult\Periph" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


