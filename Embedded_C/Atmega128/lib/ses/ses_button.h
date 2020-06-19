#ifndef SES_BUTTON_H_
#define SES_BUTTON_H_

/* INCLUDES ******************************************************************/

#include "ses_common.h"
#include "ses_uart.h"
#include "ses_timer.h"

/* FUNCTION PROTOTYPES *******************************************************/

/**
 * Initializes rotary encoder and joystick button
 */
void button_init(bool debouncing);

/**
 * Prepare function pointer for buttons Interrupt
*/

typedef void (*pButtonCallback)();
void button_setRotaryButtonCallback(pButtonCallback callback);
void button_setJoystickButtonCallback(pButtonCallback callback);

/** 
 * Get the state of the joystick button.
 */
bool button_isJoystickPressed(void);

/** 
 * Get the state of the rotary button.
 */
bool button_isRotaryPressed(void);

/**
 * Check the state and eliminate bouncing
 */
void button_checkState();

#endif /* SES_BUTTON_H_ */
