/*INCLUDES ************************************************************/

#include "ses_timer.h"
#include "ses_motorFrequency.h"

/* PRIVATE VARIABLES **************************************************/
/** list of scheduled tasks */

#define TOLERANCE_FACTOR		10	// Assure elapsed time reached a huge value
#define CONVERT_TO_HERTZ	   	200	// With 5 ms intervals 
	

volatile static uint8_t edge_counter = 0;
volatile static uint16_t elapsed_time = 0;
volatile static uint16_t last_elapsed_time = 0;
volatile static bool one_rev = false; 
volatile static uint16_t N_samples[N] = {}; 
volatile static bool motor_stopped = true;

/*FUNCTION DEFINITION *************************************************/
void motorFrequency_init()
{
	// Configure Interrupt 0, at rising edge
          // Enable the Yellow LED to indicate interrupt signal:
               led_yellowInit();
		// Enable the GREEN LED to indicate stop situation:
			led_greenInit();	
          // Define interrupt sense control
               EICRA |= (1<<ISC00)| (1<<ISC01);
	// ATOMIC block used to avoid context switching before starting timer5
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
	{ 
		// Enable interrupt mask:
		EIMSK |= (1<<INT0);
		timer5_start();
	}
}

uint16_t motorFrequency_getRecent()
{	
		// Convert from time (ms) to Hz
		// Check if not empty, to avoid zero division
		if (last_elapsed_time != 0)
		{
		return (CONVERT_TO_HERTZ / last_elapsed_time); 
		}
		// if empty return zero (stop state)
		return 0;
}

uint16_t motorFrequency_getMedian()
{
	uint16_t median_buffer[N] = {};
	uint16_t	sum = 0;
	uint16_t static median = 0;

	// Atomic block used to avoid changing any element inside the array during the calculation
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) 
	{
		for (int j = 0; j <N; j++)
		{
			median_buffer[j] = N_samples[j];	
		}
	}
	for(int k =0; k<N; k++)
	{
		sum += median_buffer[k];
	}
	median = (sum / (N));
	// Check if not empty, to avoid zero division
	if (median != 0)
	{
	median = CONVERT_TO_HERTZ/median ;
	}
	return median; 
}

ISR(INT0_vect)
{
	led_yellowToggle();
	motor_stopped = false;
	edge_counter++;
	// if 6 spikes reached, (one revolution is complete), reset the counter
	if (edge_counter == 6)
	{
		edge_counter = 0;
		one_rev = true;
	}
}

ISR(TIMER5_COMPA_vect)
{
	uint8_t static index = 0;
	// start counting when motor signals sensed
	if(!motor_stopped)
	{	
		elapsed_time++; // Each 5 ms 
		led_greenOff();	
	}
	if (one_rev) // tackle the current measured time, and recent the time counter
	{
		last_elapsed_time = elapsed_time;
		N_samples[index] = elapsed_time; // fetch samples in the array buffer.
		elapsed_time = 0; 			   // Reset the counter for the next rev. 
		one_rev = false;			   // Reset revolution flag
		index++;
		if (index >= N)			   // Buffer reached the end, reset the index. 
		{
			index = 0;
		}
	}
	else if((elapsed_time >=  (TOLERANCE_FACTOR*last_elapsed_time)))
	{
		// if the counter reached a huge value(did not reset), then the motor has stopped
		// Reset all the variables
		elapsed_time = 0;
		last_elapsed_time = 0;
		edge_counter = 0;
		motor_stopped = true;
		for (int j = 0; j <N; j++)
			{
				N_samples[j] =0;	
			}
			led_yellowOff();
			led_greenOn();
	} 
}