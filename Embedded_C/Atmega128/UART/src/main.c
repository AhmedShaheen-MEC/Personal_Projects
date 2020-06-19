#include "ses_lcd.h"
#include "ses_uart.h"	
#include <util/delay.h>
#include "ses_led.h"

int main(void) {
	uart_init(57600);
     lcd_init();
	led_greenInit();
     while (1) 
	{
		_delay_ms(5000);
          fprintf(uartout, "START\n");
          //fprintf(lcdout, "START");
		led_greenToggle();	
	}
	return 0;
}






