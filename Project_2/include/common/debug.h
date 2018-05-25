/*
 * debug.c
This creates a print_memory() function that enables/disables debug printing with a compile time switch. -DVERBOSE is the flag that is used to enable the compile time switch.
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#ifndef DEBUG_H_
#define DEBUG_H

void print_memory(unsigned char * start, unsigned int length );

#endif /* DEBUG_H_ */
