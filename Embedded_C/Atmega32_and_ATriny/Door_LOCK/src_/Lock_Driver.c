/*
 * Lock_Driver.c
 *
 *  Created on: Apr 16, 2020
 *      Author: ahmed
 */


#include <stdbool.h>
#include<stdio.h>
#include "Lock_Driver.h"
#include "keypad_driver.h"
#include "LCD_Driver.h"

unsigned char gPassword[5] = {'1','2','3','4','5'};
unsigned char gAdminPassword[5];
unsigned char INPUT[5];
void vLockInit(void)
{
	initLCD();
	vKeypadInit();
}


unsigned char  bCheckPassword(unsigned char indicator)
{
	int i =0, star_Counter=0;
	char  keyword = 'T';
	while(i<5)
	{
		if ( indicator == 'A' )
		{
			if ( INPUT[i] != gPassword[i])
			{
				keyword = 'F';
			}
			else if (INPUT[i] == '*')
			{
				star_Counter++;
				if (star_Counter == 4)
				{
					keyword= 'C';
				}
			}
		}
		else
		{
			if (INPUT[i]  != gPassword[i])
			{
				keyword = 'F';
			}
		}
	i++;
	}
	return keyword;
}


void vSaveInput(void)
{
	int i=0;
	unsigned char pressed_key ;
	lcdPrint("Change Password");
	_delay_ms(1500);
	while (i<=4)
	{
		pressed_key = ucKeypadScan();
		Lcd8_Set_Cursor(2, 3);
		if (pressed_key!= NO_VALID_INPUT && pressed_key!= '=' && pressed_key != '+')
		{
			INPUT[i]= pressed_key;
			lcdOut('*');
			i++;
		}

	}
	lcdPrint("Password Saved");
	_delay_ms(1500);
	commandLCD(1);
}

char vPasswordRun(char keyword)
{
	unsigned char pressed_key;
	int i=0;
	char sign ='0';
		char Yes= 1;
		INPUT[0]= 0;
		INPUT[1]= 0;
		INPUT[2]= 0;
		INPUT[3]= 0;
		INPUT[4]= 0;
		lcdPrint("Trials remaining");
		_delay_ms(1500);
		commandLCD(1);
		lcdOut(((unsigned char)counter));
		_delay_ms(1500);
		commandLCD(1);
		lcdPrint("Enter Password:");

		Lcd8_Set_Cursor(2, 3);
		do
		{
			pressed_key = ucKeypadScan();
			if (pressed_key == '+')
			{
				commandLCD(1);
				Lcd8_Set_Cursor(1, 0);
				lcdPrint("Please, Repeat");
				Yes ='0';
			}
			if ( pressed_key == '=')
			{
				if (i < 4)
				{
					commandLCD(1);
					Lcd8_Set_Cursor(1, 0);
					lcdPrint("Incorrect..!");
					Yes ='0';
				}
				else if (i >= 4)
				{
					Yes=bCheckPassword(keyword);
				}
				if (Yes == 'T')
				{
					lcdPrint("Welcome Boss");
					_delay_ms(450);
					Yes='0';
					sign = '1';
					break;
				}
				else
				{
					lcdPrint("Incorrect,Try again");
					counter--;
				}
				}
			else if (pressed_key!= NO_VALID_INPUT && pressed_key!= '=' && pressed_key != '+')
			{
				INPUT[i] = pressed_key;
				lcdOut('*');
				i++;
				}

			}while(Yes == 1);
		return sign;
}

void vChangePassword(unsigned char keyword)
{
		int flag=0;
		while (flag <5)
		{
			if (keyword == 'U')
			{

				gPassword[flag] = INPUT[flag];
			}
			else
			{
				gAdminPassword[flag] = INPUT[flag];
			}
			flag++;
		}
		commandLCD(1);
		lcdPrint("Password changed");
		_delay_ms(1500);


}
