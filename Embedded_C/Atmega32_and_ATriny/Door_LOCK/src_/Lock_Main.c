/*
 * Lock_Main.c
 *
 *  Created on: Apr 16, 2020
 *      Author: ahmed
 */




#include "Lock_Driver.h"
#include "LCD_Driver.h"
#include <util/delay.h>
#include <avr/eeprom.h>


#define F_CPU 8000000UL
#define ADDRESS_IN_ROM		0 // cAST (void *) to convert value to pointer
#define SIZE_IN_BYTES		2

extern unsigned int counter = 3;


int main(void){
	char keyword = 'U' ;
	char Result;
	vLockInit();
	commandLCD(1);
	lcdPrint("Welcome...");
	_delay_ms(1000);
	commandLCD(1);

	unsigned char pAdminFlag = 'N';
	uint8_t * pPAdimnFlag = &pPAdimnFlag;
	eeprom_read_block (pPAdimnFlag, ADDRESS_IN_ROM, SIZE_IN_BYTES);
	unsigned char pUserFlag = 'N';

	while (1)
	{
//		if (pAdminFlag == 'N')
//		{
//			vSaveInput();
//			vChangePassword('A');
//			pAdminFlag = 'Y';
		eeprom_update_block ((void *)pPAdimnFlag, (void *) 0, SIZE_IN_BYTES);
//		}
//		if (pUserFlag == 'N')
//		{
//			vSaveInput();
//			vChangePassword('U');
//			pUserFlag = 'Y';
//		}
		Result = vPasswordRun(keyword);

		if (counter == 0 && Result != '1')
		{

			if (keyword == 'A')
			{
				lcdPrint("Fuckyou");
				_delay_ms(30000);
			}
			else
			{
			commandLCD(1);
			lcdPrint("Enter Admin Password:");
			_delay_ms(1000);
			commandLCD(1);
			counter = 3;
			keyword = 'A';
			}
		}



	}
return 0;
}


