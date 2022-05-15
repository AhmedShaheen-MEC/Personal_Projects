/**
 *
 * platoonLeader_communication.h - Leader Vehicle ESP-NOW communication handler.
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
#ifndef PLATOONLEADER_COMMUNICATION_H_
#define PLATOONLEADER_COMMUNICATION_H_

/* ****************** Includes ****************** */
#include "esp_now_common.h"
#include "platoon_FreeRTOS_common.h"
#include "platoonSDK.h"

/* ****************** Defines ****************** */
/* CAM Timer settings */
#define TIMER                 0				// Timer group
#define TIMER_PRE_SCALLER     80			// timer is clocked using APB bus with 80MHz clock
#define TIMER_COUNT_UP        true		// count up
#define TIMER_INTERRUPT_EDGE  true		// fire at edge
#define TIMER_PERIOD          CAM_MSG_INTERVAL_MS	// 100 ms

/* ****************** Global Variables ****************** */
extern uint8_t gReceiveFlag;
#if ESP_NOW_DEBUG
extern uint16_t gReceived, gSent, gSentLogger; 
#endif
/* ****************** Function prototypes ****************** */
void cam_timer_init(void);
esp_err_t esp_now_communication_init(void);

#endif /* PLATOONLEADER_COMMUNICATION_H_ */