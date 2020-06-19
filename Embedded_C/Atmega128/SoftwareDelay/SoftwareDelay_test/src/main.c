#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<avr/io.h>

void wait(uint16_t miliseconds)
{
uint16_t i = 0; // 16 bit unsigned integer
for (i = 0 ; i < (miliseconds* 244) ; i++) 
{
    for ( uint8_t j = 0; j < 63 ; j++)
    {
        asm volatile ("nop");
    }
    
}  

}
/**Toggles the red LED of the SES-board*/
int main(void) 
{
    DDRG |= 0x02;
	
	while (1) 
	{
		wait(5000);
		PORTG ^= 0x02;
	}
}
