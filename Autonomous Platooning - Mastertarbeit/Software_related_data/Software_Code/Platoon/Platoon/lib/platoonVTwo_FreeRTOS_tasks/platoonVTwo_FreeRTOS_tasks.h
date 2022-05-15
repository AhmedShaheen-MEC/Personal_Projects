/**
 *
 * platoonVTwo_FreeRTOS_tasks.h - Vehicle Two freeRTOS tasks definition
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
#ifndef PLATOONVTWO_FREERTOS_TASKS_H_
#define PLATOONVTWO_FREERTOS_TASKS_H_
/**
   @file: tasks_handle.h
   @function: include all defines, structs and function protorypes.

*/
/* ****************** Includes ****************** */ 
#include <Arduino.h>
#include "platoonSDK.h"
#include "platoon_FreeRTOS_common.h"
#include "platoon_vehicle_motion_handle.h"
/* ****************** Defines ****************** */ 
#define US_SAMPLES            US_MAX_SAMPLES_PER_CTR_FREQ 
#define MINIMUM_SPACING_DIST  VTWO_MINIMUM_SPACING_DIST
#define DECELERATION_RATE     VTWO_DECELERATION_RATE
/*
   ===========================================================
   =           	RTOS Handlers and tasks             		=
   ===========================================================
*/
void data_logger_task(void *arg);
void velocity_controller_task(void *arg);
void distance_controller_task(void *arg);

#endif /* PLATOONVTWO_FREERTOS_TASKS_H_ */
