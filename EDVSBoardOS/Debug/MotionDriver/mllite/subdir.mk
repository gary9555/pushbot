################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MotionDriver/mllite/data_builder.c \
../MotionDriver/mllite/hal_outputs.c \
../MotionDriver/mllite/message_layer.c \
../MotionDriver/mllite/ml_math_func.c \
../MotionDriver/mllite/mlmath.c \
../MotionDriver/mllite/mpl.c \
../MotionDriver/mllite/results_holder.c \
../MotionDriver/mllite/start_manager.c \
../MotionDriver/mllite/storage_manager.c 

OBJS += \
./MotionDriver/mllite/data_builder.o \
./MotionDriver/mllite/hal_outputs.o \
./MotionDriver/mllite/message_layer.o \
./MotionDriver/mllite/ml_math_func.o \
./MotionDriver/mllite/mlmath.o \
./MotionDriver/mllite/mpl.o \
./MotionDriver/mllite/results_holder.o \
./MotionDriver/mllite/start_manager.o \
./MotionDriver/mllite/storage_manager.o 

C_DEPS += \
./MotionDriver/mllite/data_builder.d \
./MotionDriver/mllite/hal_outputs.d \
./MotionDriver/mllite/message_layer.d \
./MotionDriver/mllite/ml_math_func.d \
./MotionDriver/mllite/mlmath.d \
./MotionDriver/mllite/mpl.d \
./MotionDriver/mllite/results_holder.d \
./MotionDriver/mllite/start_manager.d \
./MotionDriver/mllite/storage_manager.d 


# Each subdirectory must supply rules for building sources it contributes
MotionDriver/mllite/%.o: ../MotionDriver/mllite/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__NEWLIB__ -DUSE_DMP -DMPL_LOG_NDEBUG=1 -DEMPL -DMPU9150 -DLPC4337 -D__USE_LPCOPEN -DLPC43_MULTICORE_M0APP -DDEBUG -D__CODE_RED -DCORE_M4 -D__MULTICORE_MASTER -D__MULTICORE_MASTER_SLAVE_M0APP -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/driver/include" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/eMPL-hal" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/mpl" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/mllite" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/driver/eMPL" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/inc" -I"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/FatFs/inc" -I"/home/gary9555/Desktop/pushbot_new/lpc_chip_43xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


