################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/stm32f446x_gpio_driver.c 

OBJS += \
./drivers/Src/stm32f446x_gpio_driver.o 

C_DEPS += \
./drivers/Src/stm32f446x_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/stm32f446x_gpio_driver.o: ../drivers/Src/stm32f446x_gpio_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"D:/Mechatronics_master/Second_semster/STM32 Course/STM32F4xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f446x_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

