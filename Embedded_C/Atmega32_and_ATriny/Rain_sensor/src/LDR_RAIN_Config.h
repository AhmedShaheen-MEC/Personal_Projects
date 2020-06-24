/*
 * LDR_RAIN_Config.h
 *
 *  Created on: Apr 15, 2020
 *      Author: ahmed
 */

#ifndef LDR_RAIN_CONFIG_H_
#define LDR_RAIN_CONFIG_H_

#include <avr/io.h>
#include <util/delay.h>
// LDR:
#define LDR_PIN			0
#define LDR_REG_DIR		DDRD
#define LDR_INPUT_DATA	PIND

/*
// Rain: To Do (Editing will be in Driver main will not be affected)

#define RAIN_PIN
#define RAIN_REG_DIR
#define RAIN_INPUT_DATA
*/
// Rain Output (TX)
#define TxRAIN_PIN			3
#define TxRAIN_REG_DIR		DDRD
#define TxRAIN_DATA_OUTPUT	PORTD

// LDR Output (TX)
#define TxLIGHT_PIN			4
#define TxLIGHT_REG_DIR		DDRD
#define TxLIGHT_DATA_OUTPUT	PORTD

#endif /* LDR_RAIN_CONFIG_H_ */
