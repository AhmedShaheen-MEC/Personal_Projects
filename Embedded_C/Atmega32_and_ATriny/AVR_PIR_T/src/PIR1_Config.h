/*
 * PIR1_Config.h
 *
 *  Created on: Apr 15, 2020
 *      Author: ahmed
 */



#ifndef PIR1_CONFIG_H_
#define PIR1_CONFIG_H_
#include <avr/io.h>
// PIR IN
#define PIR_REG_DIR		DDRB
#define PIR_PIN			0
#define PIR_INPUT_DATA	PINB
// OUTPUT
#define TxLIGHT_REG_DIR		DDRD
#define TxLIGHT_PIN			4
#define TxLIGHT_DATA_OUTPUT PORTD

//



#endif /* PIR1_CONFIG_H_ */
