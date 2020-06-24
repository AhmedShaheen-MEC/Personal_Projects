################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_/Keypad.c \
../src_/Keypad_driver.c \
../src_/LCD_Driver.c \
../src_/Lock_Driver.c \
../src_/Lock_Main.c 

OBJS += \
./src_/Keypad.o \
./src_/Keypad_driver.o \
./src_/LCD_Driver.o \
./src_/Lock_Driver.o \
./src_/Lock_Main.o 

C_DEPS += \
./src_/Keypad.d \
./src_/Keypad_driver.d \
./src_/LCD_Driver.d \
./src_/Lock_Driver.d \
./src_/Lock_Main.d 


# Each subdirectory must supply rules for building sources it contributes
src_/%.o: ../src_/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


