/**
 *
 * platoon_relative_motion_handle.cpp - Preceding vehicle movement handler module 
 * 								   with ultrasonic interface. 
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
#include "platoon_relative_motion_handle.h"
/* ****************** Global Variables ****************** */
static const char *TAG = "Ultrasonic_Handle";
portMUX_TYPE us_muxtex = portMUX_INITIALIZER_UNLOCKED;
/* ****************** Function declaration ****************** */
void us_init(us_data_t *us_handle)
{
	pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an OUTPUT
	pinMode(ECHO_PIN, INPUT);
	memset(&us_handle, 0, sizeof(us_handle));
#ifdef ULTRASONIC_DEBUG
	ESP_LOGI(TAG, "DEBUG::ULTRASONIC::US init... done\n");
#endif
}

void us_init_direct()
{
	pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an OUTPUT
	pinMode(ECHO_PIN, INPUT);
#ifdef ULTRASONIC_DEBUG
	ESP_LOGI(TAG, "DEBUG::ULTRASONIC::US init... done\n");
#endif
}

uint16_t us_get_distance()
{	
	digitalWrite(TRIG_PIN, LOW);
	delayMicroseconds(2);
	// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW);
	uint16_t duration = pulseIn(ECHO_PIN, HIGH);
	uint16_t distance = duration * 0.017; 
	return distance;
}

void calc_relative_dynamics(us_data_t *us_handle)
{
	uint16_t relative_distance;
	int32_t temp = 0.0;
	static uint32_t last_average_time = 1;
	// static uint32_t cycle_start_millis = millis();
	static int32_t last_relative_distance = 0;

	uint32_t current_time = 0;
	// Check controller time internval	#Comment reason: After testing it in MATLAB it turnedout the flushing 
	// (i.e., fill does not improve the results as expected, so it was commented to save computation time)
// 	if ((millis() - cycle_start_millis) >= CONTROLLER_INTERVAL_MS)
// 	{
// #ifdef ULTRASONIC_DEBUG
// 	ESP_LOGI(TAG, "MCU interval timeout, rempy dynamics arrays");
// #endif
// 		fill(us_handle->index, us_handle->average_spacing_error_rate);
// 		fill(us_handle->index, us_handle->relative_acceleraion);

// 		// Update next cycle starting time
// 		cycle_start_millis = millis();
// 	}
	// Check Buffer fill
	us_handle->vel_index == MAX_SAMPLES_VEL ? us_handle->vel_index = 0 : us_handle->vel_index++;
	us_handle->acc_index == MAX_SAMPLES_ACC ? us_handle->acc_index = 0 : us_handle->acc_index++;
	// Start sampling process
#ifdef ULTRASONIC_DEBUG
	ESP_LOGI(TAG, "==============================\n:Start new sampling process...\n");
#endif
	// More compact implementation is to call us_calc_distance_once, but I have some concernes about run time call overhead
	portENTER_CRITICAL(&us_muxtex);
	relative_distance = us_get_distance();
	portENTER_CRITICAL(&us_muxtex);
#ifdef ULTRASONIC_DEBUG
	ESP_LOGD(TAG, "Distance::%d\n", relative_distance);
#endif
	// Average spacing error in n samples taken at m steps...
	abs(relative_distance - last_relative_distance) <= ALLAWED_TOLERANCE ? us_handle->average_spacing_error = last_relative_distance : us_handle->average_spacing_error = relative_distance;
	current_time = millis();
	temp = current_time - last_average_time;
	int index = 0;
	(us_handle->vel_index - 1) == 0 ? index = MAX_SAMPLES_VEL : index = us_handle->vel_index - 1;
	(us_handle->acc_index - 1) == 0 ? index = MAX_SAMPLES_ACC : index = us_handle->acc_index - 1;
	us_handle->average_spacing_error_rate[us_handle->vel_index] = calc_average((float)(1000 * (us_handle->average_spacing_error - last_relative_distance) / temp), us_handle->average_spacing_error_rate);
	us_handle->relative_acceleraion[us_handle->acc_index] = calc_average((float)((us_handle->average_spacing_error_rate[us_handle->vel_index] - us_handle->average_spacing_error_rate[index]) / temp), us_handle->relative_acceleraion);
#ifdef ULTRASONIC_DEBUG
	ESP_LOGD(TAG, "Final average spacing error: %d, last value %d average dist %d\n", us_handle->average_spacing_error, last_relative_distance, relative_distance);
	ESP_LOGD(TAG, "Final average relative velocity: %0.2f , last value is:%0.2f \n", us_handle->average_spacing_error_rate[us_handle->index], us_handle->average_spacing_error_rate[index]);
	ESP_LOGD(TAG, "Final acceleration:%0.2f  last value %0.2f \n", us_handle->relative_acceleraion[us_handle->index], us_handle->relative_acceleraion[index]);
	ESP_LOGD(TAG, "Final average time:%d last value %d\n", current_time, last_average_time);
	ESP_LOGI(TAG, "Done...\n==============================\n");
#endif
	last_relative_distance = relative_distance;
	last_average_time = current_time;
	return;
}

/* ****************** Helper functions ****************** */
void fill(int index, float *buffer)
{
	for (int i = 0; i < sizeof(buffer) + 1; i++)
	{
		if (i == index)
		{
#ifdef ULTRASONIC_DEBUG
	ESP_LOGI(TAG, "Index no. %d left as it is",i);
#endif			
			continue;
		}
		buffer[i] = DUMMY_VALUE;
	}
}

float calc_average(float new_value, float *array_buffer)
{
	float sum = 0.0;
	int8_t valid_samples = 0;
	for (int i = 0; i < (sizeof(array_buffer) + 1); i++)
	{
#ifdef ULTRASONIC_DEBUG
	ESP_LOGV(TAG, "Array elements %f\n",*array_buffer);
#endif	
		if (*array_buffer == DUMMY_VALUE)
		{
			continue;
		}
		sum += *(array_buffer++);
		valid_samples++;
	}
#ifdef ULTRASONIC_DEBUG
	ESP_LOGI(TAG, "Vaid values %d\n",valid_samples);
#endif	
	return (sum + new_value) / (valid_samples + 1);
}