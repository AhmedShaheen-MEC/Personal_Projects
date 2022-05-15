/**
 *
 * platoon_FreeRTOS_common.h - common tasks definitions and inclusion.
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
#ifndef PLATOON_FREERTOS_COMMON_H_
#define PLATOON_FREERTOS_COMMON_H_
/**
   @file: tasks_handle.h
   @function: include all defines, structs and function protorypes.

*/
/* ****************** Includes ****************** */
#include <stdint.h>
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_now_common.h"
#include "platoon_pwm_driver.h"
#include "platoonSDK.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#if ESP_PLATOON_NODE == ESP_NODE_LEADER
#include "platoonLeader_communication.h"
#define DATA_LOGGER_TASK_PRIO			   LEADER_DATA_LOG_TASK_PRIO
#define DISTANCE_CONTROLLER_TASK_PRIO	LEADER_US_TASK_PRIO
#define VELOCITY_CONTROLLER_TASK_PRIO	LEADER_PMW3360_TASK_PRIO 
#elif ESP_PLATOON_NODE == ESP_NODE_VONE
#define DATA_LOGGER_TASK_PRIO			   VONE_DATA_LOG_TASK_PRIO
#define DISTANCE_CONTROLLER_TASK_PRIO	VONE_US_TASK_PRIO
#define VELOCITY_CONTROLLER_TASK_PRIO	VONE_PMW3360_TASK_PRIO 
#elif ESP_PLATOON_NODE == ESP_NODE_VTWO
#define DATA_LOGGER_TASK_PRIO			   VTWO_DATA_LOG_TASK_PRIO
#define DISTANCE_CONTROLLER_TASK_PRIO	VTWO_US_TASK_PRIO
#define VELOCITY_CONTROLLER_TASK_PRIO	VTWO_PMW3360_TASK_PRIO 
#endif

#define DISTANCE_CONTROLLER_STACK_SIZE 5120
#define VELOCITY_CONTROLLER_STACK_SIZE 5120
#define DATA_LOGGER_TASK_STACK_SIZE    2048

#define FREERTOS_TASK_NOTIFICATION_BIT      (1<<0)
#define FREERTOS_TIMER_INT_NOTIFICATION_BIT (1<<1)
#define FREERTOS_RECEIVE_NOTIFICATION_BIT   (1<<2)

/*
   ===========================================================
   =           		RTOS control members             		 =
   ===========================================================
*/
typedef void (*ptask)(void *args);

typedef struct task_descriptor
{
   ptask task;
   void *args;
   char *tag;
   uint32_t stack_size;
   uint8_t priority;
   TaskHandle_t *handle;
   BaseType_t core_id;

} task_descriptor_t;

extern xSemaphoreHandle binSemaphore;
extern TaskHandle_t velocity_conrtoller_handler, distance_conroller_handler, data_logger_handler;
extern task_descriptor_t distance_conroller, speed_conrtoller, data_logger,temp_cmd_handler;
extern ptask pCommon_data_logger_task, pCommon_distance_conroller_task, pCommon_velocity_conrtoller_task;
#define CORE_ZERO	0
#define CORE_ONE	1

/* ****************** Remote action commands ****************** */

typedef enum
{
   START_LEADER_ONLY = 0,
   STOP,
   CACC_START,
   ACC,
   START_TIMEOUT,
   RESTART_DELAY,
   RESTART_IMMEDIATE

} platoon_status_t;
/* ****************** Function prototypes ****************** */
extern void start_time_sync(uint32_t s, uint32_t us);
extern void create_task(task_descriptor_t task_to_create);
extern void analyze_cmd(uint8_t cmd);
extern void CreatTasks();
#endif /* PLATOON_FREERTOS_COMMON_H_ */