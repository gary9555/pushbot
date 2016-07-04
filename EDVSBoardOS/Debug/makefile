################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include MotionDriver/mllite/subdir.mk
-include MotionDriver/eMPL-hal/subdir.mk
-include MotionDriver/driver/eMPL/subdir.mk
-include FatFs/src/option/subdir.mk
-include FatFs/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: EDVSBoardOS.axf

# Tool invocations
EDVSBoardOS.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/gary9555/Desktop/pushbot_new/lpc_chip_43xx/Debug" -L"/home/gary9555/Desktop/pushbot_new/EDVSBoardOS/MotionDriver/mpl" -Xlinker -Map="EDVSBoardOS.map" -Xlinker --gc-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T "EDVSBoardOS_Debug.ld" -o "EDVSBoardOS.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) EDVSBoardOS.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "EDVSBoardOS.axf" ; arm-none-eabi-objdump -S  "EDVSBoardOS.axf" > "EDVSBoardOS.lss" ; arm-none-eabi-objcopy -O ihex "EDVSBoardOS.axf" "EDVSBoardOS.hex" ; arm-none-eabi-objcopy -O binary "EDVSBoardOS.axf" "EDVSBoardOS.bin" ; checksum -p LPC4337 -d "EDVSBoardOS.bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
