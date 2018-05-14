/*
 * profiling.c
 *
 *  Created on: Nov 30, 2017
 *      Author: monish
 */
#include "memory.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "binary_logger.h"
#include "profiling.h"
#include <time.h>
uint32_t loop_for_big_memory=1;

/*********************************************************************
* Time calculation function
* pre_interrupt uses SysTick that has a LOAD pointer
* post_interrupt uses SysTick that has a LOAD pointer
* profiling time is the difference between pre and post interrupt
* returns profiling_time
***********************************************************************/

void time_start(uint8_t state)
{
	     pre_interrupt[state] = clock();
	     return;
}

void time_end(uint8_t state)

{
	post_interrupt[state] = clock();
	profiling_time[state] = pre_interrupt[state] - post_interrupt[state];
	return;
}

void log_result(uint32_t length, uint8_t k)
{
		uint8_t i=0,j=0,count=0;
		uint8_t array[20];
		uint8_t* value = array;
		j = my_itoa(k,value,10);
		for(i=0;i<j;i++)
		{
			CB_buffer_add_item(&log_profiling_result,*(value+i));
			count += get_count_of_1(*(value+i));
		}
		j = my_itoa(length,value,10);
		for(i=0;i<j;i++)
		{
			CB_buffer_add_item(&log_profiling_result,*(value+i));
			count += get_count_of_1(*(value+i));
		}
		j = my_itoa(profiling_time[k],value,10);
		for(i=0;i<j;i++)
		{
			CB_buffer_add_item(&log_profiling_result,*(value+i));
			count += get_count_of_1(*(value+i));
		}
		return;
}
/**********************************************************************
* Profiling function that is used for memset and memmove function
* Case 1 uses standard C version
* Case 2 uses memory function
* Case 3 uses memmory function using Optimized O3 flag
* Case 4 uses memset and memmove by using dma
* Free destination and free source
***********************************************************************/

void profiling(uint32_t length)
{
	uint32_t length_temp=0;
	uint8_t i=0,flag_length_change=0,k=0;
	uint8_t* dst = (uint8_t*) malloc(length+10); //memory allocation to dst
	uint8_t* src = dst + 10; //memory allocation to src
	time_start(k);
	if(length>100)
	{
		loop_for_big_memory = length/100 + 1;
		flag_length_change=1;
		length_temp=length;
		length=100;
	}
	for(i=0;i<loop_for_big_memory;i++)
	{
		src=memset((void*)src,(uint8_t)(k+1),4*length); //using standary C version memset
	}
	if (flag_length_change==1)
	{
		length=length_temp;
	}
	time_end(k);
	log_result(length,k);//1
	k++;
	time_start(k);
	if(length>100)
	{
		loop_for_big_memory = length/100 + 1;
		length=100;
	}
	for(i=0;i<loop_for_big_memory;i++)
	{
		src=memmove((void*)dst,(void*)src,4*length); //using standard C version memmove
	}
	if (flag_length_change==1)
	{
		length=length_temp;
	}
	time_end(k);
	log_result(length,k);//2
	k++;
	time_start(k);
	if(length>100)
	{
		loop_for_big_memory = length/100 + 1;
		length=100;
	}
	for(i=0;i<loop_for_big_memory;i++)
	{
		src = my_memset(src, length, (uint8_t)k); //using memory function for memset
	}
	if (flag_length_change==1)
	{
		length=length_temp;
	}
	time_end(k);
	log_result(length,k);//3
	k++;
	time_start(k);
	if(length>100)
	{
		loop_for_big_memory = length/100 + 1;
		length=100;
	}
	for(i=0;i<loop_for_big_memory;i++)
	{
		dst = my_memmove( src, dst, length);          //using memory function for memmove
	}
	if (flag_length_change==1)
	{
		length=length_temp;
	}
	time_end(k);
	log_result(length,k);//4
	k++;
	time_start(k);
	if(length>100)
	{
		loop_for_big_memory = length/100 + 1;
		length=100;
	}
	for(i=0;i<loop_for_big_memory;i++)
	{
		src = my_memset(src, length, (uint8_t) k); //using memory function for memset by O3 flag
	}
	if (flag_length_change==1)
	{
		length=length_temp;
	}
	time_end(k);
	log_result(length,k);//5
	k++;
	time_start(k);
	if(length>100)
	{
		loop_for_big_memory = length/100 + 1;
		length=100;
	}
	for(i=0;i<loop_for_big_memory;i++)
	{
		dst = my_memmove( src, dst, length);           //using memory function for memmove by O3 flag
	}
	if (flag_length_change==1)
	{
		length=length_temp;
	}
	time_end(k);
	log_result(length,k);//6
	k++;
	
	free_words((uint32_t*)dst);                          //frees destination
	free_words((uint32_t*)src);                          //frees source
	return;
}



