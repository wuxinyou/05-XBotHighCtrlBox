################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include default/subdir.mk
-include Protocol/subdir.mk
-include Drivers/subdir.mk
-include Apps/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
XBOT510_CtrlBox.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: XBOT510_CtrlBox.elf secondary-outputs

# Tool invocations
XBOT510_CtrlBox.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,XBOT510_CtrlBox.map -mmcu=atxmega64a3 -o"XBOT510_CtrlBox.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

XBOT510_CtrlBox.lss: XBOT510_CtrlBox.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S XBOT510_CtrlBox.elf  >"XBOT510_CtrlBox.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: XBOT510_CtrlBox.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atxmega64a3 XBOT510_CtrlBox.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) XBOT510_CtrlBox.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
