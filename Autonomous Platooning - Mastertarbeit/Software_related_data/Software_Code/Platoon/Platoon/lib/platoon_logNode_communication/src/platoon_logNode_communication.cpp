/**
 *
 * platoon_logNode_communication.cpp - log node communication handlers.
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
#include "platoon_logNode_communication.h"
/* ****************** Global Variables ****************** */
uint8_t broadcastAddress[PLATOON_MEMBERS][MAC_ADDR_LEN] = {LEADER_MAC, VEHICLE_ONE_MAC, VEHICLE_TWO_MAC, LOGGER_MAC};
static const char *TAG = "LOGGER_CAM_HANDLER";
uint16_t gReceived = 0, gSent = 0; 
control_msg gControlMsg = {.synced_time_sec = 0, .synced_time_msec = 0, .cmd = 0};
cam_message gLeaderCamMsg;
cam_message gVOneCamMsg;
cam_message gVTwoCamMsg;
esp_now_peer_info_t peerInfo;

bool gReceiveLeader = false;
bool gReceiveVOne = false;
bool gReceiveVTwo = false;

/* ****************** ESP-NOW Handlers ****************** */
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
	case LEADER_FLAG:
		ESP_LOGD(TAG, "Last Packet sent to LEADER, Send Status: %s", status == ESP_NOW_SEND_SUCCESS ? success.c_str() : fail.c_str());
		break;
	default:
		break;
	}
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
	switch (mac[5])
	{
	case LEADER_FLAG:
		ESP_LOGI(TAG, "New data received from V_Leader");
		memcpy(&gVOneCamMsg, incomingData, sizeof(cam_message));
		gReceiveLeader = true;
		break;
	case VEHICLE_ONE_FLAG:
		ESP_LOGI(TAG, "New data received from V_ONE");
		memcpy(&gVOneCamMsg, incomingData, sizeof(cam_message));
		gReceiveVOne = true;
		break;
	case VEHICLE_TWO_FLAG:
		ESP_LOGI(TAG, "New data received from V_TWO");
		memcpy(&gVTwoCamMsg, incomingData, sizeof(cam_message));
		gReceiveVTwo = true;
		break;
	default:
		break;
	}
#if ESP_NOW_DEBUG
 		gReceived++;
		ESP_LOGD(TAG, "Logger received msg at %d, No. of received msgs: %d", rtc.getMillis(), gReceived);  
#endif
}
/* ****************** Function definitions ****************** */
esp_err_t esp_now_communication_init(void)
{
	ESP_LOGI(TAG, "ESP MAC: %d", WiFi.macAddress());
	ESP_LOGI(TAG, "WiFi Channel:%d\n", WiFi.channel());

	// Adjust ESP-NOW Channel procedure
	WiFi.printDiag(Serial); // Uncomment to verify channel number before
	esp_wifi_set_promiscuous(true);
	esp_wifi_set_channel(6, WIFI_SECOND_CHAN_NONE);
	esp_wifi_set_promiscuous(false);
	WiFi.printDiag(Serial); // Uncomment to verify channel change after

	if (esp_now_init() != ESP_OK)
	{
		ESP_LOGE(TAG, "Error initializing ESP-NOW");
	}
#ifdef LOGGER_ACK_MSGS
	esp_now_register_send_cb(OnDataSent);
#endif
	peerInfo.encrypt = false;
	// Init ESP-NOW
	memcpy(peerInfo.peer_addr, broadcastAddress[LEADER_MAC_INDEX], MAC_ADDR_LEN);

	if (esp_now_add_peer(&peerInfo) != ESP_OK)
	{
		ESP_LOGD(TAG, "Failed to add peer");
	}

	// memcpy(peerInfo.peer_addr, broadcastAddress[VEHICLE_TWO_MAC_INDEX], MAC_ADDR_LEN);
	// if (esp_now_add_peer(&peerInfo) != ESP_OK)
	// {
	// 	ESP_LOGD(TAG, "Failed to add peer");
	// }

	// memcpy(peerInfo.peer_addr, broadcastAddress[VEHICLE_ONE_MAC_INDEX], MAC_ADDR_LEN);
	// if (esp_now_add_peer(&peerInfo) != ESP_OK)
	// {
	// 	ESP_LOGD(TAG, "Failed to add peer");
	// }

	// Register for a callback function that will be called when data is received
	esp_now_register_recv_cb(OnDataRecv);

	return ESP_OK;
}
