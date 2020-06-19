/* INCLUDES ******************************************************************/

#include "ses_button.h"

/* DEFINES & MACROS **********************************************************/
#define ROTARY_BUTTON_PORT    PORTB
#define ROTARY_BUTTON_PIN     6

#define JOYSTICK_BUTTON_PORT  PORTB
#define JOYSTICK_BUTTON_PIN   7

#define INPUT_STATUS          0
#define OUTPUT_STATUS         1

#define BUTTON_NUM_DEBOUNCE_CHECKS      5   // Number of debounced buttons..!
#define BUTTON_DEBOUNCE_PERIOD          5  //  30 ms
#define BUTTON_DEBOUNCE_POS_JOYSTICK    0x01
#define BUTTON_DEBOUNCE_POS_ROTARY      0x02

volatile static pButtonCallback joystickCallback;
volatile static pButtonCallback rotaryCallback;
/* FUNCTION DEFINITION *******************************************************/

void button_init(bool debouncing) 
{
     //Set pin direction
     DDR_REGISTER(ROTARY_BUTTON_PORT) &= ~(1U<<ROTARY_BUTTON_PIN);
     DDR_REGISTER(JOYSTICK_BUTTON_PORT) &= ~(1U<<JOYSTICK_BUTTON_PIN);
     //Set pull-ups to sense the grounding
     ROTARY_BUTTON_PORT |= (1U<<ROTARY_BUTTON_PIN);
     JOYSTICK_BUTTON_PORT |= (1U<<JOYSTICK_BUTTON_PIN);
     if(debouncing)
     {
          timer1_setCallback(button_checkState);
          timer1_start();
     }
     else 
     {
          //Interrupt setting:
          // EICRB set actication level, will stick with low as signal. 
          PCICR |= (1<<PCIE0); // Pin Change Interrupt Control Register
          PCMSK0 |= (1<<PCINT7) | (1<<PCINT6); 
     }
}
bool button_isJoystickPressed(void)
{
     return (PIN_REGISTER(JOYSTICK_BUTTON_PORT) & (1U<<JOYSTICK_BUTTON_PIN));
}


bool button_isRotaryPressed(void)
{
     return (PIN_REGISTER(ROTARY_BUTTON_PORT) & (1U<<ROTARY_BUTTON_PIN));
}

ISR(PCINT0_vect){
     
// execute callbacks here
     if ((button_isJoystickPressed() == 0) && ((PCMSK0 &(1<<PCINT7)) == (1<<PCINT7)) && (joystickCallback != NULL))
     {
          joystickCallback();
     }
     
     else if ((button_isRotaryPressed() == 0) && ((PCMSK0 &(1<<PCINT6)) == (1<<PCINT6)) && (rotaryCallback != NULL))
     {
          rotaryCallback();
     }
}

void button_setRotaryButtonCallback(pButtonCallback callback)
{
     rotaryCallback = callback;  
}

void button_setJoystickButtonCallback(pButtonCallback callback)
{
     joystickCallback = callback;
}

void button_checkState()
 {

     static uint8_t state[BUTTON_NUM_DEBOUNCE_CHECKS] = {};
     static uint8_t index = 0;
     static uint8_t debouncedState = 0;
     uint8_t lastDebouncedState = debouncedState;
     // each bit in every state byte represents one button
     state[index] = 0;
     if(button_isJoystickPressed() == 0) 
     {
          state[index] |= BUTTON_DEBOUNCE_POS_JOYSTICK;
     }
     if(button_isRotaryPressed() == 0) 
     {
          state[index] |= BUTTON_DEBOUNCE_POS_ROTARY;
     }
     index++;
     if (index == BUTTON_NUM_DEBOUNCE_CHECKS) 
     {
          index = 0;
     }
     // init compare value and compare with ALL reads, only if
     // we read BUTTON_NUM_DEBOUNCE_CHECKS consistent "1's" in the state
     // array, the button at this position is considered pressed
     uint8_t j = 0xFF;
     for(uint8_t i = 0; i < BUTTON_NUM_DEBOUNCE_CHECKS; i++) 
     {
          j = j & state[i];
     }
  
     debouncedState = j;
     // TODO extend function
     if (lastDebouncedState == BUTTON_DEBOUNCE_POS_JOYSTICK && lastDebouncedState != debouncedState && joystickCallback != NULL)
     {    
          joystickCallback();
     }     
     else if ((lastDebouncedState == BUTTON_DEBOUNCE_POS_ROTARY) && lastDebouncedState != debouncedState && rotaryCallback != NULL)
     {
          rotaryCallback(); 
     }
}