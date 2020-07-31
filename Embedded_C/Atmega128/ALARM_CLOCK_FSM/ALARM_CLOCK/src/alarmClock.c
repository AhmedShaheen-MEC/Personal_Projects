#include "alarmClock.h"
//****************Define global variables and function****************
#define TRANSITION(newState) ((fsm->state = newState), RET_TRANSITION)

#define MILIS_HOURS_SCALER         3600000 
#define MILIS_MINUTES_SCALER       60000
#define MILIS_SECONDS_SCALER       1000
#define HOURS_REMAINEDER           24
#define MINUTES_REMAINDER          60
#define SECONDS_REMAINDER          60
#define MILIS_REMAINDER            1000
#define MINUTES_HOURS_SCALER       60


#define GET_HOURS(current_time) ((current_time / MILIS_HOURS_SCALER) % HOURS_REMAINEDER)
#define GET_MINS(current_time) ((current_time / MILIS_MINUTES_SCALER)% MINUTES_REMAINDER)
#define GET_SECS(current_time) ((current_time / MILIS_SECONDS_SCALER) % SECONDS_REMAINDER)
#define GET_MILIS(current_time) (current_time % MILIS_REMAINDER)

#define GET_TOTAL_TIME_MILIS(hours,minutes) (((hours*MINUTES_HOURS_SCALER) + (minutes))*MILIS_MINUTES_SCALER)  // convert total time to Milis 

#define ALARM_EXPIRATION_TIME_SECS 5

#define MAX_HOURS                  24
#define MAX_MINS                   60

#define IDEAL_SECOND               1000

//*********** Internal  events triggered by internal devices (i.e. Timers) ***********
static taskDescriptor time_dispatcher     = {.task = timerDispatch, .param = NULL, .period = IDEAL_SECOND, .expire=0};    // Time updating event
static taskDescriptor alarm_dispatcher    = {.task = alarmTimeoutDispatch, .param = NULL, .period = 125, .expire=0};      // Timeout check event
// Green red toggle event, period dynamically changed(sync.) with the second counter, updted in (timerDispatch()) function 
static taskDescriptor green_led_toggler    = {.task = led_greenToggle, .param = NULL, .period = IDEAL_SECOND, .expire=0}; 

//*********** External events triggered by external devices (i.e. Buttons and switches) ***********
// Triggered when the Rotaty button pressed
static taskDescriptor rotary_dispatcher   = {.task = rotaryPressedDispatch, .param = NULL, .period = 0, .expire=0}; 	
// Triggered when the Joystick button pressed
static taskDescriptor joystick_dispatcher = {.task = joystickPressedDispatch, .param = NULL, .period = 0, .expire=0};	
// Triggered when the Rotary encoder, rotated CW
static taskDescriptor rotary_clock_wise_dispatcher = {.task = rotaryClockWiseDispatch, .param = NULL, .period = 0, .expire=0};	
// Triggered when the Rotary encoder, rotated CCW
static taskDescriptor rotary_counter_clock_wise_dispatcher = {.task = rotaryCounterClockWiseDispatch, .param = NULL, .period = 0, .expire=0};	

Fsm theFsm;
static uint16_t alarm__elapsed_time;
static struct time_t global_system_time;
static bool alarm_time_set;
/************************ Clock *****************/
/*****Helper Functions*****/
// Set system time variable to the initialized clock time (ms)
void static clock_set_time(void)
{
     systemTime_t strating_time = 0;
     strating_time = GET_TOTAL_TIME_MILIS(theFsm.timeSet.hour, theFsm.timeSet.minute);
     scheduler_setTime(strating_time);
}

// Display the clock time accodring the the current state (Flag)
void static clock_display(uint8_t digit)
{
     uint8_t hours_value = theFsm.timeSet.hour;
     uint8_t min_value   = theFsm.timeSet.minute;
     uint8_t sec_value   = theFsm.timeSet.second;

     if (digit == HOURS)
     {
          lcd_setCursor(0,0);
          fprintf(lcdout,"%02d:",hours_value); 
     }
     else if (digit == MINTUES)
     {
         lcd_setCursor(3,0);
         fprintf(lcdout,"%02d:",min_value); 
     }
     else
     {
          lcd_setCursor(0,0);
          fprintf(lcdout,"%02d:",hours_value); 
          lcd_setCursor(3,0);
          fprintf(lcdout,"%02d:",min_value); 
          lcd_setCursor(6,0);
          fprintf(lcdout,"%02d",sec_value); 
     }
}

// Update the clock time variable whenever update event is triggered.
void static clock_update_time(void)
{
     systemTime_t current_time = scheduler_getTime();
     
     global_system_time.milli  =  GET_MILIS(current_time);
     global_system_time.second =  GET_SECS(current_time);
     global_system_time.minute =  GET_MINS(current_time);
     global_system_time.hour   =  GET_HOURS(current_time);

     // Update the clock display if the (Alarm is not enabled and the alarm time is not being set)
     if ((!theFsm.isAlarmEnabled) && (!alarm_time_set))
     {
          theFsm.timeSet.milli  = global_system_time.milli ;
          theFsm.timeSet.second = global_system_time.second;
          theFsm.timeSet.minute = global_system_time.minute;
          theFsm.timeSet.hour   = global_system_time.hour;
     }
     else if ((theFsm.isAlarmEnabled))
     {
          // Alarm is enabled, check for time match
          if ((global_system_time.minute == theFsm.timeSet.minute) && (theFsm.timeSet.hour == global_system_time.hour))
          {
              alarmActivationDispatch();
              return; 
          }  
          
     }
     clock_display(ALL);  
}

// Handle alarm flag, and led stats.
void static check_alarm_setting(void)
{
     theFsm.isAlarmEnabled = !theFsm.isAlarmEnabled;
     if (theFsm.isAlarmEnabled)
     {
          led_yellowOn();
          if (theFsm.timeSet.hour < global_system_time.hour)
          {               
               lcd_setCursor(0,2);
               fprintf(lcdout, "Warning:alarm will");
               lcd_setCursor(0,3);
               fprintf(lcdout, "fire the next day");
               
          }
          else if ((theFsm.timeSet.hour == global_system_time.hour))
          {
               if (theFsm.timeSet.minute < global_system_time.minute)
               {
                    lcd_setCursor(0,2);
               fprintf(lcdout, "Warning:alarm will");
               lcd_setCursor(0,3);
               fprintf(lcdout, "fire the next day");
               }
          }
     }
     else
     {
          
          led_yellowOff();
     }
}

//*********** Events passed when external events trigger by the scheduler ***********

void joystickPressedDispatch(void * param)
{
     Event e = {.signal = JOYSTICK_PRESSED};
     fsm_dispatch(&theFsm, &e);
}

void rotaryPressedDispatch(void * param) 
{
     Event e = {.signal = ROTARY_PRESSED};
     fsm_dispatch(&theFsm, &e);
}

void rotaryClockWiseDispatch(void * param) 
{
     Event e = {.signal = ROTARY_PRESSED};
     fsm_dispatch(&theFsm, &e);
}

void rotaryCounterClockWiseDispatch(void * param) 
{
     Event e = {.signal = ROTARY_LEFT_PRESSED};
     fsm_dispatch(&theFsm, &e);
}

void add_rotaryDispatch(void)
{
	scheduler_add(&rotary_dispatcher);
}

void add_joystickDispatch(void)
{
	scheduler_add(&joystick_dispatcher);
}

void add_rotaryClockWiseDispatch(void)
{
	scheduler_add(&rotary_clock_wise_dispatcher);
}

void add_rotaryCounterClockWiseDispatch(void)
{
	scheduler_add(&rotary_counter_clock_wise_dispatcher);
}

 
//*********** Events passed when internal events trigger by the scheduler ***********
/**
 * Tasks(Events), that will be added to the scheduler as a Qeue
 * @param param is set to void pointer to match scheduler task discriptor 
 */

void timerDispatch(void * param)
{
     green_led_toggler.period = IDEAL_SECOND - GET_MILIS(scheduler_getTime()); 
     Event e = {.signal = UPDATE_CLOCK};
     fsm_dispatch(&theFsm, &e);   
}

void alarmTimeoutDispatch(void * param)
{
     clock_update_time();
     led_redToggle();
     if ((global_system_time.second - alarm__elapsed_time) >= ALARM_EXPIRATION_TIME_SECS)
     {
          Event e = {.signal = ALARM_EXPIRED};
          fsm_dispatch(&theFsm, &e);
     }
}

void alarmActivationDispatch(void)
{
     Event e = {.signal = ALARM_CLOCKTIME_MATCH};
     fsm_dispatch(&theFsm, &e);
}

static void returnToRunning(void)
{
     Event e = {.signal = RETURN};
     fsm_dispatch(&theFsm, &e);
}


 //*********** System States***********
 
fsmReturnStatus clock_set_hours(Fsm * fsm, const Event * event)
{
     switch(event->signal) 
     {
          case ENTRY:
               theFsm.timeSet.hour = 0;
               lcd_setCursor(0,0);
               fprintf(lcdout,"HH:MM\nSet clock hours  ");
               return RET_HANDLED;
          case ROTARY_PRESSED:
               theFsm.timeSet.hour = (theFsm.timeSet.hour + 1) % MAX_HOURS;
               clock_display(HOURS);
               return RET_HANDLED;
          case ROTARY_LEFT_PRESSED:
               if (theFsm.timeSet.hour > 0)
               {
                    theFsm.timeSet.hour--;
               }
               clock_display(HOURS);
               return RET_HANDLED;
          case JOYSTICK_PRESSED:
               return TRANSITION(clock_set_minutes);
          case EXIT:
               return RET_IGNORED;
          default:
               return RET_IGNORED;
     }
}

fsmReturnStatus clock_set_minutes(Fsm * fsm, const Event * event)
{
     switch(event->signal) 
     {
          case ENTRY:
               theFsm.timeSet.minute = 0;
               lcd_setCursor(3,0);
               fprintf(lcdout, "00",theFsm.timeSet.hour);
               lcd_setCursor(0,1);
               fprintf(lcdout,"Set clock minutes  ");
               return RET_HANDLED;
          case ROTARY_PRESSED:
               theFsm.timeSet.minute++;
               if (theFsm.timeSet.minute >= 60)
               {
                    theFsm.timeSet.hour++;
                    theFsm.timeSet.minute = 0;
               }
               clock_display(MINTUES);
               return RET_HANDLED;
          case ROTARY_LEFT_PRESSED:
               if (theFsm.timeSet.minute > 0)
               {
                    theFsm.timeSet.minute--;
               }
               clock_display(MINTUES);
               return RET_HANDLED;
          case JOYSTICK_PRESSED:
               return TRANSITION(clock_running);
          case EXIT:
               clock_set_time();
               return RET_HANDLED;
          default:
               return RET_IGNORED;
     }
}

fsmReturnStatus clock_running(Fsm * fsm, const Event * event) 
{
     switch(event->signal) 
     {
          case ENTRY:
               lcd_setCursor(0,1);
               fprintf(lcdout,"                    ");
               scheduler_add(&time_dispatcher);
               scheduler_add(&green_led_toggler);    
               return RET_HANDLED;
          case UPDATE_CLOCK:
               clock_update_time();
               return RET_HANDLED;
          case ROTARY_PRESSED:
               return TRANSITION(clock_alarm_enable);
          case JOYSTICK_PRESSED:
               return TRANSITION(alarm_set_hours);
          case ALARM_CLOCKTIME_MATCH:
               return TRANSITION(clock_alarm_activated);
          case EXIT:
               scheduler_remove(&time_dispatcher);
               return RET_HANDLED;
          default:
               return RET_IGNORED;
     }
}

fsmReturnStatus clock_alarm_enable(Fsm * fsm, const Event * event)
{
     switch(event->signal) 
     {
          case ENTRY:
               check_alarm_setting();
               returnToRunning();
               return RET_HANDLED;
          case RETURN:
               return TRANSITION(clock_running);
          case EXIT:
               
          default:
               return RET_IGNORED;
     }
}

fsmReturnStatus alarm_set_hours(Fsm * fsm, const Event * event)
{
     switch(event->signal) 
     {
          case ENTRY:
               theFsm.timeSet.hour = 0; 
               lcd_clear();
               lcd_setCursor(0,0);
               fprintf(lcdout,"00:MM\nSet alaram hours ");
               return RET_HANDLED;
          case ROTARY_PRESSED:
               theFsm.timeSet.hour = (theFsm.timeSet.hour + 1) % MAX_HOURS;
               clock_display(HOURS);
               return RET_HANDLED;
          case JOYSTICK_PRESSED:
               return TRANSITION(alarm_set_minutes);
          case ROTARY_LEFT_PRESSED:
               if (theFsm.timeSet.hour > 0)
               {
                    theFsm.timeSet.hour--;
               }
               clock_display(HOURS);
               return RET_HANDLED;
          case EXIT:return RET_IGNORED;
          default:
               return RET_IGNORED;
     }
}

fsmReturnStatus alarm_set_minutes(Fsm * fsm, const Event * event)
{
     switch(event->signal) 
     {
          case ENTRY:
               theFsm.timeSet.minute = 0;
               lcd_setCursor(3,0);
               fprintf(lcdout, "00",theFsm.timeSet.hour);
               lcd_setCursor(0,1);
               fprintf(lcdout,"Set alarm minutes  ");
               return RET_HANDLED;
          case ROTARY_PRESSED:
               theFsm.timeSet.minute++;
               if (theFsm.timeSet.minute >= 60)
               {
                    theFsm.timeSet.hour++;
                    theFsm.timeSet.minute = 0;
               }
               clock_display(MINTUES);
               return RET_HANDLED;
          case JOYSTICK_PRESSED:
               return TRANSITION(clock_running);
          case ROTARY_LEFT_PRESSED:
               if (theFsm.timeSet.minute > 0)
               {
                    theFsm.timeSet.minute--;
               }
               clock_display(MINTUES);
               return RET_HANDLED;
          case EXIT:
               theFsm.timeSet.second =0;
               alarm_time_set = true;
               return RET_HANDLED;
          default:
               return RET_IGNORED;
     }
}

fsmReturnStatus clock_alarm_activated(Fsm * fsm, const Event * event)
{
     switch(event->signal) 
     {
          case ENTRY:
               fsm->isAlarmEnabled = false;
               alarm__elapsed_time  = global_system_time.second;
               led_redToggle();
               led_greenOff();
               led_yellowOff();
               scheduler_add(&alarm_dispatcher);  
               return RET_HANDLED;
          case JOYSTICK_PRESSED:
               return TRANSITION(clock_running);
          case ROTARY_PRESSED:
               return TRANSITION(clock_running);
          case ALARM_EXPIRED:
               return TRANSITION(clock_running);
          case EXIT:
               alarm_time_set = false;
               scheduler_remove(&alarm_dispatcher);
               led_redOff();
               return RET_HANDLED;
          default:
               return RET_IGNORED;
     }
}
