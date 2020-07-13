#include <avr/io.h>
#include <util/delay.h>
#include "ses_button.h"
#include "ses_pwm.h"
#include "util/atomic.h"
#include "ses_motorFrequency.h"
#include "ses_lcd.h"

//****************Define variables and function****************
taskDescriptor taskDescriptor_2;
static uint8_t rotary_flag; 

#define DUTY             60
#define CONVERT_TO_RPM   60

/* *****************Functions declaration**************** */
void motor_start(void);
void motor_stop(void);
void check_rotary_button(void);
void lcd_print_frequency(void);
void task_2(void);

/* *****************Motor control**************** */
/*****Task 5*****/

void motor_start(void)
{
     pwm_setDutyCycle(DUTY);            // Set duty cycle
     DDR_REGISTER(PORTG) |= (1<<PIN5);  // Enable motor port
     TCCR0B |= (1<<CS00);               // Start timer0, with CPU speed
}
void motor_stop(void)
{
   timer0_stop();                            //  Stop timer0 to save power.
   DDR_REGISTER(PORTG) &= ~(1<<PIN5);        //  Disable motor port, to insure the motor is stopped
}

// rotary button call back(inside the check_button_state)
void check_rotary_button(void)
{
     rotary_flag ^= 0xff;
       // check timer status, to avoid multiple stopping or starting. 
     if(!(rotary_flag) && (TCCR0B &(1<<CS00)))
     {
          motor_stop();
     }
     else if ( !(TCCR0B &(1<<CS00)) && (rotary_flag != 0))
     {
          motor_start();
     }  
}

void lcd_print_frequency(void)
{
     uint16_t measured_freq_median = motorFrequency_getMedian();          // Read measured Freq. (Hz)
     uint16_t measured_freq = motorFrequency_getRecent();                 // Read measured Freq. (Hz)
     measured_freq_median = CONVERT_TO_RPM*(measured_freq_median);        // Convert Hz to RPM
     measured_freq = CONVERT_TO_RPM*(measured_freq);                      // Convert Hz to RPM

     lcd_setCursor(0,1);
     fprintf(lcdout, "Median:%u    RPM \n", measured_freq_median);

     lcd_setCursor(0,2);
     fprintf(lcdout, "Fre.:%u      RPM \n", measured_freq);
}

// /*****Task 5.2- Define task descriptors*****/
void task_2(void)
{
     // Task1: LCD_Print measured freq. 
	taskDescriptor_2.task = &lcd_print_frequency; 
	taskDescriptor_2.param =  NULL;
	taskDescriptor_2.execute = 0;
	taskDescriptor_2.period = 1001; // 1 s period 
	taskDescriptor_2.expire = 0 ;
	taskDescriptor_2.next = NULL;
}

//************************Main*****************
int main(void) {

     uart_init(57600);
     lcd_init();
     pwm_init();
     lcd_setCursor(0,0);
     fprintf(lcdout, "Duty:%u N: %u\n", (uint8_t)DUTY, (uint8_t)N);
     scheduler_init();
     button_init(true);
     button_setRotaryButtonCallback(&check_rotary_button);
     motorFrequency_init();     

     task_2();

     scheduler_add(&taskDescriptor_2);
     sei();
     scheduler_run();
	return 0;
}