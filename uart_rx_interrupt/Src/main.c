#include<stdio.h>
#include<stdint.h>
#include<stm32g4xx.h>
#include "uart.h"

#define GPIOA_ENABLE 	 (0x01U<<00)
#define PIN5        	 (0x01U<<5)
#define LED_ON      	 PIN5

#define USART_STATUS_RX		(0x01<<5)
#define USART_STATUS_TX		(0x01U<<7)

static void uart_callback(void);
static void uart_callback_tx(char ch);

char reveived;

int main()
{
	//Enable the clock for AHB2 bus
	RCC->AHB2ENR |= GPIOA_ENABLE;


	//Configure Pin 5 of PORTA as the output
	GPIOA->MODER |= (0x01U<<10);
	GPIOA->MODER &= ~(0x01U<<11);

	//uart_tx_init();
	//uart_TxRx_init();

	uart2_Rx_interrupt_init();
	uart2_tx_interrupt_init();
	while(1)
	{
		//uart2_write('Y');
		//printf("Hello from STM32...\r\n");
		//reveived = uart2_read_data();
	}
}

static void uart_callback(void)
{
	reveived = USART2->RDR;
			if(reveived == '1')
			{
				GPIOA->ODR = LED_ON;
			}
			else
			{
				GPIOA->ODR &= ~(LED_ON);
			}

}

static void uart_callback_tx(char ch)
{
	GPIOA->ODR |=LED_ON;
	USART2->TDR = (ch & 0xFF);

}
/*
void USART2_IRQHandler(void)
{
	//Check if the data is received

	if(USART2->ISR & USART_STATUS_RX)
	{
		uart_callback();
	}
}
*/
void USART2_IRQHandler(void)
{
	if(USART2->ISR & USART_STATUS_TX)
	{
		uart_callback_tx('Y');
	}
}

