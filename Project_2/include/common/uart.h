/*
 * uart.h
 *
 *  Created on: Oct 27, 2017
 *      Author: monis
 */


#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_
#include "circbuf.h"
#include <stdint.h>
uint8_t receiver_flag;
CB_t buffer;
void UART0_IRQHandler(void);
uint8_t UART_receive_n(CB_t* rx_circbuf,uint8_t length);
uint8_t UART_receive(CB_t* rx_circbuf);
void UART_send_n(CB_t* tx_circbuf,uint8_t length);
void UART_send (CB_t* tx_circbuf);
void UART_send_test(void);
void UART_configure(void);

#endif /* INCLUDES_UART_H_ */
0
