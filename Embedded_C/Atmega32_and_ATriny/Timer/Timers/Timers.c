/*
 * GccLibrary1.c
 *
 * Created: 4/12/2020 4:59:44 AM
 *  Author: ahmed
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint16_t counter =0 ; // Whenever the flag is raised this function will be called so the counter should remain with the same value

int main(void)
{
    
	DDRD = 0b11100000;
	// set starting position  !!
	// TIMER mode CTC
	TCCR2 &= ~(1U<<WGM20);
	TCCR2 |= (1U<<WGM21);
	OCR2 = 125; 
	sei(); // Enable special function register for interrupt
	// Enable interrupt mask (IE) register
	TIMSK |= (1U<<OCIE2); // This in related to the ISR vector function
	//Toggle the 3 LEDs every 100 ms !! (F OSC = 8 MHz), Pre-scaller (/8) counts 125 Hint(For 1 MHz, 1 ms = 1000 count, with /8, 1 ms = 125
	// lAST THING TO enable is the Hardware (I.e timer in this case)
	TCCR2 &= ~(1U<<CS00);
	TCCR2 |= (1U<<CS01);
	TCCR2 &= ~(1U<<CS02);
	// after prescalling by 8, the max count is 255 while 125 counts = 1 ms ticks.   
	// timer starts from (256- 125) 
	while (1)
	{
		if (counter == 500)
		{
			// toggle LEDs and reset timer register
			counter =0;
			PORTD ^= 0xff;
		}	
	}
    return 0;
}


// *********************ISR******** (Interrupt sent request)
//**Note: If there is any equality checking this should be done in the ISR. 

ISR(TIMER2_COMP_vect) // The code in this function should be small so the whole program does not stop for longer. (least time)
{
	
	// check on timer flag (Automatically done)
		counter ++;
		// reset timer counts to 256 - 125
		// if raised ++ counter and reset the flag	
}