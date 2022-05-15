/**
 *
 * platoonVTwo_FreeRTOS_tasks.h - Vehicle Two freeRTOS tasks implementation
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
#include "platoonSDK.h"
#include "platoon_FreeRTOS_common.h"
#include "platoonVTwo_FreeRTOS_tasks.h"
#include "platoonVTwo_communication.h"
#include "platoon_relative_motion_handle.h"
#include "platoon_pwm_driver.h"
/* ****************** Global Variables ****************** */ 	
static const char *TAG = "vTwo_Task_handle";
static uint32_t r_d,r_v, r_a;


void distance_controller_task(void *arg)
{
	ESP_LOGI(TAG, "Distance_controller_task started...");
	xSemaphoreTake(binSemaphore, 100 / portTICK_PERIOD_MS);
	us_data_t us_data;
    us_init(&us_data);
	ESP_LOGI(TAG, "distance_controller_task:: Task preparation done...");
	while (1)
	{
#if VONE_TH_CONTROLLER_FREQ_FLAG
	uint32_t t_f = millis(), t_t = 0;
#endif
		ESP_LOGD(TAG, "Distance_controller_task:: Starting new iteration\n");
		// 1. Spacing error handling:
		calc_relative_dynamics(&us_data);
		// 2. Release flag
		ESP_LOGD(TAG, "Distance_controller_task:: Resume velocity task\n");
		ESP_LOGD(TAG, "Distance_controller_task:: Finished my calculations, waiting for my release\n");
		xSemaphoreTake(binSemaphore, 12 / portTICK_PERIOD_MS);
		r_d = us_data.average_spacing_error;
		r_v = us_data.average_spacing_error_rate[us_data.vel_index];
		r_a = us_data.relative_acceleraion[us_data.acc_index];
#if VONE_TH_CONTROLLER_FREQ_FLAG
	t_t = millis() - t_f; 
	ESP_LOGI(TAG, "t:%d",t_t);
	ESP_LOGD(TAG, "Distance controller task:: measured distance %d", gDistance);
#endif
	}
}

void velocity_controller_task(void *arg)
{
	ESP_LOGI(TAG, "Velocity controller task:: started...");
	
	float new_velocity = 0.0, accumulated_displacement = 0.0;
	float deceleration_ratio = 0.8; // deceleration::ratio of the most recent measured velocity stored in CAM msg...
	/** Initialize PWM**/
	pwm_init();
	dynamics_t d_values;
	memset(&d_values, 0, sizeof(dynamics_t)); // Initialize to zero
	xSemaphoreGive(binSemaphore);
	ESP_LOGI(TAG, "velocity_controller_task:: Task preparation done...");
	while (1)
	{
#if VONE_TH_CONTROLLER_FREQ_FLAG
	uint32_t t_f = millis(), t_t = 0;
	uint32_t static cnt = 0;
#endif
		if (gReceiveFlag == Logger)
		{
			ESP_LOGI(TAG, "velocity_controller_task:: New Action command received\n");
			create_task(temp_cmd_handler);
			gReceiveFlag = -1;
		}
		
		ESP_LOGD(TAG, "velocity_controller_task:: Starting new iteration");
		// // 1. Calc own velocity and accelecration
		laserSensor_calculate_dynamics(&d_values);
		// // 2. calc accumulated displacement: previous set velocity 
		accumulated_displacement += d_values.displacement;
		// // Wait for US to release it's falg
		// // Update cam msg data
		gVTwoCamMsg.displacement = accumulated_displacement; // no need for "+=" since we do it on the "accumulated_displacement" var...
		gVTwoCamMsg.velocity = d_values.velocity;
		gVTwoCamMsg.acceleration = d_values.acceleration;
		gVTwoCamMsg.target_velocity = r_v;
		gVTwoCamMsg.target_distance = r_d;
		gVTwoCamMsg.target_acceleration = r_a;
		xSemaphoreGive(binSemaphore);
		gVTwoCamMsg.time_stamp_s = TIME_STAMP_SEC();
		gVTwoCamMsg.time_stamp_ms = TIME_STAMP_MS();
		// // 3. Set new motor speed
		// // 3.1 when approaching curves slow down
		if (r_d < MINIMUM_SPACING_DIST) // 80 cm
		{
			new_velocity = gVTwoCamMsg.velocity * (deceleration_ratio);
			deceleration_ratio = (deceleration_ratio > 0) ? (deceleration_ratio - DECELERATION_RATE) : DECELERATION_RATE;
		}
		else // 3.2 Set velocity according to prescribed trend
		{
			deceleration_ratio = 0.8;
			//new_velocity =  ;
		}
		brushed_motor_forward(CONVERT_VELOCITY_TO_DUTY_MMS(new_velocity));
		// 4. Log data
		xTaskNotify(data_logger_handler, FREERTOS_TIMER_INT_NOTIFICATION_BIT, eSetBits);		
#if VONE_TH_CONTROLLER_FREQ_FLAG
	t_t = millis() - t_f; 
	ESP_LOGD(TAG,"Velocity controller sent the following CAM content:");
	ESP_LOGD(TAG,"Displacement: %f",     gVTwoCamMsg.displacement);
	ESP_LOGD(TAG,"Velocity: %f",         gVTwoCamMsg.velocity);
	ESP_LOGD(TAG,"Acceleration:",        gVTwoCamMsg.acceleration );
	ESP_LOGD(TAG,"Target_velocity:",     gVTwoCamMsg.target_velocity);
	ESP_LOGD(TAG,"Target_distnace:",     gVTwoCamMsg.target_distance);
	ESP_LOGD(TAG,"Target_acceleration:", gVTwoCamMsg.target_acceleration);
	ESP_LOGD(TAG,"Time_stamp:",          gVTwoCamMsg.time_stamp_s);
    ESP_LOGD(TAG,"Time_stamp:",          gVTwoCamMsg.time_stamp_us);
#endif
	}
}

void data_logger_task(void *arg)
{
	ESP_LOGI(TAG,"Data logger task started...");
	uint32_t notification_value = 0;
	while (1)
	{
		xTaskNotifyWait(0xFFFFFFFF, 0, &notification_value, portMAX_DELAY);
		switch (notification_value)
		{
		case FREERTOS_TASK_NOTIFICATION_BIT:
			esp_now_send(broadcastAddress[LOGGER_INDEX], (uint8_t *)&gVTwoCamMsg, sizeof(cam_message));
			break;
		default: break;
		}		
		ESP_LOGI(TAG,"Data logger task:: Data has been logged...");
#if ESP_NOW_DEBUG
 		gSent++; 
		ESP_LOGD(TAG, "VTwo sent %d msgs to be logged at synced time::%d, %d", gSent, TIME_STAMP_SEC(),TIME_STAMP_MS());
#endif   
	}
}