/*
 * ADC_interrupt_main.c
 *
 *  Created on: Apr 17, 2020
 *      Author: ahmed
 */


#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{

	ADMUX = 0x00;
	//Channel:
	ADMUX |= (1<<REFS1);
	ADMUX &= ~(1<<REFS0);
	sei();
	// Clock prescaller
	ADCSRA |= (1<<ADPS0) | (1<< ADPS1) | (1<<ADPS2);
	// Interrupt :
	ADCSRA |= (1<< ADIE);
	// Single conversion:
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADSC); // Start conversion at the beginning






}


ISR (ADC_vect)
{
	uint16_t ADC_Reading=0;
	ADC_Reading = ADCL;
	ADC_Reading |= (uint16_t) (ADCH);
	ADCSRA |= (1<<ADSC); // Whenever the ADC interrupt catch something start conversion.


}
