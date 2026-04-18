/*
 * exti.h
 *
 *  Created on: Apr 17, 2026
 *      Author: divya
 */
#include<stm32g4xx.h>
#include<stdlib.h>

#ifndef EXTI_H_
#define EXTI_H_
#define LINE13 (0x01<<13)

/**
 * Configures the interrupt to enable the EXTI Line to PC13 Pin and writing to regetsers to enable the iSR for PC13
 */
void pc13_exti_init(void);

//When the interrupt is triggered the pending bit will be set for that line since we are targetting line 13, then
//bit 13 in Pending Regester should be set when the Interrupt is actually triggered.
//This is one way to just to make sure ISR is actually triggered.


#endif /* EXTI_H_ */
