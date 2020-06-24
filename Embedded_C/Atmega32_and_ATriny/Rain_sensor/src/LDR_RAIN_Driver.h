/*
 * LDR_RAIN_Driver.h
 *
 *  Created on: Apr 15, 2020
 *      Author: ahmed
 */

#ifndef LDR_RAIN_DRIVER_H_
#define LDR_RAIN_DRIVER_H_

#define INPUT_STATUS 0U
#define OUTPUT_STATUS 1U

void vLDR_RAIN_Init(void);
void vCheckLight(void);
uint16_t vCheckRain();
void setUpADC();
uint16_t readADC();

#endif /* LDR_RAIN_DRIVER_H_ */
