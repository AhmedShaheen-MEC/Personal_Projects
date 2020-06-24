/*
 * KeypadConfig.h
 *
 * Created: 4/7/2020 10:08:05 PM
 *  Author: ahmed
 */ 


#ifndef KEYPADCONFIG_H_
#define KEYPADCONFIG_H_

#include <avr/io.h>

#define ROW0			0
#define ROW0_DIR		DDRD
#define ROW0_DATAOUT	PORTD

#define ROW1			1
#define ROW1_DIR		DDRD
#define ROW1_DATAOUT	PORTD

#define ROW2			2
#define ROW2_DIR		DDRD
#define ROW2_DATAOUT	PORTD

#define ROW3			3
#define ROW3_DIR		DDRD
#define ROW3_DATAOUT	PORTD

#define LINE0			4
#define LINE0_DIR		DDRD
#define LINE0_DATAIN	PIND
#define LINE0_PULLUP	PORTD

#define LINE1			5
#define LINE1_DIR		DDRD
#define LINE1_DATAIN	PIND
#define LINE1_PULLUP	PORTD

#define LINE2			6
#define LINE2_DIR		DDRD
#define LINE2_DATAIN	PIND
#define LINE2_PULLUP	PORTD

#define LINE3			7
#define LINE3_DIR		DDRD
#define LINE3_DATAIN	PIND
#define LINE3_PULLUP	PORTD


#endif /* KEYPADCONFIG_H_ */