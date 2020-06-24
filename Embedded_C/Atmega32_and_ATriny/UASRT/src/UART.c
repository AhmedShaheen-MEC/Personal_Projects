/*
 * UART.c
 *
 *  Created on: Apr 4, 2020
 *      Author: ahmed
 */

#include "UART_Calc.h"

void uartEnable(){
	// 2 bytes register		The casting takes only the First 8 bits !!
	UBRRL = (uint8_t)(MYUBRR) ;    //send the low  8 bits of the UBRR
	UBRRH = (uint8_t)(MYUBRR>>8);//send the high 4 bits of the UBRR
	UCSRB |=((1<<RXEN)|(1<<TXEN));     //Enable transmit and enable RXENn TXENn
	UCSRC |=((1<<UCSZ0)|(1<<UCSZ1));     //Frame with 8 bit data , 1 stop bit, no parity UCSZn1 UCSZn0 , Asynchornous mode
	}

void transmitData(uint8_t data) // Unit8 because its a 8 bits register
{  while( !(UCSRA & (1<<UDRE)) ) ;// wait until the buffer is empty UDREn
	UDR=data;
}

uint8_t readUART()
{ while( !(UCSRA & (1<<RXC)) ) ;//wait until the receiving complete RXCn
	return UDR;
}


void transmitString (char * str)
{
	unsigned char i =0 ;
	 while(str[i]!=0) // Null terminator  of String
	    {transmitData(str[i]) ; i++;}
}
