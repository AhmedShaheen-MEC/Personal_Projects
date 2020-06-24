################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Keypad.c \
D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Keypad_driver.c 

OBJS += \
./src/Keypad/Keypad.o \
./src/Keypad/Keypad_driver.o 

C_DEPS += \
./src/Keypad/Keypad.d \
./src/Keypad/Keypad_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/Keypad/Keypad.o: D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Keypad.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Keypad/Keypad_driver.o: D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Keypad_driver.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


