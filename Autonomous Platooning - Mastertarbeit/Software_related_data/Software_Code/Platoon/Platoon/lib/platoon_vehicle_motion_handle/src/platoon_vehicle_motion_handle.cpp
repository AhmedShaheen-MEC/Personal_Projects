/**
 *
 * platoon_vehicle_motion_handle.c - Vehicle own dynamics handler module 
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
/* ****************** Includes ****************** */
#include "platoon_vehicle_motion_handle.h"
/* ****************** Global Variables ****************** */
SPIClass *hspi;
static const char* TAG = "LaserSensor";
portMUX_TYPE pm23360_muxtex = portMUX_INITIALIZER_UNLOCKED;
const int ncs 		= SPI_NCS_PIN; //This is the SPI "slave select" pin that the sensor is hooked up to
const int HSPI_SCK 	= SPI_SCK_PIN;
const int HSPI_MISO	= SPI_MISO_PIN;
const int HSPI_MOSI	= SPI_MOSI_PIN;
const int frequency	= SPI_FREQUENCY;
/* ****************** Funcions ****************** */
//Laser Sensor interface functions:

void laserSensor_init(void)
{
	hspi = new SPIClass(HSPI);
#if  LASER_SENSOR_DEBUG  
    ESP_LOGD(TAG, "HSPI is initialized with the following paramters:");
	ESP_LOGD(TAG, "NCS 	pin:%d", ncs);
	ESP_LOGD(TAG, "SCK 	pin:%d", HSPI_SCK);
	ESP_LOGD(TAG, "MISO pin:%d", HSPI_MISO);
	ESP_LOGD(TAG, "MOSI pin:%d", HSPI_MOSI);
	ESP_LOGD(TAG, "SPI clock frequency", frequency);
#endif	
	pinMode (ncs, OUTPUT);

	hspi->begin();
	hspi->setDataMode(SPI_MODE3);
	hspi->setBitOrder(MSBFIRST);
    hspi->setClockDivider(SPI_CLOCK_DIV128);
  	//hspi->setFrequency(SPI_FREQUENCY);
    
	performStartup();

	delay(5000);
#if  LASER_SENSOR_DEBUG 	
	dispRegisters();
	ESP_LOGI(TAG,"Laser Sensor initialization Done...");
#endif
}

void performStartup(void) 
{
	laserSensor_com_end(); // ensure that the serial port is reset
	laserSensor_com_begin(); // ensure that the serial port is reset
	laserSensor_com_end(); // ensure that the serial port is reset	
	laserSensor_write_reg(Power_Up_Reset, 0x5a); // force reset
	delay(50); // wait for it to reboot
	// read registers 0x02 to 0x06 (and discard the data)
	laserSensor_read_reg(Motion);
	laserSensor_read_reg(Delta_X_L);
	laserSensor_read_reg(Delta_X_H);
	laserSensor_read_reg(Delta_Y_L);
	laserSensor_read_reg(Delta_Y_H);
	// upload the firmware
	laserSensor_upload_firmware();
	delay(10);
#if  LASER_SENSOR_DEBUG 
	ESP_LOGI(TAG,"Optical Chip Initialized");
#endif

}

void laserSensor_upload_firmware() 
{	
	//1. send the firmware to the chip, cf p.18 of the datasheet
#if  LASER_SENSOR_DEBUG 
	ESP_LOGI(TAG,"Uploading firmware...");
#endif
	//2. Write 0 to Rest_En bit of Config2 register to disable Rest mode.
	laserSensor_write_reg(Config2, 0x20);

	// write 0x1d in SROM_enable reg for initializing
	laserSensor_write_reg(SROM_Enable, 0x1d);

	// wait for more than one frame period
	delay(10); // assume that the frame rate is as low as 100fps... even if it should never be that low

	// write 0x18 to SROM_enable to start SROM download
	laserSensor_write_reg(SROM_Enable, 0x18);

	// write the SROM file (=firmware data)
	laserSensor_com_begin();
	hspi->transfer(SROM_Load_Burst | 0x80); // write burst destination adress
	delayMicroseconds(15);

	//send all bytes of the firmware
#if  LASER_SENSOR_DEBUG 
	ESP_LOGI(TAG,"Sending firmware bytes...");
#endif
	unsigned char c;
	for (int i = 0; i < firmware_length; i++) 
	{
		c = (unsigned char)pgm_read_byte(firmware_data + i);
		hspi->transfer(c);
		delayMicroseconds(15);
	}

	//Read the SROM_ID register to verify the ID before any other register reads or writes.
	laserSensor_read_reg(SROM_ID);

	//Write 0x00 to Config2 register for wired mouse or 0x20 for wireless mouse design.
	laserSensor_write_reg(Config2, CPI_MODE);

	//set initial CPI resolution
    laserSensor_write_reg(Config1, PEM3360_RSOLUTION_REG_VALUE);
	laserSensor_com_end();
#if  LASER_SENSOR_DEBUG 
	ESP_LOGI(TAG,"Firmware uploaded successfully...");
#endif	
}

float readDisplacement(void) 
{
	//write 0x01 to Motion register and read from it to freeze the motion values and make them available
	
	laserSensor_write_reg(Motion, 0x01);
	laserSensor_read_reg(Motion);
	int8_t xl = (int8_t)laserSensor_read_reg(Delta_X_L);
	int8_t xh = (int8_t)laserSensor_read_reg(Delta_X_H);
	// int8_t yl = (int8_t)laserSensor_read_reg(Delta_Y_L);		// delta Y was neglected because it seems to add noise to the readings rather than getting more accurate  results
	// int8_t yh = (int8_t)laserSensor_read_reg(Delta_Y_H);		// maybe a further testing could lead to different conclusion
	
	int16_t x_r = abs(((xh << 8) | xl));			// Cars always moves forward
	//int16_t y_r = convTwosComp(((yh << 8) | yl));	// It might tilt. 
#if  LASER_SENSOR_DEBUG  
    ESP_LOGD(TAG, "Read displacement:");
	ESP_LOGD(TAG, "abs(x_r): %d, xl:%d, xh:%d", x_r,xl,xh);
	//ESP_LOGD(TAG, "convTwosComp(y_r): %d, yl:%d, yh:%d", y_r,yl,yh);
	//ESP_LOGD(TAG, "Disp %f CM", ACCUMULATED_COUNT_TO_DISP((float)sqrt((x_r*x_r)+(y_r*y_r))));
#endif	
	//return ACCUMULATED_COUNT_TO_DISP((float)sqrt((x_r*x_r)+(y_r*y_r)));
	return ACCUMULATED_COUNT_TO_DISP((float)x_r);
}

// Helper functions
void laserSensor_calculate_dynamics(dynamics_t * d)
{
	static uint32_t last_time_stamp = millis();
	static float v_last = 0.0;
	portENTER_CRITICAL(&pm23360_muxtex);
	uint32_t current_time = millis();

	d->displacement = readDisplacement(); // Get accumulated displacement since last read operation. 
	portENTER_CRITICAL(&pm23360_muxtex);
		
#if  LASER_SENSOR_DEBUG  
    ESP_LOGD(TAG, "Vehicle Dynamics values:");
	ESP_LOGD(TAG, "last_time_stamp:%d, v_last:%f",last_time_stamp, v_last);
	ESP_LOGD(TAG, "Current time value:%d", current_time);
#endif
	d->velocity = D2V(d->displacement, current_time - last_time_stamp);
	d->acceleration = V2A(d->velocity, v_last, current_time, last_time_stamp);
	
	// Update values:
	last_time_stamp = current_time;
	v_last = d->velocity;

#if  LASER_SENSOR_DEBUG  
	ESP_LOGD(TAG, "New displacement:%f", d->displacement);
	ESP_LOGD(TAG, "New velocity:%f", d->velocity);
	ESP_LOGD(TAG, "New acceleration:%f", d->acceleration);
	ESP_LOGD(TAG, "New (last_time_stamp):%d", last_time_stamp);
	ESP_LOGD(TAG, "New (v_last):%f", v_last);
#endif
	return;
}

void dispRegisters(void) 
{
	int oreg[7] = {0x00, 0x3F, 0x2A, 0x02};
	String oregname[] = {"Product_ID", "Inverse_Product_ID", "SROM_Version", "Motion"};
	byte regres;
	digitalWrite(ncs, LOW);
	int rctr = 0;
	for (rctr = 0; rctr < 4; rctr++) 
	{
		hspi->transfer(oreg[rctr]);
		delay(10);
		ESP_LOGD(TAG,"---");
		//ESP_LOGD(TAG,"%c",oregname[rctr]);
		//ESP_LOGD(TAG,"%x",oreg[rctr]);

		Serial.println(oregname[rctr]);
		Serial.println(oreg[rctr],HEX);
		regres = hspi->transfer(0);
		Serial.println(regres, BIN);
		Serial.println(regres, HEX);

		//ESP_LOGD(TAG,"%x",regres);
		delay(10);
	}
	digitalWrite(ncs, HIGH);
}

int16_t convTwosComp(int16_t b) 
{
	//Convert from 2's complement
	if (b & 0x80) 
	{
		b = -1 * ((b ^ 0xff) + 1);
	}
	return b;
}

/** Communication APIs **/ 

void laserSensor_com_begin() 
{
	digitalWrite(ncs, LOW);
}

void laserSensor_com_end() 
{
	digitalWrite(ncs, HIGH);
}

uint8_t laserSensor_read_reg(byte reg_addr) 
{
	laserSensor_com_begin();

	// send adress of the register, with MSBit = 0 to indicate it's a read
	hspi->transfer(reg_addr & 0x7f );
	delayMicroseconds(100); // tSRAD
	// read data
	uint8_t data = hspi->transfer(0);
	delayMicroseconds(1); // tSCLK-NCS for read operation is 120ns
	laserSensor_com_end();
	delayMicroseconds(19); //  tSRW/tSRR (=20us) minus tSCLK-NCS

	return data;
}

void laserSensor_write_reg(byte reg_addr, byte data) 
{
	laserSensor_com_begin();
	//send adress of the register, with MSBit = 1 to indicate it's a write
	hspi->transfer(reg_addr | 0x80 );
	//sent data
	hspi->transfer(data);
	delayMicroseconds(20); // tSCLK-NCS for write operation
	laserSensor_com_end();
	delayMicroseconds(100); // tSWW/tSWR (=120us) minus tSCLK-NCS. Could be shortened, but is looks like a safe lower bound
}