/*
 * uart.h
 *
 *  Created on: Oct 27, 2017
 *      Author: monish
 */


#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_
#include "circbuf.h"
#include <stdint.h>
uint8_t receiver_flag;
CB_t buffer,receiver_buffer;
void UART0_IRQHandler(void);
uint8_t UART_receive_n(CB_t* rx_circbuf,uint8_t length);
uint8_t UART_receive(CB_t* rx_circbuf);
void UART_send_n(CB_t* tx_circbuf,uint8_t length);
void UART_send (CB_t* tx_circbuf);
void UART_send_test(void);
void UART_configure(void);
void add_circbuf(uint8_t* temp);
void char_count_display(void);
void sort(uint8_t peek);
void get_char_count(uint8_t* alpha_ptr,uint8_t* nums_ptr,uint8_t* punc_ptr,uint8_t* misc_ptr);
uint8_t get_alpha_count(void);
uint8_t get_nums_count(void);
uint8_t get_punc_count(void);
uint8_t get_misc_count(void);

#endif /* INCLUDES_UART_H_ */
