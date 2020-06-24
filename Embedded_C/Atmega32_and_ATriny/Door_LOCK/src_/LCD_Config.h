/*
 * LCD_Config.h
 *
 *  Created on: Apr 16, 2020
 *      Author: ahmed
 */
#include <avr/io.h>
#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


// LCD OUTPUT Data 8 Pins Mode:
#define DATA_OUT_REG_DIR	DDRB
#define DATA_OUT			PORTB
#define Rs 0
#define E 1
// Comand signal  PINs
#define COMMAND_REG_DIR		DDRC
#define COMMAND_OUTPUT_DATA	PORTC
#define INPUT_STATUS 	0
#define OUTPUT_STATUS	1
// Set LCD Mode:
#define mode 8
#define MAX_X 5		// To do (Make function to check the limits)!!
#define FIRST_ROW 0x80
#define SECOND_ROW 0xC0


#endif /* LCD_CONFIG_H_ */
