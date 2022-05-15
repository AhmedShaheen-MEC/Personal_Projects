/**
 *
 * platoon_relative_motion_handle.h Preceding vehicle movement handler module 
 * 							with ultrasonic interface.
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

#ifndef PLATOON_RELATIVE_MOTION_HANDLE_H_
#define PLATOON_RELATIVE_MOTION_HANDLE_H_

/* ****************** Includes ****************** */
#include <Arduino.h>
#include "platoonSDK.h"
/* ****************** Defines ****************** */
#define ECHO_PIN 				US_ECHO_PIN 
#define TRIG_PIN 				US_TRIG_PIN 
#define MAX_SAMPLES_VEL 			US_MAX_SAMPLES_PER_CTR_FREQ
#define MAX_SAMPLES_ACC 			US_MAX_SAMPLES_ACCEELRATION
#define ALLAWED_TOLERANCE 		US_ALLAWED_TOLERANCE
#define DUMMY_VALUE 			US_DUMMY_VALUE
#define CONTROLLER_INTERVAL_MS 	PLATOON_CONTROLLER_INTERVAL_MS
/* ****************** Structs ****************** */
typedef struct us_data
{
	int32_t average_spacing_error;
	float average_spacing_error_rate[MAX_SAMPLES_VEL];
	float relative_acceleraion[MAX_SAMPLES_ACC];
	uint8_t sampling_steps;
	uint8_t vel_index;
	uint8_t acc_index;
} us_data_t;

typedef enum
{
	US_AVERAGE_STEPS_1 = 1,
	US_AVERAGE_STEPS_2
} us_average_steps_t;

/* ****************** Function prototypes ****************** */

void us_init(us_data_t *us_handle);
void us_init_direct();
uint16_t us_get_distance();
float calc_average(float new_value, float *array_buffer);
void calc_relative_dynamics(us_data_t *us_handle);

void fill(int index, float *buffer);
#endif /* PLATOON_RELATIVE_MOTION_HANDLE_H_ */
