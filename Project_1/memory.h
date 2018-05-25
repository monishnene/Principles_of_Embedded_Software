/*
 * memory.h
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdint.h>

unsigned char* my_memmove(unsigned char* src, unsigned char* dst, int length);
unsigned char* my_memcpy(unsigned char* src, unsigned char* dst, int length);
unsigned char* my_memset(unsigned char* src, int length, unsigned char value);
unsigned char* my_memzero(unsigned char* src, int length);
uint8_t* my_reverse(unsigned char* src, int length);
int* reserve_words(int length);
void free_words(uint32_t* src);


#endif /* MEMORY_H_ */
