/**
 *
 * esp_now_common.h - ESP-NOW common parameters and definitions between platoon members
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
#ifndef ESP_NOW_COMMON_H_
#define ESP_NOW_COMMON_H_
/**
 * @file: esp_now_common.h
 * @function: include all important and common libs.
 *
 */
/* ****************** Includes ****************** */
#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <ESP32Ticker.h>
#include <ESP32Time.h>
#include "platoonSDK.h"
/* ****************** Defines ****************** */
#define PLATOON_MEMBERS 4
#define MAC_ADDR_LEN 6

#define VEHICLE_LENGTH 190 // 19 cm ::TO be corrected

#define LOGGER_MAC 				{0x24, 0x6F, 0x28, 0x22, 0x72, 0x98}
#define LOGGER_FLAG 			0x98
#define LOGGER_INDEX 			3

#define LEADER_MAC  			{0x24, 0x6F, 0x28, 0x22, 0xA4, 0xF0}
#define LEADER_FLAG 			0xF0
#define LEADER_MAC_INDEX 		0

#define VEHICLE_ONE_MAC  		{0x24, 0x6F, 0x28, 0x22, 0xAA, 0xE4}
#define VEHICLE_ONE_FLAG 		0xE4
#define VEHICLE_ONE_MAC_INDEX 	1

#define VEHICLE_TWO_MAC  		{0x24, 0x6F, 0x28, 0x22, 0x7D, 0xDC}
#define VEHICLE_TWO_FLAG 		0xDC
#define VEHICLE_TWO_MAC_INDEX 	2


#define PLATOON_WIFI_ESO_NOW_CHANNEL_COMMON 	PLATOON_WIFI_ESO_NOW_CHANNEL

#define UPDATE_TIME()				gettimeofday(&tv,NULL)
#define TIME_STAMP_SEC()			({\
									UPDATE_TIME();\
									(tv.tv_sec);\
									})\
									
#define TIME_STAMP_MS()				(tv.tv_usec/1000)		

/* ****************** Structs ****************** */
typedef struct struct_message
{
	float velocity;
	float displacement;
	float acceleration;
	float target_velocity;
	float target_distance;
	float target_acceleration;
	uint32_t time_stamp_s;
	uint16_t time_stamp_ms;
} cam_message;

typedef struct control_msg_t
{
	uint32_t synced_time_sec;
	uint32_t synced_time_msec;
	uint8_t cmd;
} control_msg;

typedef enum
{
	Leader = 0,
	VOne = 1,
	VTwo = 2,
	Logger
} platoon_members_t;
/* ****************** Common Constants ****************** */
const String success = "Delivery Success", fail = "Delivery Fail";

/* ****************** Global Variables Declaration ****************** */
extern struct timeval tv;
extern cam_message gLeaderCamMsg;
extern cam_message gVOneCamMsg;
extern cam_message gVTwoCamMsg;
extern control_msg gControlMsg;

extern uint8_t broadcastAddress[PLATOON_MEMBERS][MAC_ADDR_LEN];
//extern uint16_t gNumberOfSent, gNumberOfReceived; for debug purposes
extern esp_now_peer_info_t peerInfo;

#endif /* ESP_NOW_COMMON_H_ */
