#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

static uint64_t b_moves = 0;
static uint64_t b_comps = 0;

//print the array in columns of 7
//length = elements in arr[]
void printb(uint32_t arr[], uint32_t length);

//function to swap two elements of array (arr[]) indexes (i)
//swaps with the index to the left
//increments moves by 3
void swapb(uint32_t arr[], uint32_t i);

//function to compare two elements of array indexes (i)
//returns true if arr[i] < arr[i-1]
//increments count by 1
bool compb(uint32_t arr[], uint32_t i);

//function to perform the bubble sort
void bubble_sort(uint32_t arr[], uint32_t length);

#endif
