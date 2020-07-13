#ifndef SES_TIMER_H_
#define SES_TIMER_H_

/*INCLUDES *******************************************************************/

#include "ses_common.h"
#include "ses_led.h"
#include "avr/interrupt.h"
#include "ses_uart.h"


/*PROTOTYPES *****************************************************************/

/**
 * Starts hardware timer 0 with Fast PWM mode
 */
void timer0_start();

/** Stop timer0, by reseting the pre-scaler
 * No need for disabeling the Flag, as it has not been activated
 */
void timer0_stop();

/** Start timer 5, with freq. of 5 ms
 */
void timer5_start();

/** stop timer 5, by disabling the timer flag
 *  then, reset timer pre-scaler for energy saving
 */
void timer5_stop();

/** software timer function
 * serves as callback
 * toggle a LED each second, using flag counter.
 */
void softwareTimer(void);

 
/**type of function pointer used as timer callback
 */
typedef void (*pTimerCallback)(void);


/**
 * Sets a function to be called when the timer fires. If NULL is
 * passed, no callback is executed when the timer fires.
 *
 * @param cb  valid pointer to callback function
 */
void timer2_setCallback(pTimerCallback cb);

/**
 * Starts hardware timer 2 of MCU with a period
 * of 1 ms.
 */
void timer2_start();


/**
 * Stops timer 2.
 */
void timer2_stop();


/**
 * Sets a function to be called when the timer fires.
 *
 * @param cb  pointer to the callback function; if NULL, no callback
 *            will be executed.
 */
void timer1_setCallback(pTimerCallback cb);


/**
 * Start timer 1 of MCU to trigger on compare match every 5ms.
 */
void timer1_start();


/**
 * Stops timer 1 of the MCU if it is no longer needed.
 */
void timer1_stop();

#endif /* SES_TIMER_H_ */
