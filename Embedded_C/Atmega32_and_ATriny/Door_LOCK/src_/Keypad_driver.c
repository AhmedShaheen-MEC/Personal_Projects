/*
 * CFile1.c
 *
 * Created: 4/7/2020 9:19:29 PM
 *  Author: ahmed
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include "keypad_driver.h"
#include "KeypadConfig.h"

static const unsigned char g_Keypad_Mapping[4][4] ={{'7','8','9','/'},
													{'4','5','6','*'},
													{'1','2','3','-'},
													{'C','0','=','+'}};


void vKeypadInit(void)
{
	// input 0 output 0
	// SET rows as Output, and Lines as Input
	ROW0_DIR |=(1U<<ROW0);
	ROW1_DIR |=(1U<<ROW1);
	ROW2_DIR |=(1U<<ROW2);
	ROW3_DIR |=(1U<<ROW3);
	// set lines as Input:
	LINE0_DIR &= ~(1U<<LINE0);
	LINE1_DIR &= ~(1U<<LINE1);
	LINE2_DIR &= ~(1U<<LINE2);
	LINE3_DIR &= ~(1U<<LINE3);
	// set lines pull up:
	LINE0_PULLUP |= (1U<<LINE0);
	LINE1_PULLUP |= (1U<<LINE1);
	LINE2_PULLUP |= (1U<<LINE2);
	LINE3_PULLUP |= (1U<<LINE3);
	// set rows to no output state (1), when input =1 (pull ups are active) when outputs =1 (no output state)
	ROW0_DATAOUT |= (1U<<ROW0);
	ROW1_DATAOUT |= (1U<<ROW1);
	ROW2_DATAOUT |= (1U<<ROW2);
	ROW3_DATAOUT |= (1U<<ROW3);
		
}
unsigned char ucKeypadScan(void)
{
	uint8_t line= NO_VALID_INPUT;
	unsigned char result = NO_VALID_INPUT;
	uint8_t row=0;
	for (row=0; row<4; row++)
	{
		// loop on rows
		ROW0_DATAOUT |= (1U<<ROW0);
		ROW1_DATAOUT |= (1U<<ROW1);
		ROW2_DATAOUT |= (1U<<ROW2);
		ROW3_DATAOUT |= (1U<<ROW3);
		// set rows to output state:
		switch(row)
		{
		case 0:ROW0_DATAOUT &= ~(OUTPUT_STATE<<ROW0); break;
		case 1:ROW1_DATAOUT &= ~(OUTPUT_STATE<<ROW1); break;
		case 2:ROW2_DATAOUT &= ~(OUTPUT_STATE<<ROW2); break;
		case 3:ROW3_DATAOUT &= ~(OUTPUT_STATE<<ROW3); break;
		default: break;
		}
	// check lines (input)
		if((LINE0_DATAIN&(1U<<LINE0))==0)	  {line=0;}
		else if((LINE1_DATAIN&(1U<<LINE1))==0) {line=1;}
		else if((LINE2_DATAIN&(1U<<LINE2))==0) {line=2;}
		else if((LINE3_DATAIN&(1U<<LINE3))==0) {line=3;}
		else {/* MISRA */}
	// if input detected, wait until released:	
		if (line != NO_VALID_INPUT )
		{
			//wait till the input is gone
			while(INPUT_STILL_THERE == INPUT_STATE );
			//break from the loop
			
			result = g_Keypad_Mapping[row][line];
			break;
		}
	

	}
	
	return result;
}
