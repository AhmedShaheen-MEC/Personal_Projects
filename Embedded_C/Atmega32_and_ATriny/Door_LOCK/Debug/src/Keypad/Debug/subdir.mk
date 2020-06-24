################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Debug/LCD_Driver.c 

O_SRCS += \
D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Debug/Keypad.o \
D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Debug/Keypad_driver.o 

OBJS += \
./src/Keypad/Debug/LCD_Driver.o 

C_DEPS += \
./src/Keypad/Debug/LCD_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/Keypad/Debug/LCD_Driver.o: D:/Eng.Progrmas/Master's\ programs/LCD_HEX/src/Keypad/Debug/LCD_Driver.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


