/*
 * uart.h
 *
 *  Created on: Apr 16, 2026
 *      Author: divya
 */

#ifndef UART_H_
#define UART_H_

#include<stm32g4xx.h>
#include<stdint.h>
#include "uart.h"


void uart_tx_init(void);
void uart_TxRx_init(void);
void uart2_write(int ch);
char uart2_read_data(void);

#endif /* UART_H_ */
