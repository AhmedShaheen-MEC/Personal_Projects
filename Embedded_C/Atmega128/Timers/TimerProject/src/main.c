#include <avr/io.h>
#include <util/delay.h>
#include "ses_timer.h"

//Define global variables:
#define ONE_SECOND	 		200
void softwareTimer(void);
volatile static uint16_t flagCounter;
//************************Main*****************

int main(void) {

	// initialize red LED
	led_redInit(); 
	uart_init(57600);
	// create pointer to software and counter variable
	pTimerCallback timerTwoCallbackPointer;
	timerTwoCallbackPointer = &softwareTimer;
	// void softwareTimer(void) serve as call back
	timer2_setCallback(timerTwoCallbackPointer);
	sei();
	// initialize timer 2 
	timer1_start();
	while (1) 
	{ }
	return 0;
}

void softwareTimer(void)
{
	//Timer flag 	raised --> This function will ba called directly
	flagCounter++;

	if (flagCounter == ONE_SECOND)
	{
		// Reset Counter
		flagCounter = 0;
		// Toggle LED
		led_redToggle();
	}
}