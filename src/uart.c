/*
 * uart.c
 *
 *  Created on: Oct 27, 2017
 *      Author: monish
 *
 * @file uart.c
 * @brief This file contains circular buffer operation functions.
 * @author monish and sanika
 * @date oct 25s, 2017
 *
 * uart.c
 * @Long description:-
 */
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "conversion.h"
#include "circbuf.h"
#define baud_rate  57600
#define size (1000)
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

void char_count_display(void)
{
	char stringc[]="\n\r counts of characters",stringa[]="\n\r number of alphabets=",stringp[]="\n\r number of punctuations=",stringm[]="\n\r number of miscellaneous=",stringn[]="\n\r numbers=";
	uint8_t i=0,j=0,n=11,a=23,m=27,p=26,c=23,array[20];
	uint8_t* value = array;
	for(i=0;i<c;i++)
	{
		j=(uint8_t)stringc[i];
		printf("%c",j);
	}
	for(i=0;i<a;i++)
	{
		j=(uint8_t)stringa[i];
		printf("%c",j);
	}
	j= my_itoa(alpha,value,10);
	for(i=0;i<j-1;i++)
	{
		printf("%c",*(value+i));
	}
	for(i=0;i<n;i++)
	{
		j=(uint8_t)stringn[i];
		printf("%c",j);
	}
	j= my_itoa(nums,value,10);
	for(i=0;i<j-1;i++)
	{
		printf("%c",*(value+i));
	}
	for(i=0;i<p;i++)
	{
		j=(uint8_t)stringp[i];
		printf("%c",j);
	}
	j= my_itoa(punc,value,10);
	for(i=0;i<j-1;i++)
	{
		printf("%c",*(value+i));
	}
	for(i=0;i<m;i++)
	{
		j=(uint8_t)stringm[i];
		printf("%c",j);
	}
	j= my_itoa(misc,value,10);
	for(i=0;i<j-1;i++)
	{
		printf("%c",*(value+i));
	}
	printf("\n\r");
}

void get_char_count(uint8_t* alpha_ptr,uint8_t* nums_ptr,uint8_t* punc_ptr,uint8_t* misc_ptr)
{
	*(alpha_ptr)=alpha;
	*(nums_ptr)=nums;
	*(punc_ptr)=punc;
	*(misc_ptr)=misc;
	return;
}

uint8_t get_alpha_count(void)
{
	return alpha;
}

uint8_t get_nums_count(void)
{
	return nums;
}

uint8_t get_punc_count(void)
{
	return punc;
}

uint8_t get_misc_count(void)
{
	return misc;
}

/***********************************************************************
 * @brief UART_configure()
 * This function configures the UART
 ***********************************************************************/
void UART_configure(void)
{
	uint8_t i;
	i = CB_init(&buffer,size);
	buffer.head = buffer.buffptr;
	buffer.tail = buffer.buffptr;
	buffer.count = 0;
	buffer.length = size;
	buffer.count = 0;
	if(i==Success)
	return;
}

/***********************************************************************
 * @brief UART_send()
 * This function stores the value to be transmitted in transmit circular buffer
 * @tx_circbuf pointer to circular buffer
 ***********************************************************************/
void UART_send (CB_t* tx_circbuf)
{
uint8_t temp;
CB_buffer_remove_item(tx_circbuf,&temp);
sort(temp);
printf("%c",temp);
return;
}

/*void UART_send_test(void)
{
	uint8_t i = 65;
	while((UART0_S1 & UART_S1_TDRE_MASK)==0);
	 Send the character
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
uint8_t temp,j;
uint8_t* temp_ptr=&temp;
uint8_t i;
for(i=0;i<length;i++)
{
	j = CB_buffer_remove_item(tx_circbuf,temp_ptr);
	sort(*temp_ptr);
	printf("%c",*temp_ptr);
}
if(j==Success)
return;
}

