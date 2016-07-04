################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc43xx_m0app.c \
../src/crp.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc43xx_m0app.o \
./src/crp.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc43xx_m0app.d \
./src/crp.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC43XX__ -D__MULTICORE_M0APP -I"/home/gary9555/Desktop/pushbot_new/lpc_chip_43xx/inc" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


