#ifndef SES_MOTORFREQUENCY_H_
#define SES_MOTORFREQUENCY_H_

/*INCLUDES *******************************************************************/
#include "ses_common.h"
#include "ses_lcd.h"
#include "ses_uart.h"
#include "ses_led.h"
#include "ses_scheduler.h"
#include "util/atomic.h"
#include "ses_timer.h"

/* Global Variables *******************************************************/
#define N 	50	// Buffer size 

/* FUNCTION PROTOTYPES *******************************************************/
	
/**
 * Initializes the frequency measurment. Uses hardware timer5 of the AVR.
 */

void motorFrequency_init();

/**
 *   Using interrupts, which measure the frequency of the rising edges
 *   Motor frequency can be recognized. 
 * 
 * @return return the frequency measured. 
 *  
 */
uint16_t motorFrequency_getRecent();

/**
 * For more stabilized readings, apply the madian to a certain buffer.
 * To get the madian value.
 * @N is the Buffer size (number of samples required for the madian value)
 *  
 * @return return a madian freq. to N number of recent readings
 */

uint16_t motorFrequency_getMedian();

#endif /* SES_MOTORFREQUENCY_H_ */
