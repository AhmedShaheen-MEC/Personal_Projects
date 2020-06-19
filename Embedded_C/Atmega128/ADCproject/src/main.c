#include "ses_lcd.h"
#include "ses_uart.h"
#include "ses_button.h"
#include "ses_led.h"
#include "ses_adc.h"
#include <util/delay.h>


int main(void) {
	
	uart_init(57600);
     lcd_init();
	button_init();
	led_redInit();
	led_greenInit();
	adc_init();
	fprintf(uartout, "Welcome Boss\n"); 
	led_yellowInit();
	fprintf(uartout, "Time since beginning: \n");
	uint16_t counter = 0;
	uint16_t Light_value = 0;
	int16_t temp = 0;
	uint16_t delay_flag = 0;
	char flag  = 0xFF;
     while (1) 
	{
		
		_delay_ms(500);
		delay_flag += 500;
		flag ^= 0xff;;
		if (flag == 0)
		{
		fprintf(uartout, "Counter value %d \n",counter);
		counter++;
		}
		if (button_isJoystickPressed() == 0)
		{
			led_greenOn();
		}
		else if (button_isRotaryPressed() == 0)
		{
			led_redOn();
		}
		// else
		// {
		// 	led_redToggle();
		// 	led_greenToggle();
		// 	led_yellowToggle();
		// }
		if ( delay_flag == 2500)
		{
			Light_value = adc_read(ADC_LIGHT_CH);
			fprintf(uartout,"Light reading %u \n",Light_value);
			temp = adc_getTemperature();
			fprintf(uartout, "Temp value is in K %d\n", temp);
			fprintf(uartout, "Temp  raw value is %u\n", adc_read(ADC_TEMP_CH));
			delay_flag = 0;
		}
		
		
	}
	return 0;
}






