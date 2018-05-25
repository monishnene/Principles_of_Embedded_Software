/*
* circbuf.h
 *
 *  Created on: oct 22
, 2017
 *      Author: monish and sanika
 */
#include <stdint.h>
#ifndef	CIRCBUF_H_
#define CIRCBUF_H_

typedef struct
{
uint8_t* buffptr;//base
uint8_t* head;//in
uint8_t* tail;//out
uint8_t* size;//limit
uint16_t length;//length of buffer
int16_t count;//used
}CB_t;

typedef enum
{
Buffer_Full,
Buffer_Empty,
Success,
Null_Error,
}CB_status;

extern CB_status cbstatus;
uint8_t CB_buffer_add_item(CB_t* cbptr,uint8_t data);
uint8_t CB_buffer_remove_item(CB_t* cbptr,uint8_t* store);
uint8_t CB_is_full(CB_t* cbptr);
uint8_t CB_is_empty(CB_t* cbptr);
uint8_t CB_my_peek(CB_t* cbptr, uint16_t position,uint8_t* store);
uint8_t CB_init(CB_t* cbptr,uint16_t length);
uint8_t CB_destroy(CB_t* cbptr);
#endif /*circbuf.h*/
