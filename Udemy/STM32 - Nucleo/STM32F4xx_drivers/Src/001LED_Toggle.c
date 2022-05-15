  /*
 * 001LED_Toggle.c
 *
 *  Created on: Nov 24, 2020
 *      Author: ahmed
 */

#include "stm32f446x_gpio_driver.h"

void delay(void){

	for (uint32_t i = 0; i < 500000 ; i++);
}
int main(void){

	GPIO_Handle_t 	GpioLed;

	// Select output port
	GpioLed.pGPIO = GPIOA;
	// Configure pin
	GpioLed.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_Pin_Config.GPIO_PinOPType = GPIO_MODE_OP;
	GpioLed.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OP_SPEED_FAST;
	GpioLed.GPIO_Pin_Config.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_Pin_Config.GPIO_PinPuPdControl = GPIO_NO_PUSH_PULL;
	// Enable Clock
	GPIO_PeriClockControl(GPIOA, ENABLE);
	// Initialize pin output
	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
	}

	return 0;
}

