################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: EDVSBoardOSM0.axf

# Tool invocations
EDVSBoardOSM0.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="EDVSBoardOSM0.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "EDVSBoardOSM0_Debug.ld" -o "EDVSBoardOSM0.axf" $(OBJS) $(USER_OBJS) $(LIBS) && arm-none-eabi-objcopy --target elf32-littlearm --verbose --strip-all --remove-section=.ARM.attributes --redefine-sym __vectors_start__=__vectors_start___core_m0app --keep-symbol __vectors_start___core_m0app --redefine-sym _data=__start_data_core_m0app --keep-symbol __start_data_core_m0app --redefine-sym _edata=__end_data_core_m0app --keep-symbol __end_data_core_m0app --remove-section=".bss*" --remove-section=".noinit*" --rename-section .ARM.exidx=".core_m0app.ARM.exidx" --rename-section .ARM.extab=".core_m0app.ARM.extab" --rename-section .text=".core_m0app" --rename-section .data=".core_m0app.data" --rename-section .data_RAM2=".core_m0app.data_RAM2" --rename-section .data_RAM3=".core_m0app.data_RAM3" --rename-section .data_RAM4=".core_m0app.data_RAM4" --rename-section .data_RAM5=".core_m0app.data_RAM5" --rename-section .data_RAM6=".core_m0app.data_RAM6" --rename-section .data_RAM7=".core_m0app.data_RAM7" --rename-section .data_RAM8=".core_m0app.data_RAM8" --rename-section .data_RAM9=".core_m0app.data_RAM9" "EDVSBoardOSM0.axf" "EDVSBoardOSM0.axf.o"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) EDVSBoardOSM0.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "EDVSBoardOSM0.axf" ; arm-none-eabi-objdump -S  "EDVSBoardOSM0.axf" > "EDVSBoardOSM0.lss" ; arm-none-eabi-objcopy -O ihex "EDVSBoardOSM0.axf" "EDVSBoardOSM0.hex" ; arm-none-eabi-objcopy -O binary "EDVSBoardOSM0.axf" "EDVSBoardOSM0.bin" ; checksum -p LPC4337_M0 -d "EDVSBoardOSM0.bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
