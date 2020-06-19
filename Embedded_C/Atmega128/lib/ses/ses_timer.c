/** CTC Mode discription: Clear Time on compare Match
  * in normal mode timer is cleared when overflow occures
  * in CTC mode timer is cleared when the compare match happen
  * to SET the value of comperance use OCR  register, OCF flag will trigger it.
 */


/* INCLUDES ******************************************************************/
#include "ses_timer.h"
#include <avr/interrupt.h>

/* DEFINES & MACROS **********************************************************/
#define TIMER1_CYC_FOR_5MILLISEC 0x04E2
#define TIMER2_CYC_FOR_1MILLISEC 249

volatile static pTimerCallback timerTwoCallbackPointer;
volatile static pTimerCallback timerOneCallbackPointer; 
/*FUNCTION DEFINITION ********************************************************/


void timer2_setCallback(pTimerCallback cb) 
{
	timerTwoCallbackPointer = cb;
}

void timer2_start() 
{
	//Time configurations:
	// To access time actual value use TCNT2 register and for Timer flags (TIFR2).
	//Timer Mode: WGM(Wave from Generation Mode), CTC (0x4)"0100"
	TCCR2A |= (1<<WGM21);
	TCCR2A &= ~(1<<WGM20);
	OCR2A = TIMER2_CYC_FOR_1MILLISEC; // Clear each 250 counts		
	//Set Timer mask:
	TIMSK2 |= (1<<OCIE2A);
	//Prescaler: Clock select bits 
	TCCR2B |= (1<<CS22);
	TCCR2B &= ~(1<<CS21);
	TCCR2B &= ~(1<<CS20); //IMP: when prescaler is set time will count immediatly. 
	// Time will start count from 0 untill 250.
}

void timer2_stop() 
{
    //Disable timer Mask:
     TIMSK2 &= ~(1<<OCIE2A);
     TCCR2B &= ~(1<<CS22);
	TCCR2B &= ~(1<<CS21);
	TCCR2B &= ~(1<<CS20);
}

void timer1_setCallback(pTimerCallback cb) 
{
	timerOneCallbackPointer = cb;
}


void timer1_start() 
{
	
	//Time configurations:
	// To access time actual value use TCNT2 register and for Timer flags (TIFR2).
	//Timer Mode: WGM(Wave from Generation Mode), CTC
	TCCR1A &= ~(1<<WGM11);
	TCCR1A &= ~(1<<WGM10);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	OCR1AH = (uint8_t)(TIMER1_CYC_FOR_5MILLISEC>>8); // Clear each 1250(0x04E2) counts == 5 ms		
	OCR1AL = (uint8_t) (TIMER1_CYC_FOR_5MILLISEC); 
	//Set Timer mask:
	TIMSK1 |= (1<<OCIE1A);
	//Prescaler: Clock select bits 
	TCCR1B &= ~(1<<CS22);
	TCCR1B |= (1<<CS21);
	TCCR1B |= (1<<CS20); //IMP: when prescaler is set time will count immediatly. 
	// Time will start count from 0 untill 1250.
}


void timer1_stop() 
{
	TIMSK1 &= ~(1<<OCIE1A);
	TCCR2B &= ~(1<<CS22);
	TCCR2B &= ~(1<<CS21);
	TCCR2B &= ~(1<<CS20);
}

ISR(TIMER1_COMPA_vect) 
{
	timerOneCallbackPointer();
}

ISR(TIMER2_COMPA_vect) 
{
	timerTwoCallbackPointer();
}
