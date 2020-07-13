#include <avr/io.h>
#include <util/delay.h>
#include "ses_button.h"
#include "ses_pwm.h"
#include "util/atomic.h"
#include "ses_motorFrequency.h"
#include "ses_lcd.h"


//****************Define variables and function****************
taskDescriptor taskDescriptor_4;
static uint8_t rotary_flag; 
static uint8_t pid_flag; 

/* **** Motor Parameters **** */
#define DUTY            30
#define F_TARGET        3000
#define CONVERT_TO_RPM  60
/* **** LCD aspect ratio **** */
#define LCD_WIDTH       122
#define LCD_HEIGHT      31
/* **** PID parameters **** */
#define K_P             0.03
#define K_I             0.3
#define K_D             0
#define A_W             0.5
#define SCALING_FACTOR   10 
#define PLOTTING_FACTOR  0.5

/* *****************Functions declaration**************** */
void motor_start(void);
void motor_stop(void);
void check_rotary_button(void);
void check_joystick_button(void);
inline int16_t min(int16_t entry_1, int16_t entry_2);
inline int16_t max(int16_t entry_1,  int16_t entry_2);
void plot();
void set_axes();
void apply_PID(uint16_t);
void task_4(void);

/************************Motor control*****************/
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
     // check rotary flag value, 
     // and timer status, to avoid multiple stopping or starting. 
     if(!(rotary_flag) && (TCCR0B &(1<<CS00)))
     {
          motor_stop();
     }
     else if ( !(TCCR0B &(1<<CS00)) && (rotary_flag != 0))
     {
          motor_start();
     }  
}

/* ***** Task 5.4 ***** */

inline int16_t min(int16_t entry_1, int16_t entry_2)
{
     return (entry_1>entry_2) ? entry_2 : entry_1;
}

inline int16_t max(int16_t entry_1,  int16_t entry_2)
{
     return (entry_1>entry_2) ? entry_1 : entry_2;
}

void check_joystick_button(void)
{
     pid_flag ^= 0xff;
	//if the joystick pressed, start the PID controller
	if (pid_flag != 0)
	{
		// prepare the PID task
          task_4();
          // prepare the LCD
          set_axes();
          scheduler_add(&taskDescriptor_4);
	}
	else
	{
		scheduler_remove(&taskDescriptor_4);
	}
}

void set_axes()
{
     // clear LCD first, to avoid any conflicts
     lcd_clear();
     uint8_t i, j;
     // draw the Y-axes
     for(i = LCD_HEIGHT;i <=0;i--)
     {
          lcd_setPixel(0, i, true);

     }
     // draw the X-axes
     for(j =LCD_WIDTH ;j <=0;j--)
     {    
          lcd_setPixel(j, LCD_HEIGHT, true);
     }
}

void plot()
{
     uint16_t current_freq = motorFrequency_getRecent();
     // scale the freq. (1 pixel == 2 Hz) (Max = 64, Min = 0)
     uint16_t static x_pixel = 1;
     uint16_t y_pixel = current_freq*PLOTTING_FACTOR; 
     // set LCD pixel
     lcd_setPixel(x_pixel, y_pixel, true);
     x_pixel++;
     // if the max width reached, reset the LCD
     if (x_pixel == 121)
     {
          set_axes();
     }
     apply_PID(current_freq*CONVERT_TO_RPM);
}

void apply_PID(uint16_t current_freq)
{
     int16_t static error, integrated_error = 0, last_error = 0;
     uint8_t new_duty;
     fprintf(uartout, "Current freq. %d RPM\n", current_freq);
     error = (F_TARGET - current_freq);
     fprintf(uartout, "error %d \n", error);
     integrated_error = max(min(((integrated_error)+ error), (A_W)), (-1*A_W));
     new_duty = ((K_P*error) + (K_I*integrated_error) + (K_D*(last_error - error)));
     last_error = error;
     if (new_duty > 255)
     {
          new_duty = 255;
     }
     else if (new_duty <0)
     {
          new_duty = 0;
     }
     pwm_setDutyCycle(new_duty);
}

// /*****Task 5.4- Define task descriptors*****/

void task_4(void)
{
     // Task1: Plot results on LCD with PID monitoring. 
	taskDescriptor_4.task =plot ; 
	taskDescriptor_4.param =  NULL;
	taskDescriptor_4.execute = 0;
	taskDescriptor_4.period = 1000; // 1 s period 
	taskDescriptor_4.expire = 0 ;
	taskDescriptor_4.next = NULL;
}

//************************Main*****************

int main(void) 
{
     uart_init(57600);
     lcd_init();
     set_axes();
     pwm_init();
     scheduler_init();
     set_axes();
     button_init(true);

     button_setRotaryButtonCallback(&check_rotary_button);
     button_setJoystickButtonCallback(&check_joystick_button);
     motorFrequency_init();  
     sei();
     scheduler_run();
	return 0;
}