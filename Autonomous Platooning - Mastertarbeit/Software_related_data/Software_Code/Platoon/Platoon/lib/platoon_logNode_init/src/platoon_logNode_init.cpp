/* ****************** Includes ****************** */
#include "platoon_logNode_init.h"

/* ****************** Global Variables ****************** */
static const char *TAG = "Logger_PLATOON_INIT"; // Logging tag
const char *ntpServer = "pool.ntp.org";  // Time sync server settings
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

struct timeval tv;
// Prepare WiFi connections
WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

bool gControlMsgReceived = false; // AWS communication flag

void message_handler(String &topic, String &payload);
void publish_message(String &log_doc);
/* ****************** Function definitions ****************** */
void platoon_logNode_init()
{
  connect_WiFi();               // Connect to WiFi
  update_time();                // Update RTC time
  connect_AWS();                // Connect to AWS
  esp_now_communication_init(); // Prepare ESP-NOW protocol
  while (!gControlMsgReceived)
  {
    client.loop(); // Update receive
    ESP_LOGI(TAG, "Waiting for control action command...");
  }
  gControlMsgReceived = false;
  // AWS command received and updated in the handler.
  start_time_sync(); // Send synced time to platoon members
  ESP_LOGI(TAG, "Platoon init done...");
}

void update_time()
{
  // note : getMicros function has latency of (15-17) us compared to micros()...
  time_t now;                                               // Struct to hold Epoch time
  struct tm timeinfo;                                       // RTC peripheral time struct
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); // Confiugre RTC time
  bool rtc_update_status = getLocalTime(&timeinfo);         // Check the congifured time validity
#if LOGGER_PLATOON_INIT_LOGD
  ESP_LOGD(TAG, "Epoch %d", time(&now));
  if(rtc_update_status != true)
      ESP_LOGD(TAG, "Time update is invalid");
  else
      ESP_LOGD(TAG, "Time updated successfully");
#endif
  ESP_LOGI(TAG, "Time set to %s s, and %d ms", TIME_STAMP_SEC(), TIME_STAMP_MS());
}

void start_time_sync()
{

  ESP_LOGI(TAG, "Sarting time sync...");

  // 1. update control msg:
  gControlMsg.synced_time_sec =  TIME_STAMP_SEC();
  gControlMsg.synced_time_msec = TIME_STAMP_MS();
  ESP_LOGD(TAG, "Sent time: %d s, and %d ms",gControlMsg.synced_time_sec ,  gControlMsg.synced_time_msec );
  // 2. Send to platoon:
  esp_now_send(0, (uint8_t *)&gControlMsg, sizeof(gControlMsg));  
}

esp_err_t connect_WiFi()
{
  // Initalize WiFi peripheral
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  ESP_LOGI(TAG, "Connecting to Wi - Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    ESP_LOGD(TAG, ".");
    delay(250);
  }

  ESP_LOGD(TAG, "Wi-Fi connected\n");
  return ESP_OK;
}

esp_err_t connect_AWS()
{
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, AWS_PORT, net);
  // Create a message handler
  client.onMessage(message_handler);
  ESP_LOGI(TAG, "Connecting to AWS IOT");
  while (!client.connect(THINGNAME))
  {
    delay(100);
  }

  if (!client.connected())
  {
    ESP_LOGE(TAG, "AWS IoT Timeout!");
    return ESP_FAIL;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  ESP_LOGI(TAG, "AWS IoT Connected!");

  return ESP_OK;
}

/* ****************** MQTT handlers ****************** */

void publish_message(String &log_doc)
{
  ESP_LOGD(TAG, "This doc is going to be published %s", log_doc.c_str());
  client.publish(AWS_IOT_PUBLISH_TOPIC, log_doc);

  ESP_LOGI(TAG, "Message was sent successfully");
}

void message_handler(String &topic, String &payload)
{
  StaticJsonDocument<32> control_doc;
  ESP_LOGD(TAG, "The following msg received %s\nTopic:: %s", payload.c_str(), topic.c_str());
  deserializeJson(control_doc, payload);
  gControlMsg.cmd = control_doc["cmd"];
  gControlMsgReceived = true;

  // Ack the remote sender...
  String res = "ACK";
  publish_message(res);
}
