/*
 * binary_logger.c
 *
 *  Created on: Nov 25, 2017
 *      Author: monish
 */

#include "circbuf.h"
#include "uart.h"
#include "binary_logger.h"
#include "conversion.h"
#include <stdint.h>
#include <time.h>
#include "profiling.h"
#define log_size 100
#define log_queue_size 20

void log_buffer_configure(void)
{
	uint8_t i;
	i = CB_init(&log_information,log_size);
	log_information.head = log_information.buffptr;
	log_information.tail = log_information.buffptr;
	log_information.count = 0;
	log_information.length = log_size;
	i = CB_init(&log_error,log_size);
	log_error.head = log_error.buffptr;
	log_error.tail = log_error.buffptr;
	log_error.count = 0;
	log_error.length = log_size;
	i = CB_init(&log_warning,log_size);
	log_warning.head = log_warning.buffptr;
	log_warning.tail = log_warning.buffptr;
	log_warning.count = 0;
	log_warning.length = log_size;
	i = CB_init(&log_profiling_result,4*log_size);
	log_profiling_result.head = log_profiling_result.buffptr;
	log_profiling_result.tail = log_profiling_result.buffptr;
	log_profiling_result.count = 0;
	log_profiling_result.length = log_size;
	i = CB_init(&log_queue,log_queue_size);
	log_queue.head = log_queue.buffptr;
	log_queue.tail = log_queue.buffptr;
	log_queue.count = 0;
	log_queue.length = log_size;
	if(i==Success)
	return;
}

void log_item(uint8_t log_id_current)
{
	time_t RTC;
	time(&RTC);
	uint32_t real_time = (uint32_t)RTC;	
	uint32_t count=0,j=0,count_char=0;
	uint8_t temp=0,header='!';
	uint8_t* temp_ptr = &temp;
	count+=log_string(&header,1);
	count+=log_string(&log_id_current,1);
	count+=log_data(&real_time,1);
	switch(log_id_current)
	{
		case LOGGER_INITIALIZED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case GPIO_INITIALIZED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case SYSTEM_INITIALIZED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case SYSTEM_HALTED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case INFO:
		{
			count+=log_integer(log_information.count);
			while(CB_is_empty(&log_information)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_information,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case WARNING:
		{
			count+=log_integer(log_warning.count);
			while(CB_is_empty(&log_warning)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_warning,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case ERROR:
		{
			count+=log_integer(log_error.count);
			while(CB_is_empty(&log_error)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_error,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case PROFILING_STARTED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case PROFILING_RESULT:
		{
			count+=log_integer(log_profiling_result.count);
			while(CB_is_empty(&log_profiling_result)!=Buffer_Empty)
			{
				j = CB_buffer_remove_item(&log_profiling_result,temp_ptr);
				count += log_string(temp_ptr,1);
			}
			count+=log_integer(count);
			break;
		}

		case DATA_RECEIVED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case PROFILING_COMPLETED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case DATA_ANALYSIS_STARTED:
		{
			count+=log_string(&log_id_current,1);
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case DATA_ALPHA_COUNT:
		{
			count_char = get_alpha_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_NUMERIC_COUNT:
		{
			count_char = get_nums_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_PUNCTUATION_COUNT:
		{
			count_char = get_punc_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_MISC_COUNT:
		{
			count_char = get_misc_count();
			count+=log_integer(1);
			count+=log_integer(count_char);
			count+=log_integer(count);
			break;
		}

		case DATA_ANALYSIS_COMPLETED:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}

		case HEARTBEAT:
		{
			count+=log_integer(0);
			count+=log_integer(count);
			break;
		}
	}
	if(j==Success)
	return;
}


uint32_t log_data(uint32_t* src, uint32_t length)
{
	uint8_t* src2=(uint8_t*) src;
	uint8_t i=0,count=0;
	for(i=0;i<4*length;i++)
	{
		CB_buffer_add_item(&buffer,*(src2+i));
		count += get_count_of_1(*src2+i);
	}
	return count;
}

uint32_t log_string(uint8_t* src, uint32_t length)
{

	uint8_t i=0,count=0;
	for(i=0;i<length;i++)
	{
		CB_buffer_add_item(&buffer,*(src+i));
		count += get_count_of_1(*(src+i));
	}
	return count;
}

uint32_t log_integer(uint32_t src)
{
	uint8_t i=0,j=0,count=0;
	uint8_t array[20];
	uint8_t* value = array;
	j = my_itoa(src,value,10);
	for(i=0;i<j;i++)
	{
		CB_buffer_add_item(&buffer,*(value+i));
		count += get_count_of_1(*(value+i));
	}
	return count;
}

uint8_t log_flush(void)
{
	uint8_t i=CB_is_empty(&buffer);
	return i;
}
