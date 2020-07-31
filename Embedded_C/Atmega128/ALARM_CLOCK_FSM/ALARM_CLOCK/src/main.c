#include "alarmClock.h"
//****************Define globalvariables and function****************
Fsm theFsm;
//************************Main*****************
int main(void) 
{	
	
 	// Initializating the clock requires the following:  
	lcd_init();
     scheduler_init();				
     button_init(true);
     rotary_init();
	// LEDs  initialization
     led_yellowInit();
     led_greenInit();
     led_redInit();
	// Add buttons call back
     button_setJoystickButtonCallback(&add_joystickDispatch);
     button_setRotaryButtonCallback(&add_rotaryDispatch);
     rotary_setClockwiseCallback(&add_rotaryClockWiseDispatch);
     rotary_setCounterClockwiseCallback(&add_rotaryCounterClockWiseDispatch);
	//fsm  initialization
     fsm_init(&theFsm, clock_set_hours);
     sei();
     scheduler_run();
	return 0;
}