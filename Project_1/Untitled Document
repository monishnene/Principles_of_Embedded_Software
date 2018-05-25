/*
 * conversion.c
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */
#include<stdio.h>
#include <memory.h>

short c2i(char a)
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
	for(i=0;i<digits;i++)
	{
		a=c2i(*(ptr+i));	
		number = base*number + a;
	}
	if(flag==1)
	{
		number *= -1;
	}
	return number;
}

char hexcon(int temp)
{
	switch(temp)
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
			return temp +'0';
	}
}

unsigned char i2a(short i, unsigned int data, unsigned char* ptr, unsigned int base)
{
	short temp;
	while(data>=base)
	{
	temp=data%base;
	*(ptr+i)=temp +'0';
	data=data/base;
	i++;
	}
	*(ptr+i)=data +'0';
	i++;
	*(ptr+i)='\0';
	i++;
	return i;
}

void compli(unsigned char* ptr,short i)
{	short j,c1=1,c2,temp;
	
	for(j=0;j<i;j++)
	{
	temp=*(ptr+j)^1;
	*(ptr+j)=temp;	
	}

	for(j=0;j<i;j++)
	{	
		c2=*(ptr+i-2-j)&c1;
		temp=*(ptr+i-2-j)^c1;
		*(ptr+i-2-j)=temp;
		c1=c2;
	}
	return;
}

unsigned char my_itoa(int data, unsigned char* ptr, unsigned int base)
{	
	short i=0,j,k,l=0,a,b,c,d;
	char temp;
	switch (base)
	{
		case 2:
			if (data < 0)
			{
			    	*ptr=1+'0';
			    	ptr++;
			    	data *= -1;
			    	i=i2a(i,data,ptr,base);
				my_reverse(ptr,i-1);
			    	compli(ptr,i);
				i++;	
				return i;
			}
			*(ptr)=0;
			ptr++;
			i= i2a(i,data,ptr,base);
			my_reverse(ptr,i-1);
			i++;
			return i;

		case 8:
			i=my_itoa(data,ptr,2);
			k=i-1;
			j=(k)%3;		
			temp = *(ptr);
			if(j>0)
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
			for(k=0;k<i+j-2;k+=3)
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
			if (data < 0)
			{
				*ptr='-';
				ptr++;
				data *= -1;
				i=i2a(i,data,ptr,base);
				my_reverse(ptr,i-1);
				i++;
				return i;
			}
			i= i2a(i,data,ptr,base);
			my_reverse(ptr,i-1);
			return i;

		case 16:
			i=my_itoa(data,ptr,2);
			k=i-1;
			j=(k)%4;		
			temp=*(ptr);
			if(j>0)
			{
				for(k=k-1;k>=0;k--)
				{
					*(ptr+k+4-j)=*(ptr+k);
				}
				for(k=0;k<4-j;k++)
				{
					*(ptr+k)=temp;
				}
			}
			for(k=0;k<i+j-1;k+=4)
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
			printf("Not a valid base");
			return 0;
	}
}

int my_atoi(unsigned char* ptr, unsigned char digits, unsigned int base)
{	short i,j,k,flag=0;
	int number=0,temp,power=1;
	switch(base)
	{
		case 2:
			if ((*(ptr)=='1'))
			{
				flag=1;			
			}
			number=numvalue(0,ptr,digits,2);
			if(flag==1)
			{	for(i=0;i<digits;i++)
				{
				power *= 2;
				}	
				number=-power+number;
			}
			return number;

		case 8:	if ((*(ptr)=='7')||(*(ptr)=='4')||(*(ptr)=='5')||(*(ptr)=='6'))
			{
				flag=1;			
			}
			number=numvalue(0,ptr,digits,8);
			if(flag==1)
			{	for(i=0;i<digits;i++)
				{
				power *= 8;
				}	
				number=-power+number;
			}
			return number;

		case 10:
			if (*(ptr)=='-')
			{
				ptr++;
				digits--;
				flag=1;
			}
			number=numvalue(flag,ptr,digits,base);	
			return number;

		case 16:if ((*(ptr)=='F')||(*(ptr)=='E')||(*(ptr)=='D')||(*(ptr)=='C')||(*(ptr)=='B')||(*(ptr)=='A')||(*(ptr)=='a')||(*(ptr)=='b')||(*(ptr)=='f')||(*(ptr)=='e')||(*(ptr)=='d')||(*(ptr)=='c')||(*(ptr)=='9')||(*(ptr)=='8'))
			{
				flag=1;			
			}
			number=numvalue(0,ptr,digits,16);
			if(flag==1)
			{	for(i=0;i<digits;i++)

				{
				power *= 16;
				}	
				number=-power+number;
			}
			return number;

		default:
			printf("Not a valid base");
			return 0;
	}
}

unsigned char  big_to_little32(unsigned int* data, unsigned int length)
{
	short i,j;
	for(i=0;i<length;i++)
	{
		unsigned int temp=0;
		for(j=0;j<4;j++)
		{
			temp = 16*temp + (*(data+i)%16);  				 
			*(data+i)=*(data+i)/16;
		}
			*(data+i)=temp;
	}
	return '1';
}

unsigned char little_to_big32(unsigned int * data, unsigned int length)
{
	short i,j;
	for(i=0;i<length;i++)
	{	
		unsigned int temp=0;
		for(j=0;j<4;j++)
		{
			temp = 16*temp + (*(data+i)%16);  				 
			*(data+i)=*(data+i)/16;
		}
			*(data+i)=temp;
	}
	return '1';
}


void main()
{ 
unsigned short i;
int n;
unsigned int arr[50];
unsigned int* data = arr;

*(data+0)=46155;
*(data+1)=17185;
*(data+2)=4660;
*(data+3)=65535;

n=big_to_little32(data,4);
for(i=0;i<4;i++)
{
printf("The value is %d\n",*(data+i));
printf("\n");
}
}
//for(i=0;i<n;i++)
//{
//printf("%c",*(data+i));
//}
/*unsigned char* ptr = arr;
n=my_itoa(5678,ptr,16);
for(i=0;i<n;i++)
{
printf("%c",*(ptr+i));
}*/
/* *(ptr+0)='f';
*(ptr+1)='1';
*(ptr+2)='1';
*(ptr+3)='1';
printf("\n");
n=my_atoi(ptr,4,10);
printf("The value is %d \n",n); */
//printf("\n");
//}
