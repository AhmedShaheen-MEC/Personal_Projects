/*
 * PIR_1_Driver.c
 *
 *  Created on: Apr 15, 2020
 *      Author: ahmed
 */

#include "PIR1_Driver.h"
#include "PIR1_Config.h"

void vPIRInit(void)
{
	PIR_REG_DIR |= (INPUT_STATUS<<PIR_PIN);
	TxLIGHT_REG_DIR |= (OUTPUT_STATUS<<TxLIGHT_PIN);
	TxLIGHT_DATA_OUTPUT &= ~(OUTPUT_STATUS<<TxLIGHT_PIN);
}

void vCheckLight(void)
{
	if(PIR_INPUT_DATA & (OUTPUT_STATUS<<PIR_PIN))
	{
		TxLIGHT_DATA_OUTPUT |= (OUTPUT_STATUS<<TxLIGHT_PIN);
	}
	else
	{
		TxLIGHT_DATA_OUTPUT &= ~(OUTPUT_STATUS<<TxLIGHT_PIN);
	}
}
