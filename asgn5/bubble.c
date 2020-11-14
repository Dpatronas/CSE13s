#include "bubble.h"

void printb(uint32_t arr[], uint32_t length, uint32_t print_len) {
  // print the elements, moves, and comps
  printf("Bubble Sort\n");
  printf("%d elements, ", length);
  printf("%lu moves, ", b_moves);
  printf("%lu compares\n", b_comps);

  // iterate through array elements -1
  for (uint32_t i = 0; i < print_len; i++) {
    // print the elements
    printf("%13" PRIu32, arr[i]);
    // print in columns of 7
    if (i % 7 == 6) {
      printf("\n");
    }
  }
}

void swapb(uint32_t arr[], uint32_t i) {
  // temp to hold the intermediate step of swap
  uint32_t temp = arr[i];
  arr[i] = arr[i - 1]; // swap
  arr[i - 1] = temp;   // swap

  // increment moves by 3 for swap
  b_moves += 3;
}

bool compb(uint32_t arr[], uint32_t i) {
  // if arr[index] > arr[index+1] return T
  if (arr[i] < arr[i - 1]) {
    b_comps++;
    return 1;
  }
  // in either case, increment the comparisons by 1
  b_comps++;
  // otherwise return F
  return 0;
}

void bubble_sort(uint32_t arr[], uint32_t length, uint32_t print_len) {
  uint32_t j = 0;
  // go through entire length to start
  for (uint32_t i = 0; i < length - 1; i++) {
    // j = the end
    j = length - 1;
    // while the index is less than the end
    while (j > i) {
      // compare
      if (compb(arr, j)) {
        // if true, swap
        swapb(arr, j);
      }
      // decrement the end index even if no swapping occured
      j--;
    }
  }
  // print the array when it is finished
  printb(arr, length, print_len);
}
