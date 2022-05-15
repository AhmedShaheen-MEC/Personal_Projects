/*
 * stm32f446x_gpio_driver.h
 *
 *  Created on: Nov 21, 2020
 *      Author: ahmed
 */

#ifndef INC_STM32F446X_GPIO_DRIVER_H_
#define INC_STM32F446X_GPIO_DRIVER_H_


#include "stm32f446x.h"
/*
 *This structure contains all pin configurations (Modes)
 */
typedef struct{

	uint8_t GPIO_PinNumber;			/*!<Possible values from @GPIO_PIN_NUMBERS>!*/
	uint8_t GPIO_PinMode;			/*!<Possible values from @GPIO_PIN_MODES>!*/
	uint8_t	GPIO_PinSpeed;			/*!<Possible values from @GPIO_SPEED_MODES>!*/
	uint8_t	GPIO_PinPuPdControl;	/*!<Possible values from @GPIO_PDPU_MODES>!*/
	uint8_t	GPIO_PinOPType;			/*!<Possible values from @GPIO_OUTPUT_TYPES>!*/
	uint8_t	GPIO_PinAltFunMode;		/*!<Possible values from @GPIO_PDPU_MODES>!*/


}GPIO_PinConfig_t;

/*
 * This structure handles GPIO pins
 */
typedef struct{

	HAL_GPIO_RegDef_t * pGPIO; 			/*!<Pointer to the base address of the selected GPIO pin>!*/
	GPIO_PinConfig_t  GPIO_Pin_Config;	/*!<Pointer to pin configuration settings>!*/
}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO PinNumbers
 */
#define GPIO_PIN_NO_0	0
#define GPIO_PIN_NO_1	1
#define GPIO_PIN_NO_2	2
#define GPIO_PIN_NO_3	3
#define GPIO_PIN_NO_4	4
#define GPIO_PIN_NO_5	5
#define GPIO_PIN_NO_6	6
#define GPIO_PIN_NO_7	7
#define GPIO_PIN_NO_8	8
#define GPIO_PIN_NO_9	9
#define GPIO_PIN_NO_10	10
#define GPIO_PIN_NO_11	11
#define GPIO_PIN_NO_12	12
#define GPIO_PIN_NO_13	13
#define GPIO_PIN_NO_14	14
#define GPIO_PIN_NO_15	15


/*
 * @GPIO_PIN_MODES
 * GPIO PORT Mode register
 */
#define GPIO_MODE_INP		0
#define GPIO_MODE_OP		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4		// Falling edge input mode
#define GPIO_MODE_IT_RT		5		// Rising edge input mode
#define GPIO_MODE_IT_RFT	6		// Falling and Rising edge input mode

/*
 * @GPIO_OUTPUT_TYPES
 * GPIO PORT Output mode register
 */
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1

/*
 * @GPIO_SPEED_MODES
 * GPIO PORT Output speed register
 *
 * Note: Refer to the product datasheets for the values of OSPEEDRy bits versus VDD
		 range and external load.
 */
#define GPIO_OP_SPEED_LOW		0
#define GPIO_OP_SPEED_MEDIUM	1
#define GPIO_OP_SPEED_FAST		2
#define GPIO_OP_SPEED_HIGH		3

/*
 * @GPIO_PDPU_MODES
 * GPIO PORT pull up/down register
 */
#define GPIO_NO_PUSH_PULL		0
#define GPIO_PULL_UP			1
#define GPIO_PULL_DOWN			2


/******************************************************************************
 * 						APIs supported by this driver
 * 				Check function definitions for more information
 ******************************************************************************/

/*
 * Peripheral Clock Configuration
 */
void GPIO_PeriClockControl(HAL_GPIO_RegDef_t * pGPIOx, uint8_t EnOrDi);

/*
 * Peripheral Init
 * De-init: Reset the whole GPIO peri. from RCC register
 */
void GPIO_Init(GPIO_Handle_t * pGPIOHandle);
void GPIO_DeInit(HAL_GPIO_RegDef_t * pGPIOx);

/*
 * Peripheral Output control
 */
void GPIO_WriteToOutputPin(HAL_GPIO_RegDef_t * pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WriteToOutputPort(HAL_GPIO_RegDef_t * pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(HAL_GPIO_RegDef_t * pGPIOx, uint8_t PinNumber);

/*
 * Peripheral Input control
 */
uint8_t GPIO_ReadInputPin(HAL_GPIO_RegDef_t * pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadInputPort(HAL_GPIO_RegDef_t * pGPIOx);

/*
 * IRQ Configuration and ISR Handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32F446X_GPIO_DRIVER_H_ */
