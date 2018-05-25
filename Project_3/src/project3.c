/*
 * Project3.c
 *
 *  Created on: Dec 2, 2017
 *      Author: monish and sanika
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "binary_logger.h"
#include "profiling.h"
#include "uart.h"
#include "memory.h"
void profiling_task(void)
{
	uint8_t i=CB_buffer_add_item(&log_queue,PROFILING_STARTED);
	profiling(1000);
	i=CB_buffer_add_item(&log_queue,PROFILING_COMPLETED);
	i=CB_buffer_add_item(&log_queue,PROFILING_RESULT);
	if(i==Success)
	return;
}

void data_analysis_task(void)
{
	uint8_t i=0;
	i=CB_buffer_add_item(&log_queue,DATA_RECEIVED);
	i=CB_buffer_add_item(&log_queue,DATA_ANALYSIS_STARTED);
	i=CB_buffer_add_item(&log_queue,DATA_ALPHA_COUNT);
	i=CB_buffer_add_item(&log_queue,DATA_NUMERIC_COUNT);
	i=CB_buffer_add_item(&log_queue,DATA_PUNCTUATION_COUNT);
	i=CB_buffer_add_item(&log_queue,DATA_MISC_COUNT);
	i=CB_buffer_add_item(&log_queue,DATA_ANALYSIS_COMPLETED);
	if(i==Success)
	return;
}

void project3(void)
{
	uint8_t logger_id_call=0;
	UART_configure();
	log_buffer_configure();
	uint8_t i=0,peek=0;
	i=CB_buffer_add_item(&log_queue,LOGGER_INITIALIZED);
	i=CB_buffer_add_item(&log_queue,GPIO_INITIALIZED);
	i=CB_buffer_add_item(&log_queue,SYSTEM_INITIALIZED);
	while(1)
	{
		i=CB_buffer_add_item(&log_queue,HEARTBEAT);
		printf("%c",peek);	
		if(peek=='D'||peek=='d')
		{
			data_analysis_task();
		}

		if(peek=='P'||peek=='p')
		{
			profiling_task();
		}
		while(CB_is_empty(&log_queue)!= Buffer_Empty)
		{
			i=CB_buffer_remove_item(&log_queue,&logger_id_call);
			log_item(logger_id_call);
		}
		while(CB_is_empty(&buffer)!= Buffer_Empty)
		{
			UART_send(&buffer);
		}
		if(i==Success)
		peek=getchar();
		
	}
}

