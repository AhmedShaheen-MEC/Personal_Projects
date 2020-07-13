#ifndef SES_PWM_H_
#define SES_PWM_H_

/*INCLUDES *******************************************************************/
#include "ses_common.h"
#include "ses_lcd.h"
#include "ses_uart.h"
#include "ses_led.h"
#include "ses_timer.h"
#include "ses_scheduler.h"


/* ***** PWM parameters ***** 
     Frequency: Should be large enough W.R.T to the motor transition
               and Within transistor range
     Duty cycle: (Ton/ (Ton+Toff))
     To set the duty cycle, set the OCR0B to the coresponding '
     Inverted mode has been used, (0 is maximum, 255 is minimum)
*/

/* FUNCTION PROTOTYPES *******************************************************/
/**
 * Initializes the PWM. Uses hardware timer0 of the AVR.
 */
void pwm_init(void);

/**
 * set duty cycle, Compare match value of the timer.
 * @param dutyCycle defines the T(on) time to control the V(av) 
 * on the motor terminals
 */
void pwm_setDutyCycle(uint8_t dutyCycle);

#endif /* PWM_H_ */
