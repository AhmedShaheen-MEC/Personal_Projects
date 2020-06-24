	/*
 * UART_Calc.h
 *
 *  Created on: Apr 5, 2020
 *      Author: ahmed
 */


#ifndef UART_CALC_H_
#define UART_CACL_H_

#include <avr/io.h>
#include "UART_ConfIg.h"

#define MYUBRR FOSC/16/BAUD-1 // Preprocessor

void uartEnable(void);
void transmitData(uint8_t data);
uint8_t readUART(void);
void transmitString (char * str);


#endif /* AVR_UART_H_ */
