/*
 * debug.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#include<stdint.h>
#include<stdio.h>


void print_memory(uint8_t * start, uint32_t length)
{
	uint32_t i;
	for (i=0;i<length;i++)
	{
	#ifdef VERBOSE
	printf("%x",*(start+i));
	#endif		
	}
}


