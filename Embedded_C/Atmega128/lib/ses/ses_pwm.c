/* INCLUDES **************************************************/
#include "ses_timer.h"
#include "ses_pwm.h"

/* PRIVATE VARIABLES **************************************************/
/** list of scheduled tasks */


/*FUNCTION DEFINITION *************************************************/

void pwm_init(void)
{  
	// set pin5 in PORTG to output
     PORTG &= ~(1<<PIN5);
     timer0_start();      
}


void pwm_setDutyCycle(uint8_t dutyCycle)
{
     OCR0B = dutyCycle;
}

