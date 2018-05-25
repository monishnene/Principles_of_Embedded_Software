/*
 * Copyright 2008 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Use the unit test allocators */
#define UNIT_TESTING 1

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <stdio.h>
#include "circbuf.h"
#include "conversion.h"
#include "memory.h"
#include <stdlib.h>

uint8_t* src;
 uint8_t* dst;
uint8_t* store; 
uint8_t* data;
uint8_t length, position, value;
CB_t *cbptr;
static int setup(void **state) {
    int *answer = malloc(sizeof(int));

    assert_non_null(answer);

    *answer = 1; 	

    *state = answer;

    return 0;
}

static int teardown(void **state) {
    free(*state);

    return 0;
}

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state;
}

static void memmove_null_pointer_test(void **state) 
{
src = NULL;
dst = NULL;
length=3;
src = my_memmove(src,dst,length);
if(src == NULL)
{
  printf("Null Pointer Detected \n");
  assert_int_equal(1, 1);
}
else
{
  printf("No Null pointer \n");
  assert_int_equal(1, 1);
}
}

static void memmove_no_overlap(void **state) 
{ uint8_t i;
uint8_t flag = 0;
src = malloc(12);
dst = src + 15 ;
length = 12;
dst= my_memmove(src,dst,length);
for(i=0;i<length-1;i++)
{
 if(*(src+i) != *(dst+i))
 {flag = 1;}
}
if(flag == 0 )
{
  printf("Data moved without error \n");
  assert_int_equal(flag, 0);
}
else 
{
  printf("Data not moved properly \n");
  assert_int_equal(flag, 1);
}
}

static void memmove_SRC_in_DST(void **state) 
{
uint8_t i;
uint8_t flag = 0;
dst = malloc(12);
src = dst + 5;
length = 12;
dst= my_memmove(src,dst,length);
for(i=0; i<length; i++)
{ 
  if(*(dst+i) == *(src+i))
	{flag=1;}
}
if(flag == 0 )
{
  printf("Data moved without error overlap handled \n");
  assert_int_equal(flag, 0);
}
else 
{
  printf("Data not moved properly \n");
  assert_int_equal(flag, 1);
}
}

static void memmove_DST_in_SRC(void **state) 
{
uint8_t flag = 0;
uint8_t i;
src = malloc(12);
dst = src + 5;
length = 12;
dst= my_memmove(src,dst,length);
for(i=0; i<length; i++)
{ 
  if(*(dst+i) == *(src+i))
	{flag=1;}
}
if(flag == 0 )
{
  printf("Data moved without error overlap handled \n");
  assert_int_equal(flag, 0);
}
else 
{
  printf("Data not moved properly \n");
  assert_int_equal(flag, 1);
}
}

static void memset_null_pointer_test(void **state) {
src = NULL;
dst = NULL;
length = 3;
src = my_memset(src,length,value);
if(src == NULL)
{
printf("Null pointer Detected \n");
assert_int_equal(1, 1);
}
else
{
printf("No Null pointer \n");
assert_int_equal(1, 1);
}
}

static void memset_check_region_set(void **state) 
{
uint8_t i,flag=0;
value = 0x80;
length = 4;
src = malloc(length);
src= my_memset(src,length,value);
for(i=0;i<length;i++)
{
  if(*(src+i) != value)
	{flag=1;}
}
if(flag==0)
{
 printf("The value is set to the memory location \n");
 assert_int_equal(flag, 0);
}
else
{
 printf("The value is not set to the memory location \n");
 assert_int_equal(flag, 1);
}
}

static void memzero_null_pointer_test(void **state) {
src = NULL;
dst = NULL;
length = 3;
src = my_memzero(src,length);
if(src == NULL)
{
printf("Null pointer Detected \n");
assert_int_equal(1, 1);
}
else
{
printf("No Null pointer \n");
assert_int_equal(1, 1);
}
}

static void memzero_check_region_zero(void **state) 
{
uint8_t i,flag=0;
length = 4;
src = malloc(length);
src= my_memzero(src,length);
for(i=0;i<length;i++)
{
  if(*(src+i) != 0)
  {flag=1;}
}
if(flag==0)
{
 printf("The memory locations are 0 \n");
 assert_int_equal(flag, 0);
}
else
{
 printf("The memory locations are not 0 \n");
 assert_int_equal(flag, 1);
}
}

static void reverse_null_pointer_test(void **state) {
src = NULL;
dst = NULL;
length = 3;
src = my_reverse(src,length); 
if(src == NULL)
{
printf("Null pointer Detected \n");
assert_int_equal(1, 1);
}
else
{
printf("No Null pointer \n");
assert_int_equal(1, 1);
}
}

static void reverse_check_odd(void **state) 
{ 
length = 3;
uint8_t i,arr[3],flag=0;
src = &arr;
for(i=0;i<3;i++)
{
 *(src+i) = i;
}
src = my_reverse(src,length);
for(i=0;i<length;i++)
{
  if(*(src+length-i) != i)
  {flag=1;}
}
if(flag==0)
{ 
 printf("The memory is reversed \n");
 assert_int_equal(flag, 0);
}
else
{
 printf("The memory is not reversed \n");
 assert_int_equal(flag, 1);
}
}

static void reverse_check_even(void **state) 
{
length = 4;
uint8_t i,arr[3],flag=0;
src = &arr;
for(i=0;i<3;i++)
{
 *(src+i) = i;
}
src = my_reverse(src,length);
for(i=0;i<length;i++)
{
  if(*(src+length-i) != i)
  {flag=1;}
}
if(flag==0)
{
 printf("The memory is reversed \n");
 assert_int_equal(flag, 0);
}
else
{
 printf("The memory is not reversed \n");
 assert_int_equal(flag, 1);
}
}

static void reverse_check_all_chars(void **state) 
{
length = 3;
uint8_t i,flag=0,arr[3];
src = arr;
*(src)= '\n';
*(src+1) = '\0';
*(src+2) = '\t';
src = my_reverse(src,length);
if( *(src)!='\t')
{flag=1;}
if( *(src+1)!='\0')
{flag=1;}
if( *(src+2)!='\n')
{flag=1;}
if(flag==0)
{
 printf("The memory is reversed \n");
 assert_int_equal(flag, 0);
}
else
{
 printf("The memory is not reversed \n");
 assert_int_equal(flag, 1);
}
}

static void big_to_litte_null_pointer_test(void **state) 
{
data = NULL;
length = 4;
data = big_to_little32(data,length);
if(data == NULL)
{
printf("Null pointer Detected \n");
assert_int_equal(1, 1);
}
else 
{
printf("No Null pointer \n");
assert_int_equal(1, 1);
}
}

static void big_to_litte_conversion_test(void **state) 
{uint8_t flag;
uint8_t n;
uint32_t* data;
uint32_t arr[4];
data = arr;
*(data) = 0;
*(data+1)=  2;
*(data+2) = 8;
*(data+3) = 7;
n= big_to_little32(data,4);
if( *(src)!=0x00000000)
{flag=1;}
if( *(src+1)!=0x02000000)
{flag=1;}
if( *(src+2)!=0x08000000)
{flag=1;}
if( *(src+3)!=0x07000000)
{flag=1;}
if(flag==0)
{
 printf("Big endian to little endian done \n");
 assert_int_equal(flag, 0);
}
else
{
 printf("Big endian to little endian not done \n");
 assert_int_equal(flag, 1);
}
}

static void little_to_big_null_pointer_test(void **state) {
data = NULL;
length = 4;
data = big_to_little32(data,length);
if(data == NULL)
{
printf("Null pointer Detected \n");
assert_int_equal(1, 1);
}
else 
{
printf("No Null pointer \n");
assert_int_equal(1, 1);
}
}

static void little_to_big_conversion_test(void **state)
{uint8_t flag;
uint8_t n;
uint32_t* data;
uint32_t arr[4];
data = arr;
*(data) = 0;
*(data+1)=  2;
*(data+2) = 8;
*(data+3) = 7;
n= big_to_little32(data,4);
if( *(src)!=0x00000000)
{flag=1;}
if( *(src+1)!=0x02000000)
{flag=1;}
if( *(src+2)!=0x08000000)
{flag=1;}
if( *(src+3)!=0x07000000)
{flag=1;}
if(flag==0)
{
 printf("Little endian to big endian done \n");
 assert_int_equal(flag, 0);
}
else
{
 printf("Little endian to big endian not done \n");
 assert_int_equal(flag, 1);
}
}
static void create_cicular_buffer(void **state) 
{
CB_t circular_buffer;
CB_t* cbptr = &circular_buffer;
CB_init(cbptr,length);
}


static void circular_buffer_null_pointer_test(void **state) 
{

value == cbptr;
value= CB_peek(cbptr,position,store);
if(value == NULL)
{
printf(" Null pointer detected \n");
assert_int_equal(1, 1);
}
else
{
printf(" No Null pointer \n");
assert_int_equal(1, 1);
}
}

static void circular_buffer_initialized_test(void **state) 
{
value = CB_peek(cbptr,12,store);
if(value == Success)
{
printf(" Circular buffer initialized");
assert_int_equal(value, 3);
}
else
{
printf("Circular buffer not initialized");
assert_int_equal(1, 1);
}

static void circular_buffer_add_remove_test(void **state) 
{

value = CB_buffer_add_item(cbptr,src);
if(value == Success)
{
value = CB_buffer_remove_item(cbptr,dst);
if( *dst == *src)
{
printf(" Add and Remove successful");
assert_int_equal(value, 3);
}
}
else
{
printf(" Add and Remove failed");
assert_int_equal(1, 1);
}
}

static void circular_buffer_full_test(void **state) 
{
uint8_t i;
for(i=0;i<10;i++)
{
value = CB_buffer_add_item(cbptr,dst);
}
value = CB_is_full(cbptr);

if(value == Buffer_Full)
{
printf("Circular buffer full");
assert_int_equal(value, 0);
}
else
{
printf(" Circular buffer not full");
assert_int_equal(1, 1);
}

static void circular_buffer_empty_test(void **state) 
{
uint8_t i;
for(i=0;i<10;i++)
{
value = CB_buffer_remove_item(cbptr,dst);
}
value = CB_is_empty(cbptr);
if(value == Buffer_Empty)
{
printf("Circular buffer Empty");
assert_int_equal(value, 1);
}
else
{
printf(" Circular buffer not Empty");
assert_int_equal(value, 0);
}


static void circular_buffer_wrap_add_test(void **state) 
{
 uint8_t i;
 for(i=0;i<6;i++)
{
 value= CB_buffer_add_item(cbptr,dst);
}
 for(i=0;i<5;i++)
{
 value= CB_buffer_remove_item(cbptr,dst);
}
 for(i=0;i<7;i++)
{
  value= CB_buffer_add_item(cbptr,dst);
}
value = CB_is_full(cbptr);
if(value == Buffer_Full)
{
printf("wrap add successful");
assert_int_equal(value, 0);
}
else
{
printf("wrap add not successful");
assert_int_equal(value,1);
}
}

static void circular_buffer_wrap_remove_test(void **state) {
uint8_t i;
for(i=0;i<6;i++)
{
value = CB_buffer_remove_item(cbptr,store);
}
for(i=0;i<5;i++)
{
value = CB_buffer_add_item(cbptr,dst);
}
for(i=0;i<7;i++)
{
value= CB_buffer_remove_item(cbptr,store);
}
value = CB_is_empty(cbptr);
if(value== Buffer_Empty)
{
printf("wrap remove successful");
assert_int_equal(value,1);
}
else
{
printf("wrap remove not successful");
assert_int_equal(value,0);
}
}
static void circular_buffer_overfill_test(void **state) {
uint8_t i;
value = CB_is_full(cbptr);
for(i=0;i<5;i++)
{
value = CB_buffer_add_item(cbptr,dst);
}
if(value == Success)
{
printf(" Circular buffer overfills");
assert_int_equal(0, 0);
}
else
{
printf("No overfill");
assert_int_equal(1, 1);
}

static void circular_buffer_overempty_test (void **state) {
uint8_t i;
value = CB_is_empty(cbptr);
for(i=0;i<5;i++)
{
value = CB_buffer_remove_item(cbptr,store);
}
if(value == Success)
{
printf(" Circular buffer over empty");
assert_int_equal(1, 1);
}
else
{
printf(" Circular buffer not over empty");
assert_int_equal(0, 0);
}
/* A test case that does check if an int is equal. */
static void int_test_success(void **state) {

    int *answer = *state;
    
    assert_int_equal(1, 1);
}

int main(void) {
    const struct CMUnitTest tests[] = 
    {
	cmocka_unit_test(null_test_success),
        cmocka_unit_test(int_test_success),
	cmocka_unit_test(memmove_null_pointer_test),
	cmocka_unit_test(memmove_no_overlap),
	cmocka_unit_test(memmove_SRC_in_DST),
	cmocka_unit_test(memmove_DST_in_SRC),
	cmocka_unit_test(memset_null_pointer_test),
	cmocka_unit_test(memset_check_region_set),
	cmocka_unit_test(memzero_null_pointer_test),
	cmocka_unit_test(memzero_check_region_zero),
	cmocka_unit_test(reverse_null_pointer_test),
	cmocka_unit_test(reverse_check_odd),
	cmocka_unit_test(reverse_check_even),
	cmocka_unit_test(reverse_check_all_chars),
	cmocka_unit_test(big_to_litte_null_pointer_test),
	cmocka_unit_test(big_to_litte_conversion_test),
	cmocka_unit_test(little_to_big_null_pointer_test),
	cmocka_unit_test(little_to_big_conversion_test),
	cmocka_unit_test(create_cicular_buffer),
	cmocka_unit_test(circular_buffer_null_pointer_test),
	cmocka_unit_test(circular_buffer_initialized_test),
	cmocka_unit_test(circular_buffer_add_remove_test),
	cmocka_unit_test(circular_buffer_full_test),
	cmocka_unit_test(circular_buffer_empty_test),
	cmocka_unit_test(circular_buffer_wrap_add_test),
	cmocka_unit_test(circular_buffer_wrap_remove_test),
	cmocka_unit_test(circular_buffer_overfill_test),
	cmocka_unit_test(circular_buffer_overempty_test),	
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
  }
