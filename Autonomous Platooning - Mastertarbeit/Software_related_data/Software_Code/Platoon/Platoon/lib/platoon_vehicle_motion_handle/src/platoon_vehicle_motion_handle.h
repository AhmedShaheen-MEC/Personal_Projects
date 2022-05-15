/**
 *
 * platoon_vehicle_motion_handle.h - Vehicle own dynamics handler module 
 *                              with PWM3360 sensor and communication interface.
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

 /**
  *  ********** Laser Sensor brief **********
  * This library is refactored from Sunjun library @https://github.com/SunjunKim/PMW3360
  * and based on mrjohnk library @https://github.com/mrjohnk/PMW3360DM-T2QU
  * 
  * Modification: Changes to match the ESP32 MCU, and platoon usage. 
  * 
  *	note: PMW3360 Sensors registers.
  *		  # PMW3360_DATA struct format and description
  *			- PMW3360_DATA.isMotion      : bool, True if a motion is detected. 
  *			- PMW3360_DATA.isOnSurface   : bool, True when a chip is on a surface 
  *			- PMW3360_DATA.dx, data.dy   : integer, displacement on x/y directions.
  *			- PMW3360_DATA.SQUAL         : byte, Surface Quality register, max 0x80
  *										* Number of features on the surface = SQUAL * 8
  *			- PMW3360_DATA.rawDataSum    : byte, It reports the upper byte of an 18‐bit counter 
  *          			                   which sums all 1296 raw data in the current frame;
  *                      			       * Avg value = Raw_Data_Sum * 1024 / 1296
  *			- PMW3360_DATA.maxRawData    : byte, Max/Min raw data value in current frame, max=127
  *  		  PMW3360_DATA.minRawData
  *			- PMW3360_DATA.shutter       : unsigned int, shutter is adjusted to keep the average			
  *			                             raw data values within normal operating ranges.
  */
#ifndef PMPLATOON_VEHICLE_MOTION_HANDLE_H_
#define PMPLATOON_VEHICLE_MOTION_HANDLE_H_
/* ****************** Includes ****************** */
#include <Arduino.h>
#include <SPI.h>
#include "PMW3360_firmware_SROM_0x04.h"
#include "platoonSDK.h"

/* ****************** Defines ****************** */
#define Product_ID 0x00
#define Revision_ID 0x01
#define Motion 0x02
#define Delta_X_L 0x03
#define Delta_X_H 0x04
#define Delta_Y_L 0x05
#define Delta_Y_H 0x06
#define SQUAL 0x07
#define Raw_Data_Sum 0x08
#define Maximum_Raw_data 0x09
#define Minimum_Raw_data 0x0A
#define Shutter_Lower 0x0B
#define Shutter_Upper 0x0C
#define Control 0x0D
#define Config1 0x0F
#define Config2 0x10
#define Angle_Tune 0x11
#define Frame_Capture 0x12
#define SROM_Enable 0x13
#define Run_Downshift 0x14
#define Rest1_Rate_Lower 0x15
#define Rest1_Rate_Upper 0x16
#define Rest1_Downshift 0x17
#define Rest2_Rate_Lower 0x18
#define Rest2_Rate_Upper 0x19
#define Rest2_Downshift 0x1A
#define Rest3_Rate_Lower 0x1B
#define Rest3_Rate_Upper 0x1C
#define Observation 0x24
#define Data_Out_Lower 0x25
#define Data_Out_Upper 0x26
#define Raw_Data_Dump 0x29
#define SROM_ID 0x2A
#define Min_SQ_Run 0x2B
#define Raw_Data_Threshold 0x2C
#define Config5 0x2F
#define Power_Up_Reset 0x3A
#define Shutdown 0x3B
#define Inverse_Product_ID 0x3F
#define LiftCutoff_Tune3 0x41
#define Angle_Snap 0x42
#define LiftCutoff_Tune1 0x4A
#define Motion_Burst 0x50
#define LiftCutoff_Tune_Timeout 0x58
#define LiftCutoff_Tune_Min_Length 0x5A
#define SROM_Load_Burst 0x62
#define Lift_Config 0x63
#define Raw_Data_Burst 0x64
#define LiftCutoff_Tune2 0x65

/* ********* PWM configuration parameters ********* */
#define PMW3360_RESOLUTION          LASER_SENSOR_RESOLUTION
#define PEM3360_RSOLUTION_REG_VALUE LASER_SENSOR_RSOLUTION_REG_VALUE
#define CPI_MODE                     0x00
#define INCH_2_CM 2.54
#define ACCUMULATED_COUNT_TO_DISP(count) ((count / PMW3360_RESOLUTION) * INCH_2_CM)

#define D2V(disp, delta_t) (disp / delta_t)
#define V2A(v_f, v_i, t_f, t_i) ((v_f - v_i) / (t_f - t_i))

#define SPI_NCS_PIN   LASER_SENSOR_SPI_NCS_PIN
#define SPI_FREQUENCY LASER_SENSOR_SPI_FREQ
/**
 *  For now, this is a private defines. 
 *          as we are using the default values defined @SPI.cpp ESP32 arduino lib
 */
#define SPI_SCK_PIN    LASER_SENSOR_SPI_SCK_PIN 
#define SPI_MISO_PIN   LASER_SENSOR_SPI_MISO_PIN 
#define SPI_MOSI_PIN   LASER_SENSOR_SPI_MOSI_PIN 

/* ****************** Global Variables ****************** */

extern const unsigned short firmware_length;
extern const unsigned char firmware_data[];


typedef struct dynamics_struct
{
  float displacement;
  float velocity;
  float acceleration;
} dynamics_t;

/* ****************** Function prototypes ****************** */

//Laser Sensor interface functions:
void laserSensor_init(void);
void laserSensor_upload_firmware();
void performStartup(void);
float readDisplacement(void);

// Helper functions
void dispRegisters(void);
int16_t convTwosComp(int16_t b);
void laserSensor_calculate_dynamics(dynamics_t *d);

// SPI communication functions
void laserSensor_com_begin();
void laserSensor_com_end();
uint8_t laserSensor_read_reg(byte reg_addr);
void laserSensor_write_reg(byte reg_addr, byte data);

#endif /* PMPLATOON_VEHICLE_MOTION_HANDLE_H_ */