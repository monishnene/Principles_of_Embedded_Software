/*
* ESD_Buffer_handler.h
 *
 *  Created on: mar 1 , 2018
 *      Author: monish
 */

#include <stdint.h>
typedef struct
{
uint8_t buffer_id;
uint8_t* buffptr;//current address
uint8_t* start;//start address
uint8_t* end;//end address
uint16_t length;//length of buffer
int16_t count;//used
}buffer_typedef;

typedef enum
{
Buffer_Full,
Buffer_Empty,
Success,
Null_Error,
fail,
}Buffer_status;


uint8_t buffer_add_item(buffer* cbptr,uint8_t data);
uint8_t buffer_remove_item(CB_t* cbptr,uint8_t* store);
uint8_t buffer_is_full(CB_t* cbptr);
uint8_t buffer_is_empty(CB_t* cbptr);
uint8_t buffer_my_peek(CB_t* cbptr, uint16_t position,uint8_t* store);
uint8_t buffer_init(CB_t* cbptr,uint16_t length);
uint8_t buffer_destroy(buffer_typedef* cbptr);

