/**
 *
 * platoonLeader_FreeRTOS_tasks.cpp - Leader Vehicle freeRTOS tasks implementation
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
#include "platoonLeader_FreeRTOS_tasks.h"
#include "platoonLeader_communication.h"
#include "platoon_relative_motion_handle.h"
#include "platoon_pwm_driver.h"
/* ****************** Global Variables ****************** */
static const char *TAG = "Leader_Task_handle";



void distance_controller_task(void *arg)
{
	ESP_LOGI(TAG, "Distance_controller_task started...");
	xSemaphoreTake(binSemaphore, 100 / portTICK_PERIOD_MS);
	float new_velocity = 0.0;
	uint16_t distance = 0;
	float deceleration_ratio = 0.8; // deceleration::ratio of the most recent measured velocity stored in CAM msg...
	us_init_direct();
	pwm_init();
	ESP_LOGI(TAG, "distance_controller_task:: Task preparation done...");
	uint16_t index = 0;
	while (1)
	{
#if LEADER_TH_CONTROLLER_FREQ_FLAG
	uint32_t t_f = millis(), t_t = 0;
#endif
		ESP_LOGD(TAG, "Distance_controller_task:: Starting new iteration\n");
		// 1. Spacing error handling:
		distance = us_get_distance();
		// 2. Release flag
		ESP_LOGD(TAG, "Distance_controller_task:: Finished my calculations, waiting for my release\n");
		// // 3. Set new motor speed
		// // 3.1 when approaching curves slow down
		if (distance < TRACK_TURNING_LIMIT) // 80 cm
		{
			new_velocity = gLeaderCamMsg.velocity * (deceleration_ratio);
			deceleration_ratio = (deceleration_ratio > 0) ? (deceleration_ratio - DECELERATION_RATE) : DECELERATION_RATE;
		}
		else // 3.2 Set velocity according to prescribed trend
		{
			deceleration_ratio = 0.8;
			new_velocity =  leader_velocity_profile[index];
			index == (PROFILE_LENGTH-1) ? index =0 : index++;
		}
		brushed_motor_forward(new_velocity);

#if LEADER_TH_CONTROLLER_FREQ_FLAG
	t_t = millis() - t_f; 
	ESP_LOGI(TAG, "t:%d",t_t);
	ESP_LOGD(TAG, "Distance controller task:: measured distance %d", gDistance);
#endif
	}
}

void velocity_controller_task(void *arg)
{
	ESP_LOGI(TAG, "Velocity controller task:: started...");
	
	float accumulated_displacement = 0.0;
	dynamics_t d_values;
	memset(&d_values, 0, sizeof(dynamics_t)); // Initialize to zero
	xSemaphoreGive(binSemaphore);
	ESP_LOGI(TAG, "velocity_controller_task:: Task preparation done...");
	while (1)
	{
#if LEADER_TH_CONTROLLER_FREQ_FLAG
	uint32_t t_f = millis(), t_t = 0;
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
		ESP_LOGD(TAG, "velocity_controller_task:: Finished my calculations, waiting for my release");
		// // 2. Relative information handling	-- Leader, no relative data to handle...
		// // Update cam msg data
		gLeaderCamMsg.displacement = accumulated_displacement; // no need for "+=" since we do it on the "accumulated_displacement" var...
		gLeaderCamMsg.velocity = d_values.velocity;
		gLeaderCamMsg.acceleration = d_values.acceleration;
		//gLeaderCamMsg.target_velocity =;
		//gLeaderCamMsg.target_distance = ;
		//gLeaderCamMsg.target_accelecration = ;
		gLeaderCamMsg.time_stamp_s = TIME_STAMP_SEC();
		gLeaderCamMsg.time_stamp_ms = TIME_STAMP_MS();
		// 4. Log data
		// CAM data are ready to be logged
		xTaskNotify(data_logger_handler, FREERTOS_TIMER_INT_NOTIFICATION_BIT, eSetBits);		
#if LEADER_TH_CONTROLLER_FREQ_FLAG
	t_t = millis() - t_f; 
	ESP_LOGI(TAG, "%d", t_t);
	ESP_LOGD(TAG,"Velocity controller sent the following CAM content:");
	ESP_LOGD(TAG,"Displacement: %f", gLeaderCamMsg.displacement);
	ESP_LOGD(TAG,"Velocity: %f", gLeaderCamMsg.velocity);
	ESP_LOGD(TAG,"Acceleration:", gLeaderCamMsg.acceleration );
	ESP_LOGD(TAG,"Target_velocity:", gLeaderCamMsg.target_velocity);
	ESP_LOGD(TAG,"Target_distnace:", gLeaderCamMsg.target_distance);
	ESP_LOGD(TAG,"Target_acceleration:", gLeaderCamMsg.target_acceleration);
	ESP_LOGD(TAG,"Time_stamp:", gLeaderCamMsg.time_stamp);
#endif
	}
}

void data_logger_task(void *arg)
{
	ESP_LOGI(TAG, "Data logger task started...");
	uint32_t notification_value = 0;
	while (1)
	{	
		xTaskNotifyWait(0xFFFFFFFF, 0, &notification_value, portMAX_DELAY);
		switch (notification_value)
		{
		case FREERTOS_TASK_NOTIFICATION_BIT:
			esp_now_send(broadcastAddress[LOGGER_INDEX], (uint8_t *)&gLeaderCamMsg, sizeof(cam_message));
			break;
		case FREERTOS_TIMER_INT_NOTIFICATION_BIT:
			esp_now_send(broadcastAddress[VEHICLE_TWO_MAC_INDEX], (uint8_t *)&gLeaderCamMsg, sizeof(cam_message));
			esp_now_send(broadcastAddress[VEHICLE_ONE_MAC_INDEX], (uint8_t *)&gLeaderCamMsg, sizeof(cam_message));
			break;
		default:break;
		}
#if ESP_NOW_DEBUG
 		gSent++; 
		ESP_LOGD(TAG, "Leader sent %d msgs to be logged at synced time::%d, %d", gSent, TIME_STAMP_SEC(),TIME_STAMP_MS());
#endif
		ESP_LOGI(TAG, "Data logged+");
	}
}
