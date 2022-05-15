/**
 *
 * platoon_pwm_driver.h - PWM module for motor control
 *
 * Copyright (C) 2021  Institute of Communication Networks (ComNets), 
 *                     Hamburg University of Technology (TUHH)
 *           (C) 2021  Ahmed Shaheen
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/** 
 * ********** ESP32 MCPWM peripheral driver **********
 * 
 *    MCPWM unit:
 *         Unit no. 0 
 *         A/B pair controlled using Timer_0
 *         All motor signals containd in "mcpwm_io_signals_t"     
 *         @mcpwm_counter_type_t select which counter mode to use.               
 *              MCPWM_UP_COUNTER 
 *              MCPWM_DOWN_COUNTER  
 *              MCPWM_UP_DOWN_COUNTER
 */
#ifndef PLATOON_PWM_DRIVER_H_
#define PLATOON_PWM_DRIVER_H_
/* ****************** Includes ****************** */
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "platoonSDK.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ****************** Defines ****************** */
#define GPIO_PWM0A_OUT                      MCPWM_GPIO0_A_OUT   //Set GPIO 15 as PWM0A
#define GPIO_PWM0B_OUT                      MCPWM_GPIO0_B_OUT   //Set GPIO 16 as PWM0B

#define MCPWM_UNIT                          MCPWM_UNIT_0 
#define MCPWM_TIME                          MCPWM_TIMER_1       // 32 bit timer (0 -> 65535)
#define MCPWM_FREQUENCY                     MCPWM_WAVE_FREQUENCY

#define MOTOR_MAX_REV			            ((MCPWM_MAX_MOTOR_REV*MCPWM_MAX_PWM_VOLTAGE)/MCPWM_MAX_MOTOR_VOLTAGE)	// 18.000 rpm ~= 47123.8 mm/s
#define MAX_PWM_VALU			            MCPWM_MAX_PWM_VALU
#define MOTOR_WHEEL_DIAMETER	            MCPWM_MOTOR_WHEEL_DIAMETER	
#define RPM_2_M_PER_S(rpm)                  ((rpm * 2 * PI * MOTOR_WHEEL_DIAMETER)/60)
#define MS_2_MMS                            1000
#define MAX_LINEAR_VELOCITY_MMS		        (RPM_2_M_PER_S(MOTOR_MAX_REV)*MS_2_MMS)
#define CONVERT_VELOCITY_TO_DUTY_MMS(velocity) ((velocity/MAX_LINEAR_VELOCITY_MMS)*100)     // 100 -> convert duty to percentage.
/* ****************** Function prototypes ****************** */
void pwm_gpio_init(void);
void pwm_init(void);
void motor_stop(void);
void brushed_motor_backward(float duty_cycle);
void brushed_motor_forward(float duty_cycle);

#ifdef __cplusplus
}
#endif

#endif /* PLATOON_PWM_DRIVER_H_ */
