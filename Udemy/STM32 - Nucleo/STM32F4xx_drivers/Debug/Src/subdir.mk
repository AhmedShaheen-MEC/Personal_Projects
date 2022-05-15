################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/001LED_Toggle.c 

OBJS += \
./Src/001LED_Toggle.o 

C_DEPS += \
./Src/001LED_Toggle.d 


# Each subdirectory must supply rules for building sources it contributes
Src/001LED_Toggle.o: ../Src/001LED_Toggle.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"D:/Mechatronics_master/Second_semster/STM32 Course/STM32F4xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/001LED_Toggle.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

