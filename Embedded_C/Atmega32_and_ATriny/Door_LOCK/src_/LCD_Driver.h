/*
 * LCD_Driver.h
 *
 *  Created on: Apr 16, 2020
 *      Author: ahmed
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include <avr/delay.h>
void initLCD();
void commandLCD(char);
void lcdOut(unsigned char);
void lcdPrint(char *);
void Lcd8_Set_Cursor(int a, unsigned char b);




#endif /* LCD_DRIVER_H_ */
