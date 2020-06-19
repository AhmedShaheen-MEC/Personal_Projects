#include <avr/io.h>
#include <util/delay.h>
#include "ses_button.h"
#include "ses_scheduler.h"
#include "ses_timer.h"

//****************Define variables and function****************
taskDescriptor taskDescriptor_1, taskDescriptor_2,taskDescriptor_3,taskDescriptor_4;
#define ROTARY_BUTTON_PORT    PORTB
#define ROTARY_BUTTON_PIN     6

#define JOYSTICK_BUTTON_PORT  PORTB
#define JOYSTICK_BUTTON_PIN   7

uint8_t time_flag = 0;
uint8_t led_flag = 0;
uint32_t ms_counter = 0;
void task_3(void);
// define function pointers, which will be executed.
typedef enum selectColor {
	RED,GREEN
};
const uint8_t selected_LED = GREEN;

void led_toggle(void* led_num)
{	
	switch (*((uint8_t *)led_num))
	{
		case RED : led_redToggle(); break;
		case GREEN : led_greenToggle(); break;
	}
}

void button_init_scheduler()
{
	//Set pin direction
     DDR_REGISTER(ROTARY_BUTTON_PORT) &= ~(1U<<ROTARY_BUTTON_PIN);
     DDR_REGISTER(JOYSTICK_BUTTON_PORT) &= ~(1U<<JOYSTICK_BUTTON_PIN);
     //Set pull-ups to sense the grounding
     ROTARY_BUTTON_PORT |= (1U<<ROTARY_BUTTON_PIN);
     JOYSTICK_BUTTON_PORT |= (1U<<JOYSTICK_BUTTON_PIN);
}

void stop_watch_controller(void)
{
	time_flag ^= 0xff;
	//if the LED is OFF, turn the led flag again
	//Start/Stop the stop watch
	if (time_flag != 0)
	{
		scheduler_add(&taskDescriptor_4);
	}
	else
	{
		scheduler_remove(&taskDescriptor_4);
	}
}

void yellow_led_controller(void)
{
	
	led_yellowToggle();
	led_flag ^= 0xff;
	//if the LED is ON start add the turning off task! 
	if (led_flag != 0)
	{
		//LED is activated start counting and trun it off(after 5 s)
		task_3();
		scheduler_add(&taskDescriptor_3);
	}
}

void stop_watch(void)
{
	uint16_t seconds, ms_seconds;
	seconds = ms_counter /100;
	ms_seconds = ms_counter % 100;
	if (time_flag != 0)
	{
		// count 10 ms for the stop watch
		ms_counter++;
		lcd_setCursor(0,0);
		fprintf(lcdout, "Time:%d:", seconds);
		fprintf(lcdout, "%d", ms_seconds);
	}
}

void task_1(void)
{
	// Toggle the green led every 2 s

	taskDescriptor_1.task = &led_toggle;
	taskDescriptor_1.param =  (void *)&selected_LED;
	taskDescriptor_1.execute = 0;
	taskDescriptor_1.period = 2000;	// toggle every 2 s, should be executed after this time.
	taskDescriptor_1.expire = (uint16_t)2000 ; 
	taskDescriptor_1.next = NULL;
}

void task_2(void)
{
	//Buttons and  debouncing (call backs will be executed when task 2 is called)
	//Task2: check button state and set a flag for the rotary button
	taskDescriptor_2.task = &button_checkState; 
	taskDescriptor_2.param =  NULL;
	taskDescriptor_2.execute = 0;
	taskDescriptor_2.period = 5;  // toggle every 5 ms Should be executed after this time.
	taskDescriptor_2.expire = 1 ;
	taskDescriptor_2.next = NULL;
}

void task_3(void)
{
	// Turn off the Yellow LED after 5 s (Not periodic)
	taskDescriptor_3.task = &led_yellowOff; // Atomic execution ?
	taskDescriptor_3.param =  NULL;
	taskDescriptor_3.execute = 0;
	taskDescriptor_3.period = 0;
	taskDescriptor_3.expire = (uint16_t)5000; 
	taskDescriptor_3.next = NULL;
}

void task_4(void)
{
	// Task4: timer control (periodic but controllable)
	taskDescriptor_4.task = &stop_watch; 
	taskDescriptor_4.param =  NULL;
	taskDescriptor_4.execute = 0;
	taskDescriptor_4.period = 10; // 10 ms period 
	taskDescriptor_4.expire = 1 ;
	taskDescriptor_4.next = NULL;
}

void set_callBacks(void)
{
	// Rotary button call back:(stop/start the stop watch)
	button_setRotaryButtonCallback(&stop_watch_controller);
	// Joystick button call back:
	button_setJoystickButtonCallback(&yellow_led_controller);
}

/******************Main******************/
int main()
{
	/************Initializations***********/
	// Initialize the LEDs
	led_greenInit();
	led_yellowInit();
	led_redInit();
	//Initialize LCD
	lcd_init();
	//Make sure the initial state is known.
	led_yellowOff();
	led_greenOff();
	led_redOff();
	set_callBacks();
	/************Tasks***********/
	task_1();
	task_2();
	task_4();
	/************Initiailize scheduler***********/
	scheduler_add(&taskDescriptor_1);
	scheduler_add(&taskDescriptor_2);
	button_init_scheduler();
	//Enable interrupt
	sei();
	//Enable scheduler
	scheduler_init();
	scheduler_run();
	return 0;
}