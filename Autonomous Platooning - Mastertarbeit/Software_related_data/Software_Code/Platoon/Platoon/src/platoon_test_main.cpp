/* 
 *
 *	platoon_test_main.cpp -  Main src file for testing HW components 
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
#include <WiFi.h>
#include "platoon_pwm_driver.h"
#include "platoon_vehicle_motion_handle.h"
#include "platoon_relative_motion_handle.h"
#include "platoon_leader_vel_trajectory.h"
/* ****************** Defines ****************** */
#define BAUD_RATE SERIAL_MONITOR_BOARD_RATE
float disp = 0.0;
void setup()
{
	Serial.begin(BAUD_RATE);
	char ch = 'n';
	while(ch != 'g')
	{
		ch = fgetc(stdin);
	}
	ESP_LOGI(TAG, "Platoon Hardware testing script");
	ESP_LOGI(TAG, "This vehicle MAC address is: ");
	Serial.println(WiFi.macAddress());
	ESP_LOGI(TAG, "Initialize US sensor...");
	us_init_direct();
	ESP_LOGI(TAG, "Initialize Laser sensor...");
	laserSensor_init();
	ESP_LOGI(TAG, "Initialize PWM...");
	pwm_init();
	ESP_LOGI(TAG, "Initialize Back indicator LED...");
	pinMode(PLATOON_INDICATOR_LED_PIN, OUTPUT);
	digitalWrite(PLATOON_INDICATOR_LED_PIN, HIGH);
	delay(500);
	digitalWrite(PLATOON_INDICATOR_LED_PIN, LOW);
	digitalWrite(PLATOON_INDICATOR_LED_PIN, HIGH);
	delay(500);
	digitalWrite(PLATOON_INDICATOR_LED_PIN, LOW);
	delay(500);
	digitalWrite(PLATOON_INDICATOR_LED_PIN, HIGH);
	ESP_LOGI(TAG, "Initialization done...");
	ESP_LOGI(TAG, "Taking 2 readings for each sensor and move vehicle forward for 3 secs");
	delay(2500);
}
uint8_t ch;
void loop()
{
	ch = fgetc(stdin);
	if (ch != 0xFF)
	{
		fputc(ch, stdout);
	}
	if (ch == 'R')
	{

		ESP_LOGI(TAG, "US Readings...");
		uint16_t distance = us_get_distance();
		ESP_LOGI(TAG, "Dist : %d \n", distance);
		delayMicroseconds(1500);
		distance = us_get_distance();
		ESP_LOGI(TAG, "Dist : %d \n", distance);
		delay(4000);
		ESP_LOGI(TAG,"Laser sensor  readings");
		disp += readDisplacement();
		ESP_LOGI(TAG,"Move motor forward");
		brushed_motor_forward(40);
		delay(4000);
		brushed_motor_backward(60);
		ESP_LOGI(TAG, "Accumulated Displacement: %f", disp);
		disp += readDisplacement();
		delay(4000);
		ESP_LOGI(TAG, "Accumulated Displacement: %f", disp);
	}
	// delay(500);
	// digitalWrite(PLATOON_INDICATOR_LED_PIN, LOW);
	// delay(500);
	// digitalWrite(PLATOON_INDICATOR_LED_PIN, HIGH);
}
