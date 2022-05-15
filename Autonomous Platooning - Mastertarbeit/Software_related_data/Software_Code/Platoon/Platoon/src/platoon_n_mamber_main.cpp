/* 
 *
 *	platoon_n_member_main.cpp -  Main src file for all platoon members 
 * 						execution starts on PRO_CPU (0), and jumps to Arduino Core (APP_CPU -> 1 )
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

// /********************************** Includes **********************************/
#include "platoonSDK.h"
#include "platoon_vehicle_motion_handle.h"
#include "platoon_relative_motion_handle.h"
#include "platoon_FreeRTOS_common.h"

#if ESP_PLATOON_NODE == ESP_NODE_LEADER
#include "platoonLeader_FreeRTOS_tasks.h"
#include "platoonLeader_communication.h"
static const char *TAG = "Vehicle_Leader";
#elif ESP_PLATOON_NODE == ESP_NODE_VONE
#include "platoonVOne_FreeRTOS_tasks.h"
#include "platoonVOne_communication.h"
static const char *TAG = "Vehicle_vOne";
#elif ESP_PLATOON_NODE == ESP_NODE_VTWO
#include "platoonVTwo_FreeRTOS_tasks.h"
#include "platoonVTwo_communication.h"
static const char *TAG = "Vehicle_vTwo";
#endif

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

/* ****************** Defines ****************** */
#define BAUD_RATE SERIAL_MONITOR_BOARD_RATE

/* ************************* Functions Implementation ************************* */
void platoon_init()
{
	ESP_LOGI(TAG, "Platoon init...");
	esp_now_communication_init();
	laserSensor_init();
	ESP_LOGW(TAG, "No Control msg received yet");
	// while (gReceiveFlag != Logger)
	// {
	// 	//__asm__ __volatile__ ("nop");
	// 	ESP_LOGW(TAG, ".");
	// }

	ESP_LOGW(TAG, "Control msg received ");
	gReceiveFlag = -1;
	// start_time_sync((gControlMsg.synced_time_sec, gControlMsg.synced_time_usec));
	start_time_sync(1624569618, 800);
	// ESP_LOGD(TAG, "Time sync done, platoon syncing start....");
	pCommon_data_logger_task = data_logger_task;
	pCommon_distance_conroller_task = distance_controller_task;
	pCommon_velocity_conrtoller_task = velocity_controller_task;
	analyze_cmd(gControlMsg.cmd);
}

void setup()
{
	Serial.begin(BAUD_RATE);
	/** Platoon settings coming from Data Logger **/
	platoon_init();
}
void loop()
{
	// Arduino loop, delay this task forever
	// Serial.println("This is main");2
	delay(100);
}
