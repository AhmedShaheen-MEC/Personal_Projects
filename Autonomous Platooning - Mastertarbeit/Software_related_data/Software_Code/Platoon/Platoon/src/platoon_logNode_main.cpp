/* 
 *
 *	platoon_logNode_main.cpp -  Main src file for logging node. 
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

/* ****************** Includes ****************** */
#include "platoonSDK.h"
#include "platoon_logNode_init.h"
#include "soc/rtc_wdt.h"
#include "esp_task_wdt.h"
#include "platoon_logNode_communication.h"
#include <StreamUtils.h>
/* ****************** Defines ****************** */
#define BAUD_RATE SERIAL_MONITOR_BOARD_RATE
/* ****************** Global Variables ****************** */
static const char *TAG = "Logger_node";

String msg = "";
/* ****************** Function Definetion ****************** */
void setup()
{
	Serial.begin(BAUD_RATE);
	platoon_logNode_init();
	WiFi.mode(WIFI_STA);
	// esp_now_communication_init();
}

void loop()
{
	client.loop();
#if LOGGER_MAIN_LOGI
	ESP_LOGI(TAG, "Receive loop...");
#endif
	if (gControlMsgReceived)
	{ 
		esp_now_send(0, (uint8_t *)&gControlMsg, sizeof(gControlMsg));
		gControlMsgReceived = false;
#if ESP_NOW_DEBUG
 		gSent += 3;
		ESP_LOGD(TAG, "Logger sent msgs at %d, No. of sent msgs: %d", rtc.getMillis(), gSent);  
#endif
	}
	if (gReceiveLeader)
	{
		msg = "Leader,";
		msg += ", " + String(gLeaderCamMsg.time_stamp_s);
		msg += ", " + String(gLeaderCamMsg.time_stamp_ms);
		msg += ", " + String(gLeaderCamMsg.velocity);
		msg += ", " + String(gLeaderCamMsg.displacement);
		msg += ", " + String(gLeaderCamMsg.acceleration);
		msg += ", " + String(gLeaderCamMsg.target_velocity);
		msg += ", " + String(gLeaderCamMsg.target_distance);
		msg += ", " + String(gLeaderCamMsg.target_acceleration);
		publish_message(msg);

		gReceiveLeader = false;
	}
	if (gReceiveVOne)
	{
		msg = "VOne,";
		msg += ", " + String(gVOneCamMsg.time_stamp_s);
		msg += ", " + String(gVOneCamMsg.time_stamp_ms);
		msg += ", " + String(gVOneCamMsg.velocity);
		msg += ", " + String(gVOneCamMsg.displacement);
		msg += ", " + String(gVOneCamMsg.acceleration);
		msg += ", " + String(gVOneCamMsg.target_velocity);
		msg += ", " + String(gVOneCamMsg.target_distance);
		msg += ", " + String(gVOneCamMsg.target_acceleration);
		publish_message(msg);

		gReceiveVOne = false;
	}
	if (gReceiveVTwo)
	{
		msg = "VTwo,";
		msg += ", " + String(gVTwoCamMsg.time_stamp_s);
		msg += ", " + String(gVTwoCamMsg.time_stamp_ms);
		msg += ", " + String(gVTwoCamMsg.velocity);
		msg += ", " + String(gVTwoCamMsg.displacement);
		msg += ", " + String(gVTwoCamMsg.acceleration);
		msg += ", " + String(gVTwoCamMsg.target_velocity);
		msg += ", " + String(gVTwoCamMsg.target_distance);
		msg += ", " + String(gVTwoCamMsg.target_acceleration);
		publish_message(msg);

		gReceiveVTwo = false;
	}
}
