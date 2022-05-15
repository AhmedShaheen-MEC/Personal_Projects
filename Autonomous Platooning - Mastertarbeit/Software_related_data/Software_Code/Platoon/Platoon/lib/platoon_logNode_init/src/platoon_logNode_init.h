#ifndef PLATOON_INIT_H_
#define PLATOON_INIT_H_
/* ****************** Includes ****************** */ 
#include "platoonSDK.h"
#include "time.h"
#include <Arduino.h>
#include "secrets.h"
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP32Time.h>
#include <esp_wifi.h>
#include "platoon_logNode_communication.h"
#include <esp_now.h>
/* ****************** Defines ****************** */
// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   AWS_PUBLISH_TOPIC 
#define AWS_IOT_SUBSCRIBE_TOPIC AWS_SUBSCRIBE_TOPIC
#define AWS_PORT			  	AWS_SERVER_PORT

/* ****************** Global Variables ****************** */ 
extern ESP32Time rtc;
extern MQTTClient client;
extern uint8_t status;
extern bool gControlMsgReceived ;
//extern StaticJsonDocument<256> control_doc;

/* ****************** Function prototypes ****************** */ 

void update_time();
void start_time_sync();
void platoon_logNode_init();
void publish_message(String & log_doc);
esp_err_t connect_WiFi();
esp_err_t connect_AWS();

#endif /* PLATOON_INIT_H_ */
