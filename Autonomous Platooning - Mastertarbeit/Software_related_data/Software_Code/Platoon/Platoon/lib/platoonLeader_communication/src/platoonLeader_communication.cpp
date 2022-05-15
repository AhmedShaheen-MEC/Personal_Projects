/**
 *
 * platoonLeader_communication.cpp - Leader Vehicle ESP-NOW communication handler.
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
#include "platoonLeader_communication.h"
/* ****************** Global Variables ****************** */
struct timeval tv;
hw_timer_t *camTimer;
esp_now_peer_info_t peerInfo;

static const char *TAG = "LEADER_CAM_MSG_HANDLE";

#if ESP_NOW_DEBUG
uint16_t gReceived = 0, gSent = 0, gSentLogger = 0; 
#endif
// Initialize Cam msg data
cam_message gLeaderCamMsg;
control_msg gControlMsg;
cam_message gVOneCamMsg;
cam_message gVTwoCamMsg;
uint8_t broadcastAddress[PLATOON_MEMBERS][MAC_ADDR_LEN] = {LEADER_MAC, VEHICLE_ONE_MAC, VEHICLE_TWO_MAC, LOGGER_MAC};

uint8_t gReceiveFlag = -1; // Nothing received yet.

/* ****************** ESP-NOW Handlers ****************** */
// Network receive event (Ack)
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
	switch (mac_addr[5])
	{
	case VEHICLE_ONE_FLAG:
		ESP_LOGD(TAG, "Last Packet sent to vOne, Send Status: %s", status == ESP_NOW_SEND_SUCCESS ? success.c_str() : fail.c_str());
		break;
	case VEHICLE_TWO_FLAG:
		ESP_LOGD(TAG, "Last Packet sent to vTwo, Send Status: %s", status == ESP_NOW_SEND_SUCCESS ? success.c_str() : fail.c_str());
		break;
	case LOGGER_FLAG:
		ESP_LOGD(TAG, "Last Packet sent to Logger, Send Status: %s", status == ESP_NOW_SEND_SUCCESS ? success.c_str() : fail.c_str());
		break;
	default:
		break;
	}
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
	switch (mac[5])
	{
	case LOGGER_FLAG:
		ESP_LOGI(TAG, "New data received from Logger");
		memcpy(&gControlMsg, incomingData, sizeof(gControlMsg));
		gReceiveFlag = Logger;
#if ESP_NOW_DEBUG
		gReceived++;
		ESP_LOGD(TAG, "Leader received msg at %d, No. of received msgs: %d", rtc.getMillis(), gReceived);
#endif
		break;
	default:
		break;
	}
	return;

}

// ISRs must be placed in internal RAM to avoud cache inclusion
static void IRAM_ATTR TimerHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken;	
	xTaskNotifyFromISR(data_logger_handler, FREERTOS_TIMER_INT_NOTIFICATION_BIT, eSetBits, &xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken)
   	{
       portYIELD_FROM_ISR();
   	}
}

void cam_timer_init(void)
{
	camTimer = timerBegin(TIMER, TIMER_PRE_SCALLER, TIMER_COUNT_UP);
	// Attach onTimer function to our timer.
	timerAttachInterrupt(camTimer, TimerHandler, true);
	// Set alarm to call onTimer function every second (value in microseconds).
	// Repeat the alarm (third parameter)
	timerAlarmWrite(camTimer, TIMER_PERIOD, true);
	// Start an alarm
	timerAlarmEnable(camTimer);
}

esp_err_t esp_now_communication_init(void)
{
	WiFi.mode(WIFI_STA);
	ESP_LOGI(TAG, "ESP MAC:");
	Serial.println( WiFi.macAddress());
	ESP_LOGI(TAG, "WiFi Channel:%d\n", WiFi.channel());

	// Adjust ESP-NOW Channel procedure
	WiFi.printDiag(Serial); // Uncomment to verify channel number before
	esp_wifi_set_promiscuous(true);
	esp_wifi_set_channel(PLATOON_WIFI_ESO_NOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
	esp_wifi_set_promiscuous(false);
	WiFi.printDiag(Serial); // Uncomment to verify channel change after

	if (esp_now_init() != ESP_OK)
	{
		ESP_LOGE(TAG, "Error initializing ESP-NOW");
	}
#ifdef LEADER_ACK_MSGS
	esp_now_register_send_cb(OnDataSent);
#endif
	peerInfo.encrypt = false;

	// Add peers
	memcpy(peerInfo.peer_addr, broadcastAddress[LOGGER_INDEX], MAC_ADDR_LEN);
	if (esp_now_add_peer(&peerInfo) != ESP_OK)
	{
		ESP_LOGE(TAG, "Failed to add peer");
	}

	memcpy(peerInfo.peer_addr, broadcastAddress[VEHICLE_TWO_MAC_INDEX], MAC_ADDR_LEN);
	if (esp_now_add_peer(&peerInfo) != ESP_OK)
	{
		ESP_LOGE(TAG, "Failed to add peer");
	}

	memcpy(peerInfo.peer_addr, broadcastAddress[VEHICLE_ONE_MAC_INDEX], MAC_ADDR_LEN);
	if (esp_now_add_peer(&peerInfo) != ESP_OK)
	{
		ESP_LOGE(TAG, "Failed to add peer");
	}

	// Register for a callback function that will be called when data is received
	esp_now_register_recv_cb(OnDataRecv);

	ESP_LOGI("Init ESP NOW Done..\n");

	return ESP_OK;
}

