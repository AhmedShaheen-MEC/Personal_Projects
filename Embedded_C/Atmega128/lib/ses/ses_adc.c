/* INCLUDES ******************************************************************/
#include "ses_adc.h"
#include "ses_common.h"
#include "ses_uart.h"

/* DEFINES & MACROS **********************************************************/

#define TEMP_SENSOR_PORT      PORTF
#define TEMP_PIN              2

#define LIGHT_SENSOR_PORT     PORTF
#define LIGHT_PIN             4

#define JOYSTICK_BUTTON_PORT  PORTF         
#define JOUSTICK_PIN          5

#define MICROPHONE_PORT       PORTF
#define MICROPHONE_PIN_P      0
#define MICROPHONE_PIN_N      1                      

#define INPUT_STATUS          0
#define OUTPUT_STATUS         1

// VREF = 1.6 V
#define ADC_TEMP_MAX          400 // C Rt = 12111  u = 0.755, 
#define ADC_TEMP_MIN          200 // C Rt = 5962   u = 0.403
#define ADC_TEMP_RAW_MAX      258 // when temp is 40, input voltage is 0.95 v    
#define ADC_TEMP_RAW_MIN      483 // when temp is 20, input voltage is 1.22 v 
#define ADC_TEMP_FACTOR       50    


/* FUNCTION DEFINITION *******************************************************/

void adc_init(void)
{
     //Init analog devices
     DDR_REGISTER(TEMP_SENSOR_PORT)     |= (INPUT_STATUS<<TEMP_PIN);
     TEMP_SENSOR_PORT &= ~(1<<TEMP_PIN);
     DDR_REGISTER(LIGHT_SENSOR_PORT)    |= (INPUT_STATUS<<LIGHT_PIN);
     LIGHT_SENSOR_PORT &= ~(1<<LIGHT_PIN);
     DDR_REGISTER(JOYSTICK_BUTTON_PORT) |= (INPUT_STATUS<<JOUSTICK_PIN);
     JOYSTICK_BUTTON_PORT &= ~(1<<JOUSTICK_PIN);
     DDR_REGISTER(MICROPHONE_PORT)      |= (INPUT_STATUS<<MICROPHONE_PIN_N);
     MICROPHONE_PORT &= ~(1<<MICROPHONE_PIN_N);
     DDR_REGISTER(MICROPHONE_PORT)      |= (INPUT_STATUS<<MICROPHONE_PIN_P);
     MICROPHONE_PORT &= ~(1<<MICROPHONE_PIN_P);   
     // Disable power saving mode
     PRR0 &= ~(1U<<PRADC);
     // Set reference voltage in the ADMUX register
     ADMUX |=  (1<<REFS1)|(1<<REFS0);
     //Clear the ADLAR Bit for right adjusting (By default cleared)
     ADMUX &= ~(1<<ADLAR);
     // Set ADC pre-scaller
     ADCSRA |=  (1<< ADPS2) | (0<< ADPS1) | (0 <<ADPS0 ); // Pre-scaller (100) == div by 16; (16/16) = 1 MHz clk
     //ADC Enable
     ADCSRA |= (1<<ADEN);
}

uint16_t adc_read(uint8_t adc_channel)
{
    // Validate channel
    if (adc_channel >=8)
     {
          return ADC_INVALID_CHANNEL;
     }
     else
     { 
          ADMUX = (ADMUX & 0b11100000) | adc_channel;  // Select channel, most 3 significant bits un-changed
          ADCSRA |= (1U<<ADSC);
          // Wait until conversion is finished
          while(((ADCSRA >> ADSC) & 1) == 1)
          {
               asm volatile("nop");
          }
          
          // Return 16 bit value directlry
          return ADC;
     }
}

int16_t adc_getTemperature(void)
{
     int16_t adc = adc_read(ADC_TEMP_CH);    
     int16_t slope = (ADC_TEMP_MAX - ADC_TEMP_MIN)*ADC_TEMP_FACTOR / (ADC_TEMP_RAW_MAX - ADC_TEMP_RAW_MIN); // -0.88*50
     int16_t offset = (ADC_TEMP_MAX*ADC_TEMP_FACTOR) - (ADC_TEMP_RAW_MAX * slope); //625.25*50

     return (adc * slope + offset) / (ADC_TEMP_FACTOR*10);
}
