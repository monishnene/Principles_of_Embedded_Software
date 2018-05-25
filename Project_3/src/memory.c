/**s
 * @file memory.c
 * @brief This file contains memory manipulation functions.
 * @author monish and sanika
 * @date Sep 29, 2017
 *
 * memory.c
 *@Long description:-
It has various memory functions like:-
1)my_memmove:- memmove takes 1 byte pointers source and destination and copies a length of bytes from source to destination location without any overalp. If flag =1 , if end of destination adresses intersects at start of source address then we start copying from the begining to handle overlap condition and if the start of destination location intersects at the end of source location then we start copying from the end to handle the overlap condition. If there is no overlap, then flag is zero. Destination is being returned.

2)my_memcpy:- It is used to copy a length of bytes from source to destination. THe copy function may or maynot corrupt the data. Destination is being returned.

3)my memset:- It is used to set all the locations of the source to a given value. It performs the same function as the set_all() function. Source is being returned.

4)my_memzero:- It is used to zero out all the memory.It performs the same function as the clear_all() function. Source is being returned.

5)my_reverse:- It is used for reversing the bytes in a memory. If the length of string is even ( tested by mod operator) the length is divided by 2 to carry out the iterations in the for loop (for reversing) upto half of the length. In case, the length is odd, it is first reduced by 1 and then divided by 2 and then reversing logic is performed. In the reverse for loop, the temp variable stores the source location for every iteration. THen, destination is stored in source and the temp which contains the source is stored back in destination. The function returns source.

6)reserve_words:- Malloc function that contatins the size of operator is used to reserve words in the source. This function returns source.

7)free_words:-  It is used to free dynamic memory location.
 */


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "memory.h"


/***********************************************************************
 * @brief my_memmove()
 * copies a length of bytes from source to destination location without any overalp.
 * @src source pointer
 * @dst destination pointer
 * @length length of data to be transferred
 * @return destination pointer
 ***********************************************************************/
uint8_t* my_memmove(uint8_t* src, uint8_t* dst, uint32_t length)
{ uint8_t flag=0,i;
  if( (src !=NULL) && (dst !=NULL) && (length >=0) )
  {

	for(i=0;i<length;i++)
	{
		if(dst==src+i)
		{
			flag=1;
		}
	}

	for(i=0;i<length;i++)
	{
		if(dst+length-1==src+i) /*For handling overlap condition for every iteration*/
		{
			flag=0;
		}
	}
	if(flag==0)
	{
		for(i=0;i<length;i++)
		{
			*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
		}
	}
	if(flag==1)
	{
		for(i=0;i<length;i++)
		{
			*(dst+length-1-i)=*(src+length-i-1); /*Copies from source to destination for every iteration*/
		}
	}

   return dst;
   }
   else if (src == NULL)
   {
   return src;
   }
   else
   {
   return dst;
   }
}

/***********************************************************************
 * @brief my_memcpy()
 * copies a length of bytes from source to destination location and it may or maynot corrupt the data.
 * @src source pointer
 * @dst destination pointer
 * @length length of data to be transferred
 * @return destination pointer
 ***********************************************************************/
uint8_t* my_memcpy(uint8_t* src, uint8_t* dst, uint32_t length)
{   uint8_t i;
    if( (src !=NULL) && (dst !=NULL) && (length >=0) )
    {

	for(i=0;i<length;i++)
	{
		*(dst+i)=*(src+i); /*Copies from source to destination for every iteration*/
	}
      }

	return dst;
}
/***********************************************************************
 * @brief my_memset()
 * sets a value to all the addresses given
 * @src source pointer
 * @value vallue to be set
 * @length length of data to be set
 * @return source pointer
 ***********************************************************************/
uint8_t* my_memset(uint8_t* src, uint32_t length, uint8_t value)
{
	uint8_t i;
        if( (src !=NULL) && (length >=0) )
  {
	for(i=0;i<length;i++)
	{
		*(src+i)=value; /*Sets the char value to the memory location for every iteration*/
	}

  }
	return src;
}

/***********************************************************************
 * @brief my_memzero()
 * initializes 0 to all the addresses given
 * @src source pointer
 * @length length of data to be set 0
 * @return source pointer
 ***********************************************************************/
uint8_t* my_memzero(uint8_t* src, uint32_t length)
{
	uint8_t i;
        if( (src !=NULL) && (length >=0) )
  {
	for(i=0;i<length;i++)
	{
		*(src+i)=0; /*Clears the source location for every iteration*/
	}
  }

	return src;
}

/***********************************************************************
 * @brief my_reverse()
 * reversing the bytes in a memory.
 * @src source pointer
 * @length length of data to be reversed
 * @return source pointer
 ***********************************************************************/
uint8_t* my_reverse(uint8_t* src, uint32_t length) /*Function for reversing bytes*/
{
	int8_t temp;
	size_t i,n;
        if( (src !=NULL) && (length >=0) )
      {
			if(length%2==0) /*If the length is even*/
			{
				n=length/2;
			}
			else
			{
				n=(length-1)/2; /*If the length is odd*/
			}
			for(i=0;i<n;i++) /*Loop for reversing the bytes*/
			{
				 temp = *(src+i);
				 *(src+i) = *(src+length-i-1);
				 *(src+length-i-1) = temp;
			}
       }

	return src;

}

/***********************************************************************
 * @brief reserve_words()
 * allocate memory dynamically in heap
 * @length length of data to be allocated dynamically
 * @return pointer to starting address of the allocated memory
 ***********************************************************************/
int32_t* reserve_words(uint32_t length)
{
  int32_t* src;
  src=malloc(((sizeof(int32_t))*length)); /*To reserve words = length in memory*/
  if (src != NULL)
  {
     return src;
  }
     return src;
}

/***********************************************************************
 * @brief free_words()
 * deallocate memory allocated o a pointer
 * @src pointer whose dynamic memory is to be deallocated
 ***********************************************************************/
void free_words(uint32_t* src) /*Function to free memory*/
{
 if(src != NULL)
  {
    /* Free the dynamic memory allocation by calling free()*/
    free(src);
  }

return;
}
/***************************************************************************
*****************************************************************************/
