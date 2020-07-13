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
#define TIMER5_CYC_FOR_5MILLISEC 1250		// (0 -> 1249)	

volatile static pTimerCallback timerTwoCallbackPointer;
volatile static pTimerCallback timerOneCallbackPointer; 
/*FUNCTION DEFINITION ********************************************************/
void timer0_start()
{
	// Configure timer mode: Fast PWM, Physical pin: OC0B
          // Enable timer 0: (RRR0 is the power reduction register)
          PRR0 &= ~(1<<PRTIM0); 
          TCNT0 = 0; 		// set timer count = 0
          // Wave generation mode: 0x03,Fast PWM, TOP=0xFF
          TCCR0A |= (1<<WGM00)| (1<<WGM01); 
          TCCR0B &= ~(1<<WGM02);
          // Inverting mode:(COM0x1:0 bits to 2)
          TCCR0A |= (1<<COM0B0);
          TCCR0A |= (1<<COM0B1);
          // Pre-scaler: Set to 0 (No- prescaler)
          TCCR0B &= ~(1<<CS01);
          TCCR0B &= ~(1<<CS02);  
          TCCR0B &= ~(1<<CS00);
}

void timer0_stop()
{
	TCCR0B &= ~(1<<CS00);
}

void timer5_start()
{
	      
	//Timer configurations:
	//Timer Mode: WGM(Wave from Generation Mode), CTC
		TCCR5A &= ~(1<<WGM51);
		TCCR5A &= ~(1<<WGM50);
		TCCR5B |= (1<<WGM52);
		TCCR5B &= ~(1<<WGM53);
	// Compare value:
		OCR5A = TIMER5_CYC_FOR_5MILLISEC; // ISR executed each 5 ms 
		TCNT5 = 0;			   	    // Reset timer cnt
	//Set Timer mask:
		TIMSK5 |= (1<<OCIE5A);
	//Prescaler: Clock select bits = 64
		//IMP: when prescaler is set time will count immediatly. 
		TCCR5B |= (1<<CS50);
		TCCR5B |= (1<<CS51);
		TCCR5B &= ~(1<<CS52);
}

void timer5_stop()
{
	TIMSK5 &= ~(1<<OCIE5A);
	TCCR5B &= ~(1<<CS52);
	TCCR5B &= ~(1<<CS51);
	TCCR5B &= ~(1<<CS50);
}

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
