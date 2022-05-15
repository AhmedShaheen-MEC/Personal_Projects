/**
 *
 * platoonVOne_communication.h - Vehicle One ESP-NOW communication handler.
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
#ifndef PLATOON_VONE_COMMUNICATION_H_
#define PLATOON_VONE_COMMUNICATION_H_
/* ****************** Includes ****************** */
#include "esp_now_common.h"
#include "platoonSDK.h"

#include "platoon_FreeRTOS_common.h"
/* ****************** Global Variables ****************** */
extern uint8_t gReceiveFlag;
#if ESP_NOW_DEBUG
extern uint16_t gReceived, gSent, gSentLogger; 
#endif
/* ****************** Function prototypes ****************** */
void cam_timer_init(void);
esp_err_t esp_now_communication_init(void);

#endif /* PLATOON_VONE_COMMUNICATION_H_ */