/*
 * conversion.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#include<stdio.h>
#include <memory.h>

short c2i(char a) /* Function for defining Int and Hex characters*/
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
else
return ;
}

int numvalue(short flag, unsigned char* ptr, unsigned char digits, unsigned int base)
{
	short i,a;
        unsigned int number=0;
	for(i=0;i<digits;i++)       /*loop for obtaining number in case of ascii to int conversion*/
	{
		a=c2i(*(ptr+i));	
		number = base*number + a;
	}
	if(flag==1)                /*If MSB is 1 the number is negative*/
	{
		number *= -1;     /*For converting negative number to positive*/
	}
	return number;
}

char hexcon(int temp)           /*Function that includes switch statement for hex definition*/
{
	switch(temp)            /*switch case for defining hex characters above 9 i.e. 'A' to 'F'*/

	{

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

			default:
			return temp +'0'; /*To convert int to char*/
	}
}

unsigned char i2a(short i, unsigned int data, unsigned char* ptr, unsigned int base)
{
	short temp;
	while(data>=base) /*Loop for converting integer to binary values*/
	{
	temp=data%base;  
	*(ptr+i)=temp +'0'; /*To convert int to char*/
	data=data/base;
	i++;
	}
	*(ptr+i)=data +'0';
	i++;
	*(ptr+i)='\0';  /*Convert uptill the null char has reached*/
	i++;
	return i;
}

void compli(unsigned char* ptr,short i) /*Function to find 2's complement for negative numbers*/
{	short j,c1=1,c2,temp;
	
	for(j=0;j<i;j++)
	{
	temp=*(ptr+j)^1; /*exoring logic 1 with each location and storing it in a temp variable everytime the loop executes*/
	*(ptr+j)=temp;	 /*storing the vtemp value back in the respective location everytime the loop executes*/
	}

	for(j=0;j<i;j++)
	{	
		c2=*(ptr+i-2-j)&c1; //Carry 2 is the internal carry generated that contains the 'And' operation of the previous carry and the second last                                       //location in a data
		temp=*(ptr+i-2-j)^c1; //carrying out exor for the initial carry and the bit at the second last location in a data and storing it in a temp                                       //variable
		*(ptr+i-2-j)=temp;   /*Storing the result back to the second last bit in the data*/
		c1=c2;               /*storing c2 in c1 so that c2 becomes the previous carry for further operation*/
	}
	return;
}

unsigned char my_itoa(int data, unsigned char* ptr, unsigned int base) /*Function for converting integer to ascii*/
{	
	short i=0,j,k,l=0,a,b,c,d;
	char temp;            
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
			my_reverse(ptr,i-1);          /*Reversing the bits for proper representation*/
			i++;                          
			return i;

		case 8:
			i=my_itoa(data,ptr,2);        /*using recursive function*/
			k=i-1;
			j=(k)%3;		
			temp = *(ptr);
			if(j>0)                        /*Loop for making groups of 3 bits*/
			{
				for(k=k-1;k>=0;k--)  
				{
					*(ptr+k+3-j)=*(ptr+k);
				}
				for(k=0;k<3-j;k++)
				{
					*(ptr+k)=temp;
				}
			}
			for(k=0;k<i+j-2;k+=3)      //Loop for multiplying the lsb,middle and msb groups with respective powers of 2 to get the char output                                                      //(octal)
			{	
				a=c2i(*(ptr+k));
				b=c2i(*(ptr+k+1));
				c=c2i(*(ptr+k+2));			
				temp=a*4+b*2+c;
				*(ptr+l)=temp+'0';
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
			k=i-1;
			j=(k)%4;		
			temp=*(ptr);
			if(j>0)
			{
				for(k=k-1;k>=0;k--)  /*Loop for making groups of 4 bits*/
				{
					*(ptr+k+4-j)=*(ptr+k);
				}
				for(k=0;k<4-j;k++)
				{
					*(ptr+k)=temp;
				}
			}
			for(k=0;k<i+j-1;k+=4)       //Loop for multiplying the lsb,middle and msb groups with respective powers of 2 to get the char output                                                      //(hex)
			{	a=c2i(*(ptr+k));
				b=c2i(*(ptr+k+1));
				c=c2i(*(ptr+k+2));
				d=c2i(*(ptr+k+3));			
				temp=a*8+b*4+c*2+d;
				*(ptr+l)=hexcon(temp);
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
			printf("Not a valid base");   /*Not a valid base*/
			return 0;
	}
}

int my_atoi(unsigned char* ptr, unsigned char digits, unsigned int base) /*Function for converting ascii to int values*/
{	short i,j,k,flag=0;
	int number=0,temp,power=1;
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
			{	for(i=0;i<digits;i++) /*Loop for adjusting the value into integer*/

				{
				power *= 16;
				}	
				number=-power+number;
			}
			return number;

		default:
			printf("Not a valid base"); /* The base is invalid*/
			return 0;
	}
}

unsigned char  big_to_little32(unsigned int* data, unsigned int length) /*Loop for converting big to little endian*/
{
	short i,j;
	for(i=0;i<length;i++) 
	{
		unsigned int temp=0;
		for(j=0;j<4;j++)
		{
			temp = 16*temp + (*(data+i)%16); /*Taking remainder and multiplying it by 16 for each iteration*/ 				 
			*(data+i)=*(data+i)/16;
		}
			*(data+i)=temp;
	}
	return '1';
}

unsigned char little_to_big32(unsigned int * data, unsigned int length) /*Loop for converting little to big endian*/
{
	short i,j;
	for(i=0;i<length;i++)
	{	
		unsigned int temp=0;
		for(j=0;j<4;j++)
		{
			temp = 16*temp + (*(data+i)%16);  /*Taking remainder and multiplying it by 16 for each iteration*/ 					 
			*(data+i)=*(data+i)/16;
		}
			*(data+i)=temp;
	}
	return '1';
}


