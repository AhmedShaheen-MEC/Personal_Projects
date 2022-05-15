/*
 * stm32f446x.h
 *
 *  Created on: Nov 19, 2020
 *      Author: ahmed
 */

#ifndef INC_STM32F446X_H_
#define INC_STM32F446X_H_

#include <stdint.h>



#define __vo volatile
/*
 * Memory base addresses
 */
#define HAL_FLASH_BASEADDR			0x08000000U /*Base address of the Main Memory (i.e Flash) */
#define HAL_SRAM1_BASEADDR			0x20000000U /*Base address of SRAM1 Memory (size:112KB * 1024) */
#define HAL_SRAM2_BASEADDR			0x2001C000U /*Base address of SRAM2 Memory (size: 16KB *1024) */
#define HAL_ROM_BASEADDR			0x1FFF0000U /*Base address of System Memory (i.e. ROM) */
#define HAL_SRAM 					SRAM1_BASEADDR /* SRAM start with SRAM1 */


/*
 * AHBX, APBX, and PERIPH base addresses
 */

#define HAL_PERIPH_BASEADDR 		0x40000000U
#define HAL_APB1_BASEADDR 			HAL_PERIPH_BASEADDR
#define HAL_APB2_BASEADDR			0x40010000U
#define HAL_AHB1_BASEADDR			0x40020000U
#define HAL_AHB2_BASEADDR 			0x50000000U
#define HAL_AHB3_BASEADDR			0xA0001000U

/*
 * AHB1 Peripherals base addresses
 */

#define HAL_GPIOA_BASEADDR 			(HAL_AHB1_BASEADDR + 0x0000)
#define HAL_GPIOB_BASEADDR 			(HAL_AHB1_BASEADDR + 0x0400)
#define HAL_GPIOC_BASEADDR 			(HAL_AHB1_BASEADDR + 0x0800)
#define HAL_GPIOD_BASEADDR 			(HAL_AHB1_BASEADDR + 0x0C00)
#define HAL_GPIOE_BASEADDR 			(HAL_AHB1_BASEADDR + 0x1000)
#define HAL_GPIOF_BASEADDR 			(HAL_AHB1_BASEADDR + 0x1400)
#define HAL_GPIOG_BASEADDR 			(HAL_AHB1_BASEADDR + 0x1800)
#define HAL_GPIOH_BASEADDR 			(HAL_AHB1_BASEADDR + 0x1C00)
#define HAL_RCC_BASEADDR			(HAL_AHB1_BASEADDR + 0x3800)
/*
 * APB1 Peripherals base addresses
 */
#define HAL_I2C1_BASEADDR			(HAL_APB1_BASEADDR + 0x5400)
#define HAL_I2C2_BASEADDR			(HAL_APB1_BASEADDR + 0x5800)
#define HAL_I2C3_BASEADDR			(HAL_APB1_BASEADDR + 0x5C00)

#define HAL_SPI2_BASEADDR			(HAL_APB1_BASEADDR + 0x3800)
#define HAL_SPI3_BASEADDR			(HAL_APB1_BASEADDR + 0x3C00)
#define HAL_USART2_BASEADDR			(HAL_APB1_BASEADDR + 0x4400)
#define HAL_USART3_BASEADDR			(HAL_APB1_BASEADDR + 0x4800)

#define HAL_UART4_BASEADDR			(HAL_APB1_BASEADDR + 0x4C00)
#define HAL_UART5_BASEADDR			(HAL_APB1_BASEADDR + 0x5000)


/*
 * APB2 Peripherals base addresses
 */

#define HAL_EXTI_BASEADDR			(HAL_APB2_BASEADDR + 0x3C00)
#define HAL_SPI1_BASEADDR			(HAL_APB2_BASEADDR + 0x3000)
#define HAL_USART1_BASEADDR			(HAL_APB2_BASEADDR + 0x1000)
#define HAL_USART6_BASEADDR			(HAL_APB2_BASEADDR + 0x1400)
#define HAL_SYSCFG_BASEADDR			(HAL_APB2_BASEADDR + 0x3800)

/***********************peripheral registers structure***********************/
/*
 * This structure includes all the different registers used to configure GPIO peripherals.
 */
typedef struct{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDER;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];

}HAL_GPIO_RegDef_t;


/*
 * This structure includes all the different registers for RCC.
 */
typedef struct{

	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	uint32_t Reserved0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t Reserved1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	uint32_t Reserved2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t Reserved3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t Reserved4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t Reserved5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t Reserved6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	__vo uint32_t PLLSAICFGR;
	__vo uint32_t DCKCFGR;
	__vo uint32_t CKGATENR;
	__vo uint32_t DCKCFGR2;

}HAL_Rcc_RegDef_t;

/*
 * Peripherals' registers definitions
 * type casted to a pointer to registers struct (HAL_xxxx_RegDef_t*)
 */

#define GPIOA						((HAL_GPIO_RegDef_t*)HAL_GPIOA_BASEADDR)
#define GPIOB						((HAL_GPIO_RegDef_t*)HAL_GPIOB_BASEADDR)
#define GPIOC						((HAL_GPIO_RegDef_t*)HAL_GPIOC_BASEADDR)
#define GPIOD						((HAL_GPIO_RegDef_t*)HAL_GPIOD_BASEADDR)
#define GPIOE						((HAL_GPIO_RegDef_t*)HAL_GPIOE_BASEADDR)
#define GPIOF						((HAL_GPIO_RegDef_t*)HAL_GPIOF_BASEADDR)
#define GPIOG						((HAL_GPIO_RegDef_t*)HAL_GPIOG_BASEADDR)
#define GPIOH						((HAL_GPIO_RegDef_t*)HAL_GPIOH_BASEADDR)

#define RCC							((HAL_Rcc_RegDef_t*)HAL_RCC_BASEADDR)


/*
 * Clock enable macros for GPIOx Peripheral
 */
#define HAL_GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1 << 0))
#define HAL_GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1 << 1))
#define HAL_GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1 << 2))
#define HAL_GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define HAL_GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1 << 4))
#define HAL_GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1 << 5))
#define HAL_GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1 << 6))
#define HAL_GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1 << 7))

/*
 * Clock enable macros for SPIx Peripheral
 */
#define HAL_SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define HAL_SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define HAL_SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))

/*
 * Clock enable macros for I2Cx Peripheral
 */
#define HAL_I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define HAL_I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define HAL_I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 << 23))

/*
 * Clock enable macros for USARTx Peripheral
 */
#define HAL_USART1_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define HAL_USART2_PCLK_EN()		(RCC->APB1ENR |= (1 << 17))
#define HAL_USART3_PCLK_EN()		(RCC->APB1ENR |= (1 << 18))
#define HAL_USART6_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))

/*
 * Clock enable macros for UARTx Peripheral
 */
#define HAL_USART4_PCLK_EN()		(RCC->APB1ENR |= (1 << 19))
#define HAL_USART5_PCLK_EN()		(RCC->APB1ENR |= (1 << 20))

/*
 * Clock enable macros for SYSCFG Peripheral
 */
#define HAL_SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))


/*
 * Clock disable  macros for GPIOx Peripheral
 */
#define HAL_GPIOA_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 0))
#define HAL_GPIOB_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 1))
#define HAL_GPIOC_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 2))
#define HAL_GPIOD_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 3))
#define HAL_GPIOE_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 4))
#define HAL_GPIOF_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 5))
#define HAL_GPIOG_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 6))
#define HAL_GPIOH_PCLK_DE()		(RCC->AHB1ENR &= ~(1 << 7))

/*
 * Clock disable  macros for SPIx Peripheral
 */
#define HAL_SPI1_PCLK_DE()		(RCC->APB2ENR &= ~(1 << 12))
#define HAL_SPI2_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 14))
#define HAL_SPI3_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 15))

/*
 * Clock disable  macros for I2Cx Peripheral
 */
#define HAL_I2C1_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 21))
#define HAL_I2C2_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 22))
#define HAL_I2C3_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 23))

/*
 * Clock disable  macros for USARTx Peripheral
 */
#define HAL_USART1_PCLK_DE()		(RCC->APB2ENR &= ~(1 << 4))
#define HAL_USART2_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 17))
#define HAL_USART3_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 18))
#define HAL_USART6_PCLK_DE()		(RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock disable  macros for UARTx Peripheral
 */
#define HAL_USART4_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 19))
#define HAL_USART5_PCLK_DE()		(RCC->APB1ENR &= ~(1 << 20))

/*
 * Clock disable macros for SYSCFG Peripheral
 */
#define HAL_SYSCFG_PCLK_DE()		(RCC->APB2ENR &= ~(1 << 14))

/*
 * GPIOx Reset macros
 */
#define HAL_GPIOA_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define HAL_GPIOB_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define HAL_GPIOC_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define HAL_GPIOD_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define HAL_GPIOE_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define HAL_GPIOF_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));}while(0)
#define HAL_GPIOG_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));}while(0)
#define HAL_GPIOH_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)

/*
 *  Generic Macros
 */

#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET 	RESET

#endif /* INC_STM32F446X_H_ */
