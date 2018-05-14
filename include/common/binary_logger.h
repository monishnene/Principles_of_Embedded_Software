/*
 * binary_logger.h
 *
 *  Created on: Nov 25, 2017
 *      Author: monis
 */

#ifndef INCLUDES_BINARY_LOGGER_H_
#define INCLUDES_BINARY_LOGGER_H_
#include "circbuf.h"
#include "uart.h"
#include "conversion.h"
#include <stdint.h>
typedef enum
{
LOGGER_INITIALIZED=65,
GPIO_INITIALIZED,
SYSTEM_INITIALIZED,
SYSTEM_HALTED,
INFO,
WARNING,
ERROR,
PROFILING_STARTED,
PROFILING_RESULT,
PROFILING_COMPLETED,
DATA_RECEIVED,
DATA_ANALYSIS_STARTED,
DATA_ALPHA_COUNT,
DATA_NUMERIC_COUNT,
DATA_PUNCTUATION_COUNT,
DATA_MISC_COUNT,
DATA_ANALYSIS_COMPLETED,
HEARTBEAT,
}LOG_ID;
CB_t log_information,log_queue,log_warning,log_error,log_profiling_result;
void log_buffer_configure(void);
void log_init(void);
uint32_t log_data(uint32_t* src, uint32_t length);
uint32_t log_string(uint8_t* src, uint32_t length);
uint32_t log_integer(uint32_t src);
uint8_t log_flush(void);
void log_item(uint8_t log_id_current);
#endif /* INCLUDES_BINARY_LOGGER_H_ */
