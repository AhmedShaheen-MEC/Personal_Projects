/**
 *
 * platoonVTwo_communication.h - Vehicle Two ESP-NOW communication handler.
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
#ifndef VTWO_CAM_MSG_HANDLE_H_
#define VTWO_CAM_MSG_HANDLE_H_
/**
  @file: platoon_logNode_communication.h
  @function: define specific logger data
*/
/* ****************** Includes ****************** */
#include "esp_now_common.h"
#include "platoonSDK.h"
#include "platoonVTwo_FreeRTOS_tasks.h"
/* ****************** Global Variables ****************** */
extern uint8_t gReceiveFlag;
#if ESP_NOW_DEBUG
extern uint16_t gReceived, gSent, gSentLogger; 
#endif
/* ****************** Function prototypes ****************** */
void cam_timer_init(void);
esp_err_t esp_now_communication_init(void);

#endif /* VTWO_CAM_MSG_HANDLE_H_ */