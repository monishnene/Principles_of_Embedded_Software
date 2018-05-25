/*
 * memory.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#include <stdint.h>
#include<stdlib.h>
#include<stdio.h>
uint8_t* my_memmove(uint8_t* src, uint8_t* dst, size_t length)
{
	uint8_t flag=0,i;
	for(i=0;i<length;i++)
	{
		if(dst==src+i)
		{
			flag=1;
		}
	}

	for(i=0;i<length;i++)
	{
		if(dst+length-1==src+i) /*For handling overlap condition for every iteration*/
		{
			flag=0;
		}
	}
	if(flag==0)
	{
		for(i=0;i<length;i++)
		{
			*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
		}
	}
	if(flag==1)
	{
		for(i=0;i<length;i++)
		{
			*(dst+length-1-i)=*(src+length-i-1); /*Copies from source to destination for every iteration*/
		}
	}

	return dst;
}

uint8_t* my_memcpy(uint8_t* src, uint8_t* dst, size_t length)
{	
	uint8_t i;
	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
	}
	return dst;
}

uint8_t* my_memset(uint8_t* src, size_t length, uint8_t value)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		*(src+i)=value; /*Sets the char value to the memory location for every iteration*/
	}
	return src;
}

uint8_t* my_memzero(uint8_t* src, size_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		*(src+i)=0; /*Clears the source location for every iteration*/
	}
	return src;
}


uint8_t* my_reverse(uint8_t* src, size_t length) /*Function for reversing bytes*/
{
	int8_t temp;
	size_t i,n;
	if(length%2==0) /*If the length is even*/
	{
		n=length/2;
	}
	else
	{
		n=(length-1)/2; /*If the length is odd*/
	}
	for(i=0;i<n;i++) /*Loop for reversing the bytes*/
	{
		 temp = *(src+i);
		 *(src+i) = *(src+length-i-1);
		 *(src+length-i-1) = temp;
	}
	return src;
}

int32_t* reserve_words(size_t length)
{
int32_t* src;
src=malloc(((sizeof(int32_t))*length)); /*To reserve words = length in memory*/
return src;
}

void free_words(uint32_t* src) /*Function to free memory*/
{
free(src);
return;
}
