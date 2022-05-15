/**
 *
 * platoon_FreeRTOS_common.h - common FreeRTOS handlers; tasks creation, and declaration.
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
#include "platoon_FreeRTOS_common.h"
/* ****************** Global Variables ****************** */

xSemaphoreHandle binSemaphore;
TaskHandle_t velocity_conrtoller_handler, distance_conroller_handler, data_logger_handler, cmd_handle;
task_descriptor_t distance_conroller, speed_conrtoller, data_logger;
ptask pCommon_data_logger_task, pCommon_distance_conroller_task, pCommon_velocity_conrtoller_task;
/**** One shot task ****/
void cmd_handler(void *arg)
{ // Addtional features to be added in the future...
	analyze_cmd(gControlMsg.cmd);
	vTaskDelete(cmd_handle);
}
// Temporary task for remote action commands 
task_descriptor_t temp_cmd_handler = {.task = cmd_handler,
									  .args = NULL,
									  .tag = "cmd_handler",
									  .stack_size = 4096,
									  .priority = 8,
									  .handle = &cmd_handle,
									  .core_id = CORE_ONE};

/* ****************** FreeRTOS helper functions ****************** */
void create_task(task_descriptor_t task_to_create)
{
	xTaskCreatePinnedToCore(task_to_create.task,
							task_to_create.tag,
							task_to_create.stack_size,
							task_to_create.args,
							task_to_create.priority,
							task_to_create.handle,
							task_to_create.core_id);
	ESP_LOGI(TAG, "Task %s has been created on core %d with priority of %d", task_to_create.tag, task_to_create.core_id, task_to_create.priority);
}

void CreatTasks()
{
	uint32_t startTime = micros();
	binSemaphore = xSemaphoreCreateBinary();
	/*
    ===========================================================
    ESP32 Tasks creation procedure
    Tasks dependency:: Data logger -> Velocity controller -> Distance controller
    ===========================================================
  */
	// Initialzie and create data logger task

	data_logger.task = pCommon_data_logger_task;
	data_logger.args = NULL;
	data_logger.tag = "Data_logger_task";
	data_logger.stack_size = DATA_LOGGER_TASK_STACK_SIZE;
	data_logger.core_id = CORE_ONE;
	data_logger.priority = DATA_LOGGER_TASK_PRIO;
	data_logger.handle = &data_logger_handler;
	create_task(data_logger);

	// Initialzie and create distance controller task
	distance_conroller.task = pCommon_distance_conroller_task;
	distance_conroller.args = NULL;
	distance_conroller.tag = "Distance_controller_task";
	distance_conroller.stack_size = DISTANCE_CONTROLLER_STACK_SIZE;
	distance_conroller.core_id = CORE_ONE;
	distance_conroller.priority = DISTANCE_CONTROLLER_TASK_PRIO;
	distance_conroller.handle = &distance_conroller_handler;
	create_task(distance_conroller);

	// Initialzie and create velocity controller task
	speed_conrtoller.task = pCommon_velocity_conrtoller_task;
	speed_conrtoller.args = NULL;
	speed_conrtoller.tag = "Velocity_controller_task";
	speed_conrtoller.stack_size = VELOCITY_CONTROLLER_STACK_SIZE;
	speed_conrtoller.core_id = CORE_ZERO;
	speed_conrtoller.priority = VELOCITY_CONTROLLER_TASK_PRIO;
	speed_conrtoller.handle = &velocity_conrtoller_handler;
	create_task(speed_conrtoller);

	ESP_LOGI(TAG, "Task creation is done consumed time %d arduino loop will be suspended\n", (micros() - startTime));
#if ESP_PLATOON_NODE == ESP_NODE_LEADER
	cam_timer_init();
#endif
}

void start_time_sync(uint32_t s, uint32_t us)
{
	// Accumulated time since midnight 1/1/1970.
	tv.tv_sec = s;  // epoch time (seconds)
  	tv.tv_usec = us;
	settimeofday(&tv, NULL);
	//rtc.setTime(timeinfo.tm_sec, timeinfo.tm_min, timeinfo.tm_hour-1, timeinfo.tm_mday, timeinfo.tm_mon+1, timeinfo.tm_year+1900);  // 17th Jan 2021 15:24:30
	ESP_LOGI(TAG, "Time set to %d %d ",TIME_STAMP_SEC(),TIME_STAMP_MS());
}

void analyze_cmd(uint8_t cmd)
{
	ESP_LOGI(TAG, "Analyzing command %d", cmd);
	switch (cmd)
	{
	case START_LEADER_ONLY:
		break;

	case STOP:
		break;

	case CACC_START:
		ESP_LOGI(TAG, "Start CACC");
		CreatTasks();
		break;

	case ACC:
		break;

	case START_TIMEOUT:
		break;

	case RESTART_DELAY:
		break;

	case RESTART_IMMEDIATE:
		brushed_motor_forward(0);	// Motor stop
		vTaskSuspendAll();			// Pause all running tasks.
		ESP.restart(); 				// Restart
		break;

	default:
		ESP_LOGI(TAG, "Just noise");
		break;
	}
}