#ifndef __QUICK_H__
#define __QUICK_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

static uint64_t q_moves = 0;
static uint64_t q_comps = 0;

//print the array in columns of 7
//length = elements in arr[]
void printq(uint32_t arr[], uint32_t length);

//function to swap two elements of array
//arr[low] <-> arr[hi]
//increments the moves by 3
void swapq(uint32_t arr[], uint32_t low, uint32_t hi);

//function to compare two elements of array
//returns true if ex: arr[low] <= arr[hi]
//increments count by 1
bool compq(uint32_t low, uint32_t hi);

int partition(uint32_t arr[], int32_t left, int32_t right);

//function to perform quick sort on an array
void quick_sort(uint32_t arr[], int32_t left, int32_t right);

#endif
