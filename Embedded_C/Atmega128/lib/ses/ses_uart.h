#ifndef SES_UART_H_
#define SES_UART_H_

/*INCLUDES-------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>


/*EXTERNALS------------------------------------------------------------------*/

/**
 * File descriptor for UART. You can use this in conjunction with fprintf.
 * Example fprintf(uartout, "Hello World %d\n",2017);
 */
extern FILE* uartout;


/*PROTOTYPES-----------------------------------------------------------------*/


/**
 * Initializes UART with given baud rate. By default, 8 databits and
 * 1 stop bit are used.
 * @param baudrate	baudrate of uart (e.g. 57600)
 */
void uart_init(uint32_t baudrate);


/**
 *	Reads a character from UART.
 *	@return character
 */
uint8_t uart_getc();


/**
 * Writes a character to UART.
 * @param chr character to write
 */
void uart_putc(uint8_t chr);



#endif /* SES_UART_H_ */
