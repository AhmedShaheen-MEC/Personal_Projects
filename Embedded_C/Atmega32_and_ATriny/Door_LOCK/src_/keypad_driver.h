/*
 * IncFile1.h
 *
 * Created: 4/7/2020 9:20:18 PM
 *  Author: ahmed
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


// function prototype
void vKeypadInit(void);
unsigned char ucKeypadScan(void); // unsigned char because it returns ASCI it could be unit8_t

// macros
#define INPUT_STATE		0U
#define OUTPUT_STATE	1U	
#define NO_VALID_INPUT		0xFF    /* value out of the range of buttons on keypad */
#define INPUT_STILL_THERE					   ((LINE0_DATAIN&(1U<<LINE0))\
											&&(LINE1_DATAIN&(1U<<LINE1))\
											&&(LINE2_DATAIN&(1U<<LINE2))\
											&&(LINE3_DATAIN&(1U<<LINE3)))


#endif /* INCFILE1_H_ */