/*
 * project2.c
 *
 *  Created on: Oct 27, 2017
 *      Author: monish
 */
#include "Project2.h"
#include "uart.h"
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
#include "System_MKL25Z4.h"
#include "MKL25Z4.h"
#include "conversion.h"
#define size_tx 200
uint8_t alpha=0,nums=0,punc=0,misc=0;

void sort(uint8_t peek)
{
if(((peek>=65)&&(peek<=90))||((peek>=97)&&(peek<=122)))
alpha++;
else if(((peek>=48)&&(peek<=57)))
nums++;
else if(((peek>=33)&&(peek<=47))||((peek>=91)&&(peek<=96))||((peek>=123)&&(peek<=127)))
punc++;
else
misc++;
return;
}

void project2(void)
{
char stringc[]="\n\r counts of characters",stringa[]="\n\r number of alphabets=",stringp[]="\n\r number of punctuations=",stringm[]="\n\r number of miscellaneous=",stringn[]="\n\r numbers=";
uint8_t i=0,j,circbuf_status,peek=0,n=11,a=23,m=27,p=26,c=23,str_length=0, array[20];
uint8_t* peek_ptr = &peek;
uint8_t* value = array;
SystemInit();
i = CB_init(&tx_buffer,size_tx);
UART_configure();

while(1)
{
	if(receiver_flag==0)
	{
		i = CB_my_peek(&buffer,peek_ptr);
		sort(peek);
		receiver_flag=1;
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = peek;
	}

	circbuf_status=CB_is_full(&buffer);
	if(circbuf_status == Buffer_Full||peek==0xD)
	{
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
				UART0_D = peek;
		UART0->C2 &= ~UART_C2_RIE_MASK;
		UART_send_n(&buffer,buffer.count);
		UART0->C2 |= UART_C2_RIE_MASK;
	}

	if(peek==0x1B)
	{
		UART0->C2 &= ~UART_C2_RIE_MASK;
		str_length += c;
		for(i=0;i<c;i++)
		{
			j=(uint8_t)stringc[i];
			j=CB_buffer_add_item(&tx_buffer,j);
		}
		str_length += a;
		for(i=0;i<a;i++)
		{
			j=(uint8_t)stringa[i];
			j=CB_buffer_add_item(&tx_buffer,j);
		}
		a= my_itoa(alpha,value,10);
		str_length += a-1;
		for(i=0;i<a-1;i++)
				{
					j=CB_buffer_add_item(&tx_buffer,*(value+i));
				}
		str_length += n;
		for(i=0;i<n;i++)
		{
			j=(uint8_t)stringn[i];
			j=CB_buffer_add_item(&tx_buffer,j);
		}
		n= my_itoa(nums,value,10);
		str_length += n-1;
		for(i=0;i<n-1;i++)
		{
			j=CB_buffer_add_item(&tx_buffer,*(value+i));
		}
		str_length += p;
		for(i=0;i<p;i++)
		{
			j=(uint8_t)stringp[i];
			j=CB_buffer_add_item(&tx_buffer,j);
		}
		p= my_itoa(punc,value,10);
		str_length += p-1;
		for(i=0;i<p-1;i++)
		{
				j=CB_buffer_add_item(&tx_buffer,*(value+i));
		}
		str_length += m;
		for(i=0;i<m;i++)
		{
			j=(uint8_t)stringm[i];
			j=CB_buffer_add_item(&tx_buffer,j);
		}
		m= my_itoa(misc,value,10);
		str_length += m-1;
		for(i=0;i<m-1;i++)
		{
				j=CB_buffer_add_item(&tx_buffer,*(value+i));
		}
		UART_send_n(&tx_buffer,str_length);
		UART0->C2 |= UART_C2_RIE_MASK;
	}
}
}
