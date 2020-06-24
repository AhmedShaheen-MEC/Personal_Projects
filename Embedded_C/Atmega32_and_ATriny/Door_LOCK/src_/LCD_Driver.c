/*
 * LCD_Driver.c
 *
 *  Created on: Apr 6, 2020
 *      Author: ahmed
 */

// User setUp


// End of User setUp


#include "LCD_Config.h"
#include <util/delay.h>
#include "LCD_Driver.h"

void initLCD(){

	DATA_OUT_REG_DIR = 0xFF;
	COMMAND_REG_DIR |= (OUTPUT_STATUS<<Rs) | (OUTPUT_STATUS<<E);
	DATA_OUT = 0x00;
	COMMAND_OUTPUT_DATA &= ~(1<<E);

	if (mode ==4 ){
		commandLCD(0x33);
		commandLCD(0x32);
		commandLCD(0x38);
	}
	else{

		_delay_us(2000);
		commandLCD(0x38);

	}
	commandLCD(0x0E);
	commandLCD(0x01);
	_delay_us(2000);
	commandLCD(0x06);
}

void commandLCD(char cmd){  // char = 8 bit
	if (mode == 8){
		DATA_OUT = cmd;
	}
	else if (mode == 4){
		DATA_OUT |= (cmd & 0xf0); // Hint: this code will make the other unused bits =0 !!!
		COMMAND_OUTPUT_DATA &= ~(1<<  Rs); // Command
		vHigh2Low();
		DATA_OUT |= (cmd &(1<<4));
	}

	COMMAND_OUTPUT_DATA &= ~(1<<  Rs); // Command
	vHigh2Low();

}

void lcdOut (unsigned char value){
	COMMAND_OUTPUT_DATA |= (1<<Rs);

	if (mode == 8){
		DATA_OUT= value;
	}
	else if (mode == 4){
		DATA_OUT |= (value & 0xF0);
		COMMAND_OUTPUT_DATA |= (1<<Rs);
		vHigh2Low();
		DATA_OUT |= (value &(1<<4));
	}
	COMMAND_OUTPUT_DATA |= (1<<Rs);
	vHigh2Low();

}

void lcdPrint (char * str)
{
	unsigned char i =0 ;
	 while(str[i]!=0) // Null terminator  of String
	    {lcdOut(str[i]) ; i++;}
}

void Lcd8_Set_Cursor(int a, unsigned char b)
{
	if(a == 1)
	commandLCD(FIRST_ROW + b);
	else if(a == 2)
	commandLCD(SECOND_ROW + b);
}

void vHigh2Low(void){

	COMMAND_OUTPUT_DATA |= (1<< E);
	_delay_us(1);
	COMMAND_OUTPUT_DATA &= ~(1<<E);
	_delay_us(100);
}

