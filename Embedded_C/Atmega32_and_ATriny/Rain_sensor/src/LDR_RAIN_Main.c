/*
 * LDR_RAIN_Main.c
 *
 *  Created on: Apr 15, 2020
 *      Author: ahmed
 */
#include "LDR_RAIN_Config.h"
#include "LDR_RAIN_Driver.h"


int main(void)
{
	vLDR_RAIN_Init();

	while(1)
	{

		// LDR part
		vCheckLight();
		// ADC part
		if(vCheckRain() >= 500)
		{
			TxRAIN_DATA_OUTPUT |= (OUTPUT_STATUS << TxRAIN_PIN);
		}
		else
		{
			TxRAIN_DATA_OUTPUT &= (OUTPUT_STATUS<<TxRAIN_PIN);
		}


	}

}

