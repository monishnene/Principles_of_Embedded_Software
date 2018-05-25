/**
 * @file debug.c
 * @brief This creates a print_memory() function that enables/disables debug printing with a compile time switch. -DVERBOSE is the flag that is used to enable the compile time switch.
 * @author monish and sanika
 * @date Sep 29, 2017
 *
 */

#include<stdint.h>
#include<stdio.h>


/***********************************************************************
 * @brief print_memory()  
 * This function is used by project1.c to print data
 * @start pointer to start address
 * @length length of memory to be printed
 ***********************************************************************/
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


