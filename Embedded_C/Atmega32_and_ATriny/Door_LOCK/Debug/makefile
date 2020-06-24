################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src_/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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
LSS += \
GSM_HEX.lss \

FLASH_IMAGE += \
GSM_HEX.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: GSM_HEX.elf secondary-outputs

# Tool invocations
GSM_HEX.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,GSM_HEX.map -mmcu=atmega16 -o "GSM_HEX.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

GSM_HEX.lss: GSM_HEX.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S GSM_HEX.elf  >"GSM_HEX.lss"
	@echo 'Finished building: $@'
	@echo ' '

GSM_HEX.hex: GSM_HEX.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex GSM_HEX.elf  "GSM_HEX.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: GSM_HEX.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 GSM_HEX.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: GSM_HEX.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm16 -Uflash:w:GSM_HEX.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) GSM_HEX.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
