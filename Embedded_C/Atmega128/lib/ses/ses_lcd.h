#ifndef SES_LCD_H_
#define SES_LCD_H_

/*INCLUDES-------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/*EXTERNALS------------------------------------------------------------------*/

/**
 * File descriptor for lcd. You can use this in conjunction with fprintf.
 * Example fprintf(lcdout, "Hello World %d\n",2012);
 *
 */
extern FILE* lcdout;


/*PROTOTYPES-----------------------------------------------------------------*/

/**
 * Initializes the display print facility.
 */
void lcd_init();

/**
 * Jumps character cursor to specified position. The position
 * of the cursor determines the position of the next character
 * which is written.
 *
 * @param p		horizontal position of cursor
 * @param r		row of cursor
 */
void lcd_setCursor(uint8_t p, uint8_t r);


/**
 * Writes a character to the position of the cursor. Afterwards
 * the cursor position is increased by one.
 *
 * @param chr 	character to write to display
 *
 */
void lcd_putc(char chr);


/**
 * set or clear pixel in line at horizontal position p
 * @param line	line (8 lines per row)
 * @param p		horizontal position
 * @param onOff	set if true, clear otherwise
 */
void lcd_setPixel(uint8_t line, uint8_t p, bool onOff);


/**
 * Clears the whole display.
 */
void lcd_clear();



#endif /* SES_LCD_H_ */
