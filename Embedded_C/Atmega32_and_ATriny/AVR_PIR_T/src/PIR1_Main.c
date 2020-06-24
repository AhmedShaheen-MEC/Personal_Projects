/*
 * AVR_T.c
 *
 *  Created on: Mar 27, 2020
 *      Author: ahmed
 */

#include <avr/io.h>
#include <util/delay.h>
#include "PIR1_Driver.h"

void main(void)
{
	vPIRInit();

	while (1)
	{
		vCheckLight();
	}
}
