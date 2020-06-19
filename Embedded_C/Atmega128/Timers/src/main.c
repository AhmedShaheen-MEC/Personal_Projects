
#include <avr/io.h>
#include "ses_button.h"
#include "ses_led.h"
#include "ses_uart.h"

/**Toggles the red LED of the SES-board*/

int main(void) {

	led_yellowInit();
	led_greenInit();
	button_init();
	uart_init(57600);		
	led_greenOff();
	led_yellowOff();

	pButtonCallback yellowPtr;
	pButtonCallback greenPtr;
	yellowPtr = &led_yellowToggle;
	greenPtr = &led_greenToggle;
	
	button_setJoystickButtonCallback(yellowPtr);
	button_setRotaryButtonCallback(greenPtr);

	sei();	
	while (1) {
	}
	return 0;
}
