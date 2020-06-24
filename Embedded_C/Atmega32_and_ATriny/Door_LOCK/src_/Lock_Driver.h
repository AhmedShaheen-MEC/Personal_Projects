/*
 * Lock_Driver.h
 *
 *  Created on: Apr 16, 2020
 *      Author: ahmed
 */

#ifndef LOCK_DRIVER_H_
#define LOCK_DRIVER_H_

void vLockInit(void);
void vSetPassword(unsigned char indicator);
unsigned char  bCheckPassword(unsigned char indicator);
void vSaveInput(void);
char vPasswordRun(char keyword);
void vChangePassword(unsigned char keyword);


unsigned int counter;


#endif /* LOCK_DRIVER_H_ */
