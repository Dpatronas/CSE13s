#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

static uint64_t s_moves = 0;
static uint64_t s_comps = 0;

//print the array in columns of 7
//length = elements in arr[]
void prints(uint32_t arr[], uint32_t length, uint32_t print_len);

//function to swap two elements of array
//j and gap are two variables indeces to be swapped
//returns  arr[j+gap] <-> arr[gap]
//increments moves by 3
void swaps(uint32_t arr[], uint32_t j, uint32_t gap);

//function to compare two elements of array indexes (i)
//returns true if arr[j+1] < arr[gap]
//increments count by 1
bool comps(uint32_t arr[], int32_t j, int32_t gap);

//This implementation appears in: 
//page 62 of "the C Programming Language"
//by Brian W. Kernighan and Dennis M. Ritchie
//function to do the shell sort of array (arr[])
//length = elements in arr[]
void shell_sort(uint32_t arr[], uint32_t length, uint32_t print_len);

#endif
