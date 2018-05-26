/*
 * sizeof.c
 *
 *  Created on: Sep 22, 2017
 *      Author: monish
 */

#include<stdio.h>

print_arch_data()
{
 int i;
 printf("data type \t size in host machine \n");

 char a;
 i=sizeof(a);
 printf("char \t \t %d \n",i);

 int b;
 i=sizeof(b);
 printf("int \t \t %d \n",i);

 float c;
 i=sizeof(c);
 printf("float \t \t %d \n",i);

 double d;
 i=sizeof(d);
 printf("double \t \t %d \n",i);

 short e;
 i=sizeof(e);
 printf("short \t \t %d \n",i);

 long f;
 i=sizeof(f);
  printf("long \t \t %d \n",i);

 long int g;
 i=sizeof(g);
  printf("long int \t %d \n",i);

 long long h;
 i=sizeof(h);
  printf("long long \t %d \n",i);

  printf("int8_t \t \t 1 \n");
  printf("uint8_t \t 1 \n");
  printf("unit16_t \t 2 \n");
  printf("uint32_t \t 4 \n");

 char * n;
 i=sizeof(n);
 printf("char * \t \t %d \n",i);

 int * o;
 i=sizeof(o);
  printf("int * \t \t %d \n",i);

 float * p;
 i=sizeof(p);
  printf("float * \t %d \n",i);

 void * q;
 i=sizeof(q);
  printf("void * \t \t %d \n",i);

 void ** r;
 i=sizeof(r);
  printf("void ** \t %d \n",i);
  printf("int8_t * \t 1 \n",i);
  printf("int16_t* \t 2 \n",i);
  printf("int32_t * \t 4 \n",i);

  size_t v;
  i=sizeof(v);
   printf("size_t \t \t %d \n",i);

}

void main()
{
print_arch_data();
}
