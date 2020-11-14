#ifndef __BINARY_H__
#define __BINARY_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

static uint64_t i_moves = 0;
static uint64_t i_comps = 0;

//print the array in columns of 7
//length = elements in arr[]
void printi(uint32_t arr[], uint32_t length, uint32_t print_len);

//function to swap two elements of array (arr[]) index
//swaps with the index to the left
//increments moves by 3
void swapi(uint32_t arr[], uint32_t i);

//function to compare two values from array index
//Returns true if val1 >= val2
//increments count by 1
bool compi(uint32_t val1, uint32_t val2);

//function to compare two values from array index
//Returns true if val1 < val2
//increments count by 1
bool compi2( uint32_t val1, uint32_t val2);

//function to perform the binary insertion sort
void binary_insertion(uint32_t arr[], uint32_t length, uint32_t print_len);

#endif
