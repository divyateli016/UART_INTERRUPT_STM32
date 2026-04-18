/*
 * exti.c
 *
 *  Created on: Apr 17, 2026
 *      Author: divya
 */
#include "exti.h"
#define GPIOC_EN 	(0x01U<<2)
#define SYSCFG_EN	(0x01<<0)


void pc13_exti_init(void)
{
	//Disable global interrupts
	__disable_irq();
	//Enable the clock access for the GPIOC using RCC and the APB
	RCC->AHB2ENR |= GPIOC_EN;

	//EXTII is the part of the sys module hence need to enable the clock access to SYSConfig which is available in RCC_APB2ENR

	RCC->APB2ENR |= SYSCFG_EN;

	//Set PC13 pin as input
	GPIOC->MODER &= ~(0x01 << 26);
	GPIOC->MODER &= ~(0x01 << 27);

	//Select PORTC for EXTI13 PC13 We need to write to SYSCF_EXTICR13 which is vailable in EXTICR4
	SYSCFG->EXTICR[3] = (0x01U<<5);

	//Unmask EXTI13
	EXTI->IMR1 |= (0x01 << 13);

	//selet falling edge trigger
	EXTI->FTSR1 |= (0x01 << 13);

	//Enable the exti line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Enable Global interrupts
	__enable_irq();

}

