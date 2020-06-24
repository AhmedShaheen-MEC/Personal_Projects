/*
 * ADC.c
 *
 *  Created on: Apr 3, 2020
 *      Author: ahmed
 */

#include <stdbool.h>
#include <stdint.h>
#include "LDR_RAIN_Config.h"
#include "LDR_RAIN_Driver.h"


void vLDR_RAIN_Init(void)
{
	LDR_REG_DIR |= (INPUT_STATUS<<LDR_PIN);
	TxLIGHT_REG_DIR |= (OUTPUT_STATUS<<TxLIGHT_PIN);
	TxRAIN_REG_DIR |= (OUTPUT_STATUS<<TxRAIN_PIN);
	TxLIGHT_DATA_OUTPUT &= ~(OUTPUT_STATUS<<TxLIGHT_PIN);
	TxRAIN_DATA_OUTPUT &= ~(OUTPUT_STATUS<<TxRAIN_PIN);
	setUpADC();
}

void vCheckLight(void)
{
	if (LDR_INPUT_DATA & (OUTPUT_STATUS<<LDR_PIN))
	{
		TxLIGHT_DATA_OUTPUT |= (OUTPUT_STATUS<<TxLIGHT_PIN);
	}
	else
	{
		TxLIGHT_DATA_OUTPUT &= ~(OUTPUT_STATUS<<TxLIGHT_PIN);
	}
}

uint16_t vCheckRain()
{
	uint16_t result=0;
	result = readADC();
	return result;
}


void setUpADC()
{
	ADMUX &= (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1<< ADPS2) | (1<< ADPS1) | (1 <<ADPS0 ); // to enable interrupt (1<< ADIE);, 	Division FACTOR =128

}

void startConversion(){
	ADCSRA |= (1 << ADSC);
}

uint16_t readADC()
{
//	ADMUX &= 0xF0
//	ADMUX |= channel;
	startConversion();
	while(ADCSRA & (1 << ADSC));
	return  ADC;

}
