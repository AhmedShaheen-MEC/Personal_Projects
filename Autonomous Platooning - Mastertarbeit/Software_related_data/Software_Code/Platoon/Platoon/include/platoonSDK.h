/**
 *
 * platoonSDK.h - Provide accessibility to Platoon configuration paramerts as well as debug control...
 *           - this is a shared file, between all ESP32 folders.
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
#ifndef PLATOON_SDK_H_
#define PLATOON_SDK_H_

#include <time.h>
#include <sys/time.h>

/********* Building flags *********/
#define ESP_NODE_LEADER 0
#define ESP_NODE_VONE 1
#define ESP_NODE_VTWO 2
#define ESP_NODE_LOGGER 3

/**
 * Platoon general setups 
 */
#define PLATOON_CONTROLLER_INTERVAL_MS  20
#define SERIAL_MONITOR_BOARD_RATE       115200
#define CAM_MSG_INTERVAL_MS             100000  // 100 ms
#define PLATOON_WIFI_ESO_NOW_CHANNEL    6

/**
 * Communication debugging flags
 * -> Latency calculations + Packet loss
 */
#define ESP_NOW_DEBUG  1
/**
 * Log messages control 
 */
/********* Logger *********/
#define LOGGER_MAIN_LOGI 0
#define LOGGER_PLATOON_INIT_LOGI 1
#define LOGGER_PLATOON_INIT_LOGD 1
#define LOGGER_PLATOON_INIT_LOGE 1

/**
 *  Logger specific parameters
 */
#define LOGGER_ACK_MSGS     1
#define AWS_PUBLISH_TOPIC   "esp32/pub"
#define AWS_SUBSCRIBE_TOPIC "esp32/sub"
#define AWS_SERVER_PORT      8883

/**
 *  Leader specific parameters
 * @note: 
 *      ===========================================================
 *      = Core Zero Tasks, Odd priorities                         =
 *      = Priority:                                               =
 *      = Velocity task -> 5,Core 0 is dedicated only for Dynamics=
 *      ===========================================================
 *      = Core One Tasks, even priorities                         =
 *      = Priority:                                               =
 *      = Data logger tasl -> 4                              	  =
 *      = Distance task -> 6                                      =
 *      =========================================================== 
 */

#define LEADER_ACK_MSGS                 1
#define LEADER_DATA_LOG_TASK_PRIO       6 
#define LEADER_US_TASK_PRIO             4
#define LEADER_PMW3360_TASK_PRIO        5
#define LEADER_DECELERATION_RATE	    0.1
#define LEADER_TRACK_TURNING_LIMIT	    80	// 80 cm
#define LEADER_TH_CONTROLLER_FREQ_FLAG  1
/**
 *  Vehicle ONE specific parameters
 * @note: 
 *      ===========================================================
 *      = Core Zero Tasks, Odd priorities                         =
 *      = Priority:                                               =
 *      = Velocity task -> 5,Core 0 is dedicated only for Dynamics=
 *      ===========================================================
 *      = Core One Tasks, even priorities                         =
 *      = Priority:                                               =
 *      = Data logger tasl -> 4                              	  =
 *      = Distance task -> 6                                      =
 *      =========================================================== 
 */

#define VONE_ACK_MSGS                   1
#define VONE_DATA_LOG_TASK_PRIO         6
#define VONE_US_TASK_PRIO               6
#define VONE_PMW3360_TASK_PRIO          5
#define VONE_DECELERATION_RATE	        0.1
#define VONE_MINIMUM_SPACING_DIST	    5	// cm
#define VONE_TH_CONTROLLER_FREQ_FLAG    0

/**
 *  Vehicle TWO specific parameters
 * @note: 
 *      ===========================================================
 *      = Core Zero Tasks, Odd priorities                         =
 *      = Priority:                                               =
 *      = Velocity task -> 5,Core 0 is dedicated only for Dynamics=
 *      ===========================================================
 *      = Core One Tasks, even priorities                         =
 *      = Priority:                                               =
 *      = Data logger tasl -> 4                              	  =
 *      = Distance task -> 6                                      =
 *      =========================================================== 
 */
#define VTWO_ACK_MSGS   0
#define VTWO_DATA_LOG_TASK_PRIO         6
#define VTWO_US_TASK_PRIO               6
#define VTWO_PMW3360_TASK_PRIO          5
#define VTWO_DECELERATION_RATE	        0.1
#define VTWO_MINIMUM_SPACING_DIST	    5	// cm
#define VTWO_TH_CONTROLLER_FREQ_FLAG    0
 
/** ================================= Sensors settings ================================= **/	 

/**
 * Ultrasonic sensor control parameters
 * Addition info @platoon_relative_motion_handle.h
 */
#define US_DUMMY_VALUE              1000000
#define US_ALLAWED_TOLERANCE        8       // Allow x mm error in the average
#define US_ECHO_PIN                 5       // attach pin D19 NodeMCU to pin Echo of HC-SR04 
#define US_TRIG_PIN                 4       // attach pin D18 NodeMCU to pin Trig of HC-SR04
#define US_MAX_SAMPLES_PER_CTR_FREQ 3       // (0 -> 2)
#define US_MAX_SAMPLES_ACCEELRATION 20      // (0 -> 19)
#define ULTRASONIC_DEBUG            0

/**
 * Laser sensor control parameters
 * We are using hspi ESP32 peripheral
 * Addition info @pwm3360_handle.h
 * Plese note: 
 *      In this parameters, it was assumed that all vehicles has
 *      the same motor, mechanical components, and same size.
 *      - To alter vehicles model, re-define these paramter for each platoon memmber.
 * Sensor resolution mapping: starts with 0x00 -> 100 cpi, ranging from (0 - 120) septs
 *      To determine the correct value:
 *              Ex: 5000 cpi -> Reg_value: 0x(5000/100)-1
 */
// PMW3360 Cotrols
#define LASER_SENSOR_RESOLUTION             1800
#define LASER_SENSOR_RSOLUTION_REG_VALUE    0X11
#define LASER_SENSOR_DEBUG                  1
#define LASER_SENSOR_SPI_NCS_PIN            15
#define LASER_SENSOR_SPI_SCK_PIN            14
#define LASER_SENSOR_SPI_MISO_PIN           12
#define LASER_SENSOR_SPI_MOSI_PIN           13
#define LASER_SENSOR_SPI_FREQ               3000000

/**
 * PWM Paramters & Cars parameters
 * We are using MCPWM_UNIT 0, and MCPWM_TIMER 1
 * Addition info @platoon_pwm_driver.h
 * Plese note: 
 *      In this parameters, it was assumed that all vehicles has
 *      the same motor, mechanical components, and same size.
 *      - To alter vehicles model, re-define these paramter for each platoon memmber.
 * MACROS description:
 *      1. Max output from motor driver is 11 V
 *      2. MAx motor voltage is 18 V 
 *      3. Max motor revolutions is 18000
 *      4. Max Controlable speed is : (11* (18000/18))
 *      5. PWM wave generated from 32 bit timer (Max PWM value is 65534)
 * 
 *  Min PWM value is 30
 */
// Motions controls
#define MCPWM_GPIO0_A_OUT           33
#define MCPWM_GPIO0_B_OUT           18
#define MCPWM_MAX_PWM_VOLTAGE	    11	
#define MCPWM_MAX_MOTOR_VOLTAGE	    18
#define MCPWM_MAX_MOTOR_REV   	    18000
#define MCPWM_MAX_MOTOR_Vin_REV		((MCPWM_MAX_MOTOR_REV*MAX_PWM_VOLTAGE)/MAX_MOTOR_VOLTAGE)	// 18.000 rpm ~= 47123.8 mm/s
#define MCPWM_MAX_PWM_VALU		    65534  
#define MCPWM_MOTOR_WHEEL_DIAMETER  0.025   // 25 mm , to be correlated...
#define MCPWM_WAVE_FREQUENCY        5000
#define MCPWM_DEBUG                 0

/**
 *  General Pltoorn testing flags
 *  more info @platoon_test_main.cpp
 */
#define PLATOON_TEAT_US     1
#define PLATOON_TEST_LASER  0
#define PLATOON_PWM_TEST    1
#define PLATOON_GET_MAC     0

/**
 * 
 * Notification LEDs:
 * Note: Indicator LEDs tested but not integrated yet in the software!
 */
#define PLATOON_INDICATOR_LED_PIN 32
#endif /* PLATOON_SDK_H_  */