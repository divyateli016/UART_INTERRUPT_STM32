/*
 * uart.c
 *
 *  Created on: Apr 16, 2026
 *      Author: divya
 */
#include "uart.h"

#define GPIOA_ENABLE 	 (0x01U<<00)
#define PIN5        	 (0x01U<<5)
#define LED_ON      	 PIN5
#define BSS_VALUE 		 (0x01U<<5)

//define clock enable masks to enable the clock for USART2 in APB1ENR Register
#define USART2_CLK_EN		(0x01U<<17)
#define CR1_TE		    	(0x01U<<3)
#define CR1_RX				(0x01<<2)
#define CR1_UART_EN 		(0x01U<<0)
#define USART_STATUS_TX		(0x01U<<7)
#define USART_STATUS_RX		(0x01<<5)

#define CR1_RXNEIE			(0x01<<5)

#define SYS_FREQ 	16000000
#define APB1CLK 	SYS_FREQ
#define BAUDRATE 	115200


static void uart_set_baudrate(USART_TypeDef* UART,uint32_t periphclk,uint32_t baudRate);
static uint16_t compute_uart_bd(uint32_t periphclk, uint32_t baudRate);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart_tx_init(void)
{
	/*** This will initialize and configure the PA2 pin as TX pin ***/
	/** First enable the clock to PORTA Pin2 ***/
	RCC->AHB2ENR |= GPIOA_ENABLE;
	/*** Configure PA2 Pin as Alternate function using MODER Register ***/

	//Writing 10 to the 5,4 bits( MODE2[1:0] for pin2 in MODER Register configures the PA2 pin in lternte function mode
	GPIOA->MODER &= ~(0x01U<<4);//clears the bit 4
	GPIOA->MODER |= (0x01U<<5);//Sets the bit 5


	/** Alternate function type as USART_TX ( AF7) (Alternae function 7 given in Alternate function table)***/
	/** 0111 for AF7**/
	//GPIOA->AFR[0] |= (0x07U<<8);
	//or bit by bit
	GPIOA->AFR[0] |= (0x01U<<8);
	GPIOA->AFR[0] |= (0x01U<<9);
	GPIOA->AFR[0] |= (0x01U<<10);
	GPIOA->AFR[0] &= ~(0x01U<<11);

	/** Enable the clock to USAR2 through APB1ENR Regester **/
	RCC->APB1ENR1 |= USART2_CLK_EN;

	//Set the direction of the Pin s TX Tranfer direction
	/** this selects Mode M1 00 i start bit , 8 data bits and n stop bits**/
	/** even parity **/
	/** Hardware flow control is disabled **/
	/** set baud rate to the UART **/
	uart_set_baudrate(USART2, APB1CLK, BAUDRATE);

	USART2->CR1 = CR1_TE;//Clear everything nd just set the TE bit in the control register

	//Enable the UART through CR1 regester
	USART2->CR1 |= CR1_UART_EN;



}

void uart_TxRx_init(void)
{
	/*** This will initialize and configure the PA2 pin as TX pin ***/
	/** First enable the clock to PORTA Pin2 ***/
	RCC->AHB2ENR |= GPIOA_ENABLE;
	/*** Configure PA2 Pin as Alternate function using MODER Register ***/

	//Writing 10 to the 5,4 bits( MODE2[1:0] for pin2 in MODER Register configures the PA2 pin in lternte function mode
	GPIOA->MODER &= ~(0x01U<<4);//clears the bit 4
	GPIOA->MODER |= (0x01U<<5);//Sets the bit 5


	/** Alternate function type as USART_TX ( AF7) (Alternae function 7 given in Alternate function table)***/
	/** 0111 for AF7**/
	//GPIOA->AFR[0] |= (0x07U<<8);
	//or bit by bit
	GPIOA->AFR[0] |= (0x01U<<8);
	GPIOA->AFR[0] |= (0x01U<<9);
	GPIOA->AFR[0] |= (0x01U<<10);
	GPIOA->AFR[0] &= ~(0x01U<<11);

	/** Set PA3 oin as alternate function pin for RX ***/
	GPIOA->MODER &= ~(0x01<<6);
	GPIOA->MODER |=  (0x01<<7);

	//Set it as a AF7 for RX pin using AFR register
	GPIOA->AFR[0] |= (0x01U<<12);
	GPIOA->AFR[0] |= (0x01U<<13);
	GPIOA->AFR[0] |= (0x01U<<14);
	GPIOA->AFR[0] &= ~(0x01U<<15);


	/** Enable the clock to USAR2 through APB1ENR Regester **/
	RCC->APB1ENR1 |= USART2_CLK_EN;

	//Set the direction of the Pin s TX Tranfer direction
	/** this selects Mode M1 00 i start bit , 8 data bits and n stop bits**/
	/** even parity **/
	/** Hardware flow control is disabled **/
	/** set baud rate to the UART **/
	uart_set_baudrate(USART2, APB1CLK, BAUDRATE);

	USART2->CR1 = (CR1_TE|CR1_RX);//Clear everything nd just set the TE bit in the control register
	USART2->CR1 |= CR1_RXNEIE;
	//After enabling the Interrupt bit in any regester Remeber to enable it in NVIC

	NVIC_EnableIRQ(USART2_IRQn);

	//Enable the UART through CR1 regester
	USART2->CR1 |= CR1_UART_EN;



}

void uart2_write(int ch)
{
	/* make sure that Trasmit data regetser is empty **/
	/** Write to Transmit Data register**/
	while(!(USART2->ISR & USART_STATUS_TX))
	{
		//Wait untill Transmit register become empty

	}
	USART2->TDR = (ch & 0xFF);
}

char uart2_read_data(void)
{
	//make sure receive data regester is not emoty
	while(!(USART2->ISR & USART_STATUS_RX))
	{

	}
	return USART2->RDR;

}
static void uart_set_baudrate(USART_TypeDef* UART,uint32_t periphclk,uint32_t baudRate)
{
	UART->BRR = compute_uart_bd(periphclk,baudRate);
}

static uint16_t compute_uart_bd(uint32_t periphclk, uint32_t baudRate)
{
	return ((periphclk+(baudRate/2U))/baudRate);
}


