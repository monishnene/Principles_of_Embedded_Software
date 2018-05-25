/*
 * uart.c
 *
 *  Created on: Oct 27, 2017
 *      Author: monis
 */
/**
 * @file circbuf.c
 * @brief This file contains circular buffer operation functions.
 * @author monish and sanika
 * @date oct 25s, 2017
 *
 * circbuf.c
 * @Long description:-
 */
#include <stdint.h>
#include "system_MKL25Z4.h"
#include "MKL25Z4.h"
#include "uart.h"
#include "circbuf.h"
#define baud_rate  38400
#define size (1000)


/***********************************************************************
 * @brief UART_configure()
 * This function configures the UART
 ***********************************************************************/
void UART_configure(void)
{
	uint8_t i;
	uint16_t baud = (uint16_t)(SystemCoreClock/(baud_rate*16));
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);
	SIM_SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK);
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL(1);
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
	UART0->S2 = 0X00;
	UART0->C1 = 0X00;
	NVIC_EnableIRQ(UART0_IRQn);
	UART0->C2 |= (UART0_C2_RE_MASK|UART0_C2_TE_MASK);
	UART0->C2 |= UART_C2_RIE_MASK;
	UART0->C3 = 0X00;
	UART0->C5 = 0X00;
	UART0_BDL |= (uint8_t)(baud & UART0_BDL_SBR_MASK);
	UART0_BDH |= (uint8_t)((baud >>8 ) & UART0_BDH_SBR_MASK);
	i = CB_init(&buffer,size);
	return;
}

/***********************************************************************
 * @brief UART_send()
 * This function stores the value to be transmitted in transmit circular buffer
 * @tx_circbuf pointer to circular buffer
 ***********************************************************************/
void UART_send (CB_t* tx_circbuf)
{
uint8_t* temp;
CB_buffer_remove_item(tx_circbuf,temp);
while((UART0_S1 & UART_S1_TDRE_MASK)==0);
UART0_D = *temp;
return;
}

/*void UART_send_test(void)
{
	uint8_t i = 65;
	while((UART0_S1 & UART_S1_TDRE_MASK)==0);
	/* Send the character
	UART0_D = i;
return;
}*/

/***********************************************************************
 * @brief UART_send_n()
 * This function stores values from a certain memory location to be transmitted in transmit circular buffer
 * @tx_circbuf pointer to circular buffer
 * @length length of data
 ***********************************************************************/
void UART_send_n(CB_t* tx_circbuf,uint8_t length)
{
uint8_t* temp;
uint8_t i;
for(i=0;i<length;i++)
{
	CB_buffer_remove_item(tx_circbuf,temp);
	while((UART0_S1 & UART_S1_TDRE_MASK)==0);
	UART0_D = *temp;
}

return;
}


/***********************************************************************
 * @brief UART_receive()
 * This function stores a from receive circular buffer to  a certain memory location
 * @rx_circbuf pointer to circular buffer
 ***********************************************************************/
uint8_t UART_receive(CB_t* rx_circbuf)
{
uint8_t i,temp;
temp = UART0_D;
i = CB_buffer_add_item(rx_circbuf,temp);
return Success;
}
/***********************************************************************
 * @brief UART_receive_n()
 * This function stores multipl000e values from receive circular buffer to  a certain memory location
 * @rx_circbufpointer to circular buffer
 * @length length of data
 ***********************************************************************/
uint8_t UART_receive_n(CB_t* cbptr,uint8_t length)
{
uint8_t temp,i;
for(i=0;i<length;i++)
{
	while((UART0_S1 & UART_S1_RDRF_MASK)==0);
	temp = UART0_D;
	CB_buffer_add_item(cbptr,temp);
}
return Success;
}

/***********************************************************************
 * @brief UART0_IRQHandler()
 * This function checks the register values after interrupt occurs and sends or receives data by UART
 ***********************************************************************/
void UART0_IRQHandler(void)
{
 uint8_t i=UART_receive(&buffer);
 receiver_flag=0;
}
