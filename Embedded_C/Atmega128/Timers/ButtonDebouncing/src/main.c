#include <avr/io.h>
#include <util/delay.h>
#include "ses_button.h"

//************************Main*****************

int main(void) {

	// initialize red LED
	led_yellowInit();
	led_greenInit(); 
	uart_init(57600);
	// create pointer to software and counter variable
	pButtonCallback checkButtonStatePtr  ;
	checkButtonStatePtr = &button_checkState;
	
	pButtonCallback yellowPtr;
	pButtonCallback greenPtr;
	yellowPtr = &led_yellowToggle;
	greenPtr = &led_greenToggle;
	
	// set button action pointer to toggle the leds
	button_setJoystickButtonCallback(yellowPtr);
	button_setRotaryButtonCallback(greenPtr);
	// pass check button to timer ISR
	timer1_setCallback(checkButtonStatePtr);
	sei();
	// initialize buttons and Timer1
	button_init(true); // Activite debouncing 
	while (1) 
	{ }
	return 0;
}