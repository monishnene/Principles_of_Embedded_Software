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
else if(!((peek==0x0D)||(peek==0x1B)||(peek==0x0A)||(peek==0x00)))
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
UART_configure();

while(1)
{
	if(receiver_flag==0)
	{
		i = CB_my_peek(&buffer,0,peek_ptr);
		sort(peek);
		receiver_flag=1;
	}
	circbuf_status=CB_is_full(&buffer);
	if(circbuf_status == Buffer_Full||peek==0xD)
	{
		UART0->C2 &= ~UART_C2_RIE_MASK;
		UART_send_n(&buffer,buffer.count-1);
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
					UART0_D = 10;
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
					UART0_D = 13;
		UART0->C2 |= UART_C2_RIE_MASK;

	}

	if(peek==0x1B)
	{
		UART0->C2 &= ~UART_C2_RIE_MASK;
		for(i=0;i<c;i++)
		{
			j=(uint8_t)stringc[i];
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = j;
		}
		for(i=0;i<a;i++)
		{
			j=(uint8_t)stringa[i];
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = j;
		}
		j= my_itoa(alpha,value,10);
		for(i=0;i<j-1;i++)
		{
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = *(value+i);
		}
		for(i=0;i<n;i++)
		{
			j=(uint8_t)stringn[i];
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = j;
		}
		j= my_itoa(nums,value,10);
		for(i=0;i<j-1;i++)
		{
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = *(value+i);
		}
		for(i=0;i<p;i++)
		{
			j=(uint8_t)stringp[i];
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
				UART0_D = j;
		}
		j= my_itoa(punc,value,10);
		for(i=0;i<j-1;i++)
		{
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = *(value+i);
		}
		for(i=0;i<m;i++)
		{
			j=(uint8_t)stringm[i];
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = j;
		}
		j= my_itoa(misc,value,10);
		for(i=0;i<j-1;i++)
		{
			while((UART0_S1 & UART_S1_TDRE_MASK)==0);
			UART0_D = *(value+i);
		}
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = 10;
		while((UART0_S1 & UART_S1_TDRE_MASK)==0);
		UART0_D = 13;
		UART0->C2 |= UART_C2_RIE_MASK;
	}
	peek=0x00;
}
}
