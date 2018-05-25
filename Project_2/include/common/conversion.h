/*
 * conversion.h
 *
 *  Created on: Sep 29, 2017
 *      Author: monish
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_
#include <stdint.h>

unsigned char my_itoa(int data, unsigned char * ptr, unsigned int base);
int my_atoi(unsigned char * ptr, unsigned char digits, unsigned int base);
char big_to_little32(unsigned int * data, unsigned int length);
char little_to_big32(unsigned int * data, unsigned int length);
/*extra functions defined in conversion*/
short c2i(char a);
int numvalue(short flag, unsigned char* ptr, unsigned char digits, unsigned int base);
char hexcon(int temp);
unsigned char i2a(short i, unsigned int data, unsigned char* ptr, unsigned int base);
void compli(unsigned char* ptr,short i);

#endif /* CONVERSION_H_ */
