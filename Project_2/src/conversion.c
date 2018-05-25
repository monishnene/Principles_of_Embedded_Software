/**
 * @file conversion.c
 * @brief This file contains data conversion functions from one type to another.
 * @author monish and sanika
 * @date Sep 29, 2017
 *
 * conversion.c
 *@Long description:-
 *
 * The conversion.c is used for making different conversions like:-
 *1) Integer to Ascii
 *2) Ascii to integer 
 *3) big to little endian and little to big endian
 *Integer to Ascii uses my_itoa function that handles cases for base 2 to base 16. For base2, if the data is negative, it converts int to char and then converts the negative number into a positive number.The function i2a is then called on which converts the integer to binary values and then reverse function is being called upon to reverse the bits for proper representation of the bits. The compli function is then called which takes the 2's complement of the number and the final answer we get are the binary values for int number. Incase, the number is positive the same logic is applied except that the 2's complement is not required to be taken. For base 8, the binary values for number has been found out and arranged in groups of 3 and for each group respective powers of 2 have been multiplied to get the final answer. For base 10, incrementing the pointer so that it points to the signed bit in case of negative number.The negative number is converted to positive and then converted into bits which are then represented properly. For positive values, the same logic has been used as above.For base 16, the binary values for number has been found out and arranged in groups of 4 and for each group respective power of 2 has been multiplied to get the final answer.
 *
 *Ascii to integer uses my_atoi function that handles cases for base 2 to base 16. If msb is 1, flag is set to 1 and then negative number is first converted into positive. A function call is used to find  the numvalue and then loop would be used for adjusting the value into integer. Similar logic is used for positive number. For base 8, if MSB is 4 or above flag is set to 1. Then, function call is used to find the numvalue and then loop is used for adjusting the value into integer. For base 10, if it has a negative sign, if flag =1, convert negative to positive.Then, the function call numvalue is used to find the numvalue.For, base 16, if MSB is 8 or above, then use the functioncall to find the numvalue. Loop for adjusting the value into integer is used. For all other cases the default condition is that the base is invalid.
 *
 *For  converting big to little endian, Remainder of data with 16 (for hex) is taken and is being multiplied by 16 for each iteration.After this operation, the MSB and LSB is being swapped  and the middle bytes remain the same. The little to big endian conversion uses the same logic the MSB gets stored first and then the middle bytes and LSB at the last.
 */

#include<stdlib.h>
#include <stdint.h>
#include<stdio.h>
#include"memory.h"

/***********************************************************************
 * @brief c2i()  
 * This funtion returns corresponding int value for a character  
 * @a character 
 * @return int value for the particular character
 ***********************************************************************/
uint16_t c2i(int8_t a) /* Function for converting char to Int*/
{
if(a=='0')
{return 0;}
else if(a=='1')
{return 1;}
else if(a=='2')
{return 2;}
else if(a=='3')
{return 3;}
else if(a=='4')
{return 4;}
else if(a=='5')
{return 5;}
else if(a=='6')
{return 6;}
else if(a=='7')
{return 7;}
else if(a=='8')
{return 8;}
else if(a=='9')
{return 9;}
else if(a=='A'||a=='a')
{return 10;}
else if(a=='B'||a=='b')
{return 11;}
else if(a=='C'||a=='c')
{return 12;}
else if(a=='D'||a=='d')
{return 13;}
else if(a=='E'||a=='e')
{return 14;}
else if(a=='F'||a=='f')
{return 15;}
return 0;
}

/***********************************************************************
 * @brief numvalue()  
 * This function finds numerical value of a string
 * @flag positive or negative
 * @ptr pointer to string start
 * @digits length of string
 * @base base of number
 * @return int value of the string
 ***********************************************************************/
size_t numvalue(uint16_t flag, uint8_t* ptr, uint8_t digits, uint32_t base)
{       
        
	uint16_t i,a;
        uint32_t number=0;
        if( ptr!= NULL)
        {
	for(i=0;i<digits-1;i++)       /*loop for obtaining number in case of ascii to int conversion*/
	{
		a=c2i(*(ptr+i));	
		number = base*number + a;
	}
	if(flag==1)                /*If MSB is 1 the number is negative*/
	{
		number *= -1;     /*For converting negative number to positive*/
	}

        }
	return number;
}

/***********************************************************************
 * @brief i2c()  
 * This function returns character corresponding to int
 * @temp number to be converted to character
 * @return character for corresponding int
 ***********************************************************************/
int8_t i2c(int temp)           /*Function that includes switch statement for hex definition*/
{
	switch(temp)            /*switch case for defining hex characters above 9 i.e. 'A' to 'F'*/

	{		case 1:
			return '1';
			
			case 0:
			return '0';
			
			case 2:
			return '2';
			
			case 3:
			return '3';
			
			case 4:
			return '4';

			case 5:
			return '5';

			case 6:
			return '6';

			case 7:
			return '7';

			case 8:
			return '8';

			case 9:
			return '9';

			case 10:
			return 'A';

			case 11:

			return 'B';

			case 12:
			return 'C';

			case 13:
			return 'D';

			case 14:
			return 'E';

			case 15:
			return 'F';
			 /*To convert int to char*/
	}
return '0';
}

/***********************************************************************
 * @brief i2a()  
 * This function coverts int to string 
 * @i initial offset
 * @ptr pointer to string start
 * @data number to be converted
 * @base base of number
 * @return string length
 ***********************************************************************/
uint8_t i2a(uint16_t i, uint32_t data, uint8_t* ptr, uint32_t base)
{       
        if( ptr != NULL )
        {
	uint16_t temp;
	while(data>=base) /*Loop for converting integer to binary values*/
	{
	temp=data%base;  
	*(ptr+i)=i2c(temp); /*To convert int to char*/
	data=data/base;
	i++;
	}
	*(ptr+i)=i2c(data);
	i++;
	*(ptr+i)='\0';  /*Convert uptill the null char has reached*/
	i++;
        }
	return i;
}

/***********************************************************************
 * @brief compli()  
 * This function finds 2's compliment of a string and saves it
 * @ptr pointer to string start
 * @i length of string
 ***********************************************************************/
void compli(uint8_t* ptr,uint16_t i) /*Function to find 2's complement for negative numbers*/
{	uint16_t j,c1=1,c2,temp;
	if ( ptr!= NULL)
        {
	for(j=0;j<i;j++)
	{
	temp=*(ptr+j)^1; /*exoring logic 1 with each location and storing it in a temp variable everytime the loop executes*/
	*(ptr+j)=temp;	 /*storing the vtemp value back in the respective location everytime the loop executes*/
	}

	for(j=0;j<i;j++)
	{	
		c2=*(ptr+i-2-j)&c1; //Carry 2 is the internal carry generated that contains the 'And' operation of the previous carry and the second last locationin a data
		temp=*(ptr+i-2-j)^c1; //carrying out exor for the initial carry and the bit at the second last location in a data and storing it in a temp variable
		*(ptr+i-2-j)=temp;   /*Storing the result back to the second last bit in the data*/
		c1=c2; /*storing c2 in c1 so that c2 becomes the previous carry for further operation*/
	}
        }
	return;
}

/***********************************************************************
 * @brief my_itoa()  
 * This function converts integer to string
 * @ptr pointer to string start
 * @data number to be converted
 * @base base of number
 * @return length of string with \0
 ***********************************************************************/
uint8_t my_itoa(int32_t data, uint8_t* ptr, uint32_t base) /*Function for converting integer to ascii*/
{	
	uint16_t i=0,j,k,l=0,a=0,b=0,c=0,d=0;
	int8_t temp; 
        if ( ptr != NULL) 
        {           
	switch (base)                /*Switch statement for binary,octal,decimal,hex*/
	{
		case 2:                     
			if (data < 0) /*For negative integers*/
			{
			    	*ptr=1+'0';  /*converting int to char*/
			    	ptr++;       /*Incrementing the pointer so that it points at the negative sign of the negative integer*/
			    	data *= -1;   /*converting negative to positive integer*/
			    	i=i2a(i,data,ptr,base); /*Function call for converting integer to binary values*/	
				my_reverse(ptr,i-1);    /*Reversing the bits for proper representation*/		    	
				compli(ptr,i);         /*Function call to find 2's complement */
		         	i++;
				return i;
			}

			*(ptr)=0;                      /*For positive integers*/
			ptr++;
			i= i2a(i,data,ptr,base);      /*Function call for converting integer to binary values*/
			ptr=my_reverse(ptr,i-1);          /*Reversing the bits for proper representation*/
			i++;                          
			return i;

		case 8:
			i=my_itoa(data,ptr,2);        /*using recursive function*/												
			j=(i-1)%3;		
			temp=*(ptr); 
			if(j>0)
			{	
				for(k=2;k<i+1;k++)  /*Loop for adjusting groups of 4 bits*/
				{	
					*(ptr+i-k+3-j)=*(ptr+i-k);
				}
				for(k=0;k<3-j;k++) /*Loop for setting sign bit*/
				{
					*(ptr+k)=temp;
				}
			}
			for(k=0;k<i+j-2;k+=3)      //Loop for multiplying the lsb,middle and msb groups with respective powers of 2 to get the char output(octal)
			{	
				a=c2i(*(ptr+k));
				b=c2i(*(ptr+k+1));
				c=c2i(*(ptr+k+2));			
				temp=a*4+b*2+c;
				*(ptr+l)=i2c(temp);
				l++;
			}
			if(*(ptr)=='0')
			{
				for(i=0;i<l;i++)
				{	
					*(ptr)=*(ptr+1);
				}		
			l--;
			}
			*(ptr+l)='\0';
			l++;
			return l;

		case 10:
			if (data < 0)       /*for negative integers*/
			{
				*ptr='-';
				ptr++;      /*Incrementing the pointer so that it points at the negative sign of the negative integer*/
				data *= -1;  /*converting negative to positive integer*/
				i=i2a(i,data,ptr,base); /*Function call for converting integer to binary values*/
				my_reverse(ptr,i-1);    /*Reversing the bits for proper representation*/
				i++;                 
				return i;
			}                               /*For positive integers*/
			i= i2a(i,data,ptr,base);       /*Function call for converting integer to binary values*/ 
			my_reverse(ptr,i-1);           /*Reversing the bits for proper representation*/
			return i;

		case 16:
			i=my_itoa(data,ptr,2);        /*using recursive function*/												
			j=(i-1)%4;		
			temp=*(ptr); 
			if(j>0)
			{	
				for(k=2;k<i+1;k++)  /*Loop for adjusting groups of 4 bits*/
				{	
					*(ptr+i-k+4-j)=*(ptr+i-k);
				}
				for(k=0;k<4-j;k++) /*Loop for setting sign bit*/
				{
					*(ptr+k)=temp;
				}
			}
			for(k=0;k<i+j-1;k+=4)       //Loop for multiplying the lsb,middle and msb groups with respective powers of 2 to get the char output                                                  
			{	a=c2i(*(ptr+k));
				b=c2i(*(ptr+k+1));
				c=c2i(*(ptr+k+2));
				d=c2i(*(ptr+k+3));			
				temp=a*8+b*4+c*2+d;
				*(ptr+l)=i2c(temp);
				l++;
			}
			if(*(ptr)=='0')
			{
				for(i=0;i<=l;i++)
				{
					*(ptr)=*(ptr+1);
				}	
			l--;
			}	
			*(ptr+l)='\0';
			l++; 
			return l;
                


		default:
			return 0;	 /* The base is invalid*/
	}
	return 0;
        }
	return 0;
}

/***********************************************************************
 * @brief my_atoi()  
 * This function converts string to integer
 * @ptr pointer to string start
 * @digits length of string
 * @base base of number
 * @return int value of the string
 ***********************************************************************/
int32_t my_atoi(uint8_t* ptr, uint8_t digits, uint32_t base) /*Function for converting ascii to int values*/
{	uint16_t i,flag=0;
	size_t number=0,power=1;
        if( ptr != NULL)
        {
	switch(base)
	{
		case 2:
			if ((*(ptr)=='1'))  /*If MSB is 1*/
			{
				flag=1;		
			}
			number=numvalue(0,ptr,digits,2); /*Function call to find the numvalue*/
			if(flag==1)
			{	for(i=0;i<digits;i++) /*Loop for adjusting the value into integer*/
				{
				power *= 2;   
				}	
				number=-power+number;
			}
			return number;

		case 8:	if ((*(ptr)=='7')||(*(ptr)=='4')||(*(ptr)=='5')||(*(ptr)=='6')) /*if MSB is 7,6,5 or 4*/
			{
				flag=1;			
			}
			number=numvalue(0,ptr,digits,8); /*function call to find the num value*/
			if(flag==1)
			{	for(i=0;i<digits;i++) /*Loop for adjusting the value into integer*/
				{
				power *= 8;
				}	
				number=-power+number;
			}
			return number;

		case 10:
			if (*(ptr)=='-') /*If it is a signed number*/
			{
				ptr++;
				digits--;
				flag=1; /*set flag*/
			}
			number=numvalue(flag,ptr,digits,base);	/*function call to find the num value*/
			return number;

		case 16:if ((*(ptr)=='F')||(*(ptr)=='E')||(*(ptr)=='D')||(*(ptr)=='C')||(*(ptr)=='B')||(*(ptr)=='A')||(*(ptr)=='a')||(*(ptr)=='b')||(*(ptr)=='f')||(*(ptr)=='e')||(*(ptr)=='d')||(*(ptr)=='c')||(*(ptr)=='9')||(*(ptr)=='8')) /*if msb is 8 or above*/
			{
				flag=1;			
			}
			number=numvalue(0,ptr,digits,16); /*function call to find the num value*/
			if(flag==1)
			{	for(i=1;i<digits;i++) /*Loop for adjusting the value into integer*/

				{
				power *= 16;
				}	
				number=-power+number;
			}
			return number;

		default:
			return 0;	 /* The base is invalid*/
	}
	return 0;
        }
	return 0;
}

/***********************************************************************
 * @brief big_to_little()  
 * This function converts big endian data to little endian
 * @data pointer to data array beginning
 * @length length of array
 * @return success or fail
 ***********************************************************************/
uint8_t  big_to_little32(uint32_t* data, uint32_t length) /*Loop for converting big to little endian*/
{
	uint16_t i,j;
        if ( data != NULL)
        {
	for(i=0;i<length;i++) 
	{
		uint32_t temp=0;
		for(j=0;j<4;j++)
		{
			temp = 256*temp + (*(data+i)%256); /*Taking remainder and multiplying it by 256 for each iteration*/ 				 
			*(data+i)= *(data+i)/16;
		}
			*(data+i)=temp;
	}
        }
	return '1';
}

/***********************************************************************
 * @brief little_to_big()  
 * This function converts little endian data to big endian
 * @data pointer to data array beginning
 * @length length of array
 * @return success or fail
 ***********************************************************************/
uint8_t little_to_big32(uint32_t * data, uint32_t length) /*Loop for converting little to big endian*/
{
	uint16_t i,j;
        if ( data != NULL)
        {
	for(i=0;i<length;i++)
	{	
		uint32_t temp=0;
		for(j=0;j<4;j++)
		{
			temp = 256*temp + (*(data+i)%256);  /*Taking remainder and multiplying it by 256 for each iteration*/ 					 
			*(data+i)=*(data+i)/16;
		}
			*(data+i)=temp;
	}
        }
	return '1';
}


