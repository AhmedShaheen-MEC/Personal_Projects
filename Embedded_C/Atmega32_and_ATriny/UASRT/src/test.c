///*
// * test.c
// *
// *  Created on: Apr 5, 2020
// *      Author: ahmed
// */
//
//#include <avr/io.h>
//#include <util/delay.h>
//#define input 0
//#define output 1
//#define F_CPU 8000000
//
//
//void uartEnable();
//void transmitData(uint8_t);
//uint8_t readUART();
//void transmitString (char);
//
//int main(){
//
//	DDRD  |= (1<<PIN6)| (1<<PIN5) | (1<<PIN4) | (1<<7);
//	unsigned char data  = "N";
//	uartEnable();
//	PORTD = 0xFF;
//	while(1)
//	{
//		PORTD ^= (1<<5);
//		for (int i = 0; i <= 10; i++)
//		{
//			transmitData("A");
//		}
//
//		/*
//		data = readUART();
//		PORTD ^= (1<<PIN7);
//		if (data == 'C')
//		{
//			PORTD |= (1<<PIN5);
//			PORTD &= ~(1<<PIN6);
//			transmitString('O');
//		}
//		else if (data = 'B')
//		{
//			PORTD |= (1<<PIN6);
//			PORTD &= ~(1<<PIN5);
//			transmitString('D');
//		}
//		*/
//
//	}
//	return 0;
//}
//
//
//

/*
 * ATmega.c
 *
 * Created: 6/2/2020 3:56:45 AM
 *  Author: ahmed
 */

#include <avr/io.h>
// input 0
// output 1

#define F_CPU 8000000UL

void uartEnable();
void transmitData(uint8_t);
unsigned char readUART(void);
void transmitString (char);
void uartDisable(void);

int main(){

	DDRD  |=  (1<<PIN5) | (1<<PIN4) | (1<<7);
	DDRD &= ~((1<<PIN6));
	DDRC |= (1<<PIN0);
	uartEnable();

	unsigned char data = '0';
	while(1)
	{

		if ((PIND & (1<<PIN6)) == (1<<PIN6))
		{
			transmitData('C');
			PORTD |= (1<<PIN5);
			PORTC &= ~(1<<PIN0);

		}
		else
		{
			transmitData('D');
			PORTD &= ~(1<<PIN5);
			PORTC |= (1<<PIN0);
		}
		/*
		data = readUART();
		PORTD ^= (1<<PIN7);
		if (data == 'C')
		{
			PORTD |= (1<<PIN5);
			PORTD &= ~(1<<PIN6);
			transmitString('O');
		}
		else if (data = 'B')
		{
			PORTD |= (1<<PIN6);
			PORTD &= ~(1<<PIN5);
			transmitString('D');
		}
		*/

	}
	return 0;
}
