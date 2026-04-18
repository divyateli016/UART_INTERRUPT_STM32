#include<stdio.h>
#include<stdint.h>
#include<stm32g4xx.h>
#include "exti.h"

#define GPIOA_ENABLE 	 (0x01U<<00)
#define PIN5        	 (0x01U<<5)
#define LED_ON      	 PIN5

char reveived;

//Call back function declaration
static void exti_callback(void);

int main()
{

	//Enable the clock to GPIOA
	RCC->AHB2ENR |= GPIOA_ENABLE;

	//Set PA5 as output pin
	GPIOA->MODER |= (0x01U<<10);//Sets the bit 10
	GPIOA->MODER &= ~(0x01U<<11);//clears the bit 11

	pc13_exti_init();

	//Enable uart to print
	uart_tx_init();

	while(1)
	{
		GPIOA->ODR ^= LED_ON;
		for(int i = 0; i<100000;i++)
		{

		}

	}
}

//Interrupt handler name should be as defined here
//Interrupt lines are grouped and assigned the name in NVIC so based on the line triggered the same function will be
//executed by the NVIC For example lines from 10 to 15 are configured with the name EXTI15_10_IRQn hence for all
//these lines the function with below mentioned name will be executed.

void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR1 & LINE13)!=0)//means interrupt i striggered
	{
		/* cleard the interrupt by clearing the bit, writing 1 to this bit will clear the pending bit*/
		EXTI->PR1 |= (LINE13);

		//Do something what u want t do when ISR Request happens
		exti_callback();
	}

}

static void exti_callback(void)
{
	printf("BTN is pressed\r\n");

}




