/*
 * stm32f446x_gpio_driver.c
 *
 *  Created on: Nov 21, 2020
 *      Author: ahmed
 */

#include "stm32f446x_gpio_driver.h"

/****************************************************
 *
 * @fn				- GPIO_PeriClockControl
 *
 * @brief			- This function enable or disables the clock for the given GPIO port
 *
 * @param[pGPIOx]	- Base address of the GPIO peripheral
 * @param[EnOrDi]	- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_PeriClockControl(HAL_GPIO_RegDef_t * pGPIOx, uint8_t EnOrDi){

	if (EnOrDi == ENABLE)
	{
		if (pGPIOx == GPIOA)
		{
			HAL_GPIOA_PCLK_EN();
		}else if (pGPIOx == GPIOB)
		{
			HAL_GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			HAL_GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD)
		{
			HAL_GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE)
		{
			HAL_GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF)
		{
			HAL_GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG)
		{
			HAL_GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH)
		{
			HAL_GPIOH_PCLK_EN();
		}
	}else
	{
		if (pGPIOx == GPIOA)
		{
			HAL_GPIOA_PCLK_DE();
		}else if (pGPIOx == GPIOB)
		{
			HAL_GPIOB_PCLK_DE();
		}else if (pGPIOx == GPIOC)
		{
			HAL_GPIOC_PCLK_DE();
		}else if (pGPIOx == GPIOD)
		{
			HAL_GPIOD_PCLK_DE();
		}else if (pGPIOx == GPIOE)
		{
			HAL_GPIOE_PCLK_DE();
		}else if (pGPIOx == GPIOF)
		{
			HAL_GPIOF_PCLK_DE();
		}else if (pGPIOx == GPIOG)
		{
			HAL_GPIOG_PCLK_DE();
		}else if (pGPIOx == GPIOH)
		{
			HAL_GPIOH_PCLK_DE();
		}
	}
}

/****************************************************
 *
 * @fn				- GPIO_Init
 *
 * @brief			- This function enable the given GPIO port
 *
 * @param[pGPIOHandle] - Contains a pointer to the base address, and port required initialization settings
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_Init(GPIO_Handle_t * pGPIOHandle){

	uint32_t temp = 0; // temp. register
	// 1. Mode configuration of the GPIO port, <= 3, i.e. (0 - 3)
	if (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode<= GPIO_MODE_ANALOG){

		// non interrupt mode
		temp = pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
		pGPIOHandle->pGPIO->MODER &= ~( 0x3 <<pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);		// Reset the bits first to avoid conflicts, 0x3 "Must be 11" clears 2 bits at once.
		pGPIOHandle->pGPIO->MODER |= temp;

	}else
	{

	}

	// 2. Speed configuration
	temp = 0;
	temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
	pGPIOHandle->pGPIO->OSPEEDER &= ~( 0x3 <<pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);		// Reset the bits first to avoid conflicts, 0x3 "Must be 11" clears 2 bits at once.
	pGPIOHandle->pGPIO->OSPEEDER |= temp;

	// 3. Pull up/down settings
	temp = 0;
	temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
	pGPIOHandle->pGPIO->PUPDR &= ~( 0x3 <<pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);		// Reset the bits first to avoid conflicts, 0x3 "Must be 11" clears 2 bits at once.
	pGPIOHandle->pGPIO->PUPDR |= temp;

	// 4. Output type config.
	temp = 0;
	temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinOPType << (pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
	pGPIOHandle->pGPIO->OTYPER &= ~( 0x1 <<pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);		// Reset the bits first to avoid conflicts, 0x1 "Must be 1" clears 2 bits at once.
	pGPIOHandle->pGPIO->OTYPER |= temp;

	// 5. Alt. functionality config.
	if (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint32_t temp1 = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber / 8; 		// Divide by 8 define [Low or High] register
		uint32_t temp2 = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber % 8;		// Module by 8 to know the shift value
		pGPIOHandle->pGPIO->AFR[temp1] &= ~( 0xF <<pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);		// Reset the bits first to avoid conflicts, 0xF "Must be 1111" clears 2 bits at once.
		pGPIOHandle->pGPIO->AFR[temp1] |= (pGPIOHandle->GPIO_Pin_Config.GPIO_PinAltFunMode << (4 * temp2));
	}
}

/****************************************************
 *
 * @fn				- GPIO_DeInit
 *
 * @brief			- This function reset all the registers in the given GPIO port
 *
 * @param[pGPIOx]	- Base address of the GPIO peripheral
 *
 * @return			- none
 *
 * @Note			- Uses RCC peripheral, AHB1 register, 1 -> 0
 */
void GPIO_DeInit(HAL_GPIO_RegDef_t * pGPIOx){

	if (pGPIOx == GPIOA)
	{
		HAL_GPIOA_REG_RESET();
	}else if (pGPIOx == GPIOB)
	{
		HAL_GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		HAL_GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		HAL_GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		HAL_GPIOE_REG_RESET();
	}else if (pGPIOx == GPIOF)
	{
		HAL_GPIOF_REG_RESET();
	}else if (pGPIOx == GPIOG)
	{
		HAL_GPIOG_REG_RESET();
	}else if (pGPIOx == GPIOH)
	{
		HAL_GPIOH_REG_RESET();
	}
}

/****************************************************
 *
 * @fn				- GPIO_WriteToOutputPin
 *
 * @brief			- This function writes a given value to a specific pin in the given GPIO port
 *
 * @param[pGPIOx]	- Base address of GPIO register
 * @param[PinNumber]- Specific Pin in the GPIO port
 * @param[value]	- SET or RESERT macros
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_WriteToOutputPin(HAL_GPIO_RegDef_t * pGPIOx, uint8_t PinNumber, uint8_t value){

	if(value == GPIO_PIN_SET)
	{
		// write ONE
		pGPIOx->ODR |= (1 << PinNumber);
	}else
	{
		// write ZERO
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

/****************************************************
 *
 * @fn				- GPIO_WriteToOutputPort
 *
 * @brief			- This function writes a given value to a complete GPIO port
 *
 * @param[pGPIOx]	- Base address of GPIO register
 * @param[value]	- SET or RESERT macros
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_WriteToOutputPort(HAL_GPIO_RegDef_t * pGPIOx, uint16_t value){

	pGPIOx->ODR = value;
}

/****************************************************
 *
 * @fn				- GPIO_ToggleOutputPin
 *
 * @brief			- This function toggles a specific pin in the given GPIO port
 *
 * @param[pGPIOx]	- Base address of GPIO register
 * @param[PinNumber]- Specific Pin in the GPIO port (0 - 15)
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_ToggleOutputPin(HAL_GPIO_RegDef_t * pGPIOx, uint8_t PinNumber){

	pGPIOx->ODR ^= (1 << PinNumber);
}

/****************************************************
 *
 * @fn				- GPIO_ReadInputPin
 *
 * @brief			- This function reads a specific pin value in the given GPIO port
 *
 * @param[pGPIOx]	- Base address of GPIO register
 * @param[PinNumber]- Specific Pin in the GPIO port (0 - 15)
 *
 * @return			- value presented in the pin register
 *
 * @Note			- none
 */

uint8_t GPIO_ReadInputPin(HAL_GPIO_RegDef_t * pGPIOx, uint8_t PinNumber){

	uint8_t value = 0;
	value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001); // Mask all the bits and leave only the first one
	return value;
}

/****************************************************
 *
 * @fn				- GPIO_ReadInputPort
 *
 * @brief			- This function reads the value presented in the given GPIO port
 *
 * @param[pGPIOx]	- Base address of GPIO register
 *
 * @return			- value presented on the whole port!
 *
 * @Note			- none
 */
uint16_t GPIO_ReadInputPort(HAL_GPIO_RegDef_t * pGPIOx){

	uint16_t value = 0;
	value = (uint16_t) (pGPIOx->IDR); // Mask all the bits and leave only the first one
	return value;
}

/****************************************************
 *
 * @fn				- GPIO_IRQConfig
 *
 * @brief			- This function configure GPIO peri. interrupts.
 *
 * @param[IRQNumber]-
 * @param[IRQPriority]-
 * @param[EnOrDi]	- DISABLE OR ENABLE macros
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi){

}

/****************************************************
 *
 * @fn				- GPIO_IRQHandling
 *
 * @brief			- This function handles any interrupt fired by the GPIO peripheral pins
 *
 * @param[PinNumber]- Pin number which has triggered the interrupt
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_IRQHandling(uint8_t PinNumber){

}
