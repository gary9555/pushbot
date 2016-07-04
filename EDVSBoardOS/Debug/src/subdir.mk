################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DVS128Chip.c \
../src/cr_start_m0.c \
../src/cr_startup_lpc43xx.c \
../src/extra_pins.c \
../src/main.c \
../src/motors.c \
../src/mpu9150.c \
../src/pushbot.c \
../src/pwm.c \
../src/sdcard.c \
../src/sensors.c \
../src/sleep.c \
../src/sysinit.c \
../src/test.c \
../src/uart.c \
../src/utils.c \
../src/xprintf.c 

OBJS += \
./src/DVS128Chip.o \
./src/cr_start_m0.o \
./src/cr_startup_lpc43xx.o \
./src/extra_pins.o \
./src/main.o \
./src/motors.o \
./src/mpu9150.o \
./src/pushbot.o \
./src/pwm.o \
./src/sdcard.o \
./src/sensors.o \
./src/sleep.o \
./src/sysinit.o \
./src/test.o \
./src/uart.o \
./src/utils.o \
./src/xprintf.o 

C_DEPS += \
./src/DVS128Chip.d \
./src/cr_start_m0.d \
./src/cr_startup_lpc43xx.d \
./src/extra_pins.d \
./src/main.d \
./src/motors.d \
./src/mpu9150.d \
./src/pushbot.d \
./src/pwm.d \
./src/sdcard.d \
./src/sensors.d \
./src/sleep.d \
./src/sysinit.d \
./src/test.d \
./src/uart.d \
./src/utils.d \
./src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__NEWLIB__ -DUSE_DMP -DMPL_LOG_NDEBUG=1 -DEMPL -DMPU9150 -DLPC4337 -D__USE_LPCOPEN -DLPC43_MULTICORE_M0APP -DDEBUG -D__CODE_RED -DCORE_M4 -D__MULTICORE_MASTER -D__MULTICORE_MASTER_SLAVE_M0APP -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/driver/include" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/eMPL-hal" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/mpl" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/mllite" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/driver/eMPL" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/inc" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/FatFs/inc" -I"/home/gary9555/Desktop/pushbot_new/lpc_chip_43xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc43xx.o: ../src/cr_startup_lpc43xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__NEWLIB__ -DUSE_DMP -DMPL_LOG_NDEBUG=1 -DEMPL -DMPU9150 -DLPC4337 -D__USE_LPCOPEN -DLPC43_MULTICORE_M0APP -DDEBUG -D__CODE_RED -DCORE_M4 -D__MULTICORE_MASTER -D__MULTICORE_MASTER_SLAVE_M0APP -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/driver/include" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/eMPL-hal" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/mpl" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/mllite" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/driver/eMPL" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/inc" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/FatFs/inc" -I"/home/gary9555/Desktop/pushbot_new/lpc_chip_43xx/inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc43xx.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


