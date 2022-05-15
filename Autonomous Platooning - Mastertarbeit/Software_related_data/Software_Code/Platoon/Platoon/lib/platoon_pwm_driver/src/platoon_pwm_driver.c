/**
 *
 * platoon_pwm_driver.c - PWM module for motor control
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

/* ****************** Includes ****************** */
#include "platoon_pwm_driver.h"
/* ****************** Global variables ****************** */
static const char *TAG = "MCPWM_DRIVER";
/* ****************** Functions ****************** */
void pwm_gpio_init(void)
{
     mcpwm_gpio_init(MCPWM_UNIT, MCPWM1A, GPIO_PWM0A_OUT);
     mcpwm_gpio_init(MCPWM_UNIT, MCPWM1B, GPIO_PWM0B_OUT);
#if  MCPWM_DEBUG  
     ESP_LOGI(TAG, "PWM (GPIO) Peripheral initialized");
#endif
}

void pwm_init(void)
{
     //1. mcpwm gpio initialization
     pwm_gpio_init();

     //2. initial mcpwm configuration
     mcpwm_config_t pwm_config;
     pwm_config.frequency     = MCPWM_FREQUENCY; //frequency = 500Hz,
     pwm_config.cmpr_a        = 0;       //duty cycle of PWMxA = 0
     pwm_config.cmpr_b        = 0;       //duty cycle of PWMxb = 0
     pwm_config.counter_mode  = MCPWM_UP_COUNTER;
     pwm_config.duty_mode     = MCPWM_DUTY_MODE_0;

#if  MCPWM_DEBUG  
     ESP_LOGD(TAG, "MCPWM will be initialized with the following paramters:");
     ESP_LOGD(TAG, "MCPWM Frequency: %d",  pwm_config.frequency);
     ESP_LOGD(TAG, "MCPWM Initial A channel duty: %d", pwm_config.cmpr_a);
     ESP_LOGD(TAG, "MCPWM Initial B channel duty: %d", pwm_config.cmpr_b);
     ESP_LOGD(TAG, "MCPWM counter mode UP");
     ESP_LOGD(TAG, "MCPWM Duty mode: Active high duty, i.e. duty cycle proportional to high time for asymmetric MCPWM");
#endif
     mcpwm_init(MCPWM_UNIT, MCPWM_TIME, &pwm_config); //Configure PWM0A & PWM0B with above settings
}

void motor_stop(void)
{
     mcpwm_set_signal_low(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_A);
     mcpwm_set_signal_low(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_B);
#if  MCPWM_DEBUG  
     ESP_LOGI(TAG, "Motor stopped");
#endif
}

void brushed_motor_backward(float duty_cycle)
{
#if  MCPWM_DEBUG  
     ESP_LOGD(TAG, "Motor will move backward with the following duty:");
     ESP_LOGD(TAG, "Duty set: %f", duty_cycle);
#endif
     mcpwm_set_signal_low(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_A);
     mcpwm_set_duty(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_B, duty_cycle);
     mcpwm_set_duty_type(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
}

void brushed_motor_forward(float duty_cycle)
{
#if  MCPWM_DEBUG  
     ESP_LOGD(TAG, "Motor will move forward with the following duty:");
     ESP_LOGD(TAG, "Duty set: %f", duty_cycle);
#endif
     mcpwm_set_signal_low(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_B);
     mcpwm_set_duty(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_A, duty_cycle);
     mcpwm_set_duty_type(MCPWM_UNIT, MCPWM_TIME, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
}