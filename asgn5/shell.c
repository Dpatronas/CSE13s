#include "shell.h"

void prints(uint32_t arr[], uint32_t length, uint32_t print_len) {
  // print the elements, moves, and comps
  printf("Shell Sort\n");
  // print the length that was sorted
  printf("%d elements, ", length);
  printf("%lu moves, ", s_moves);
  printf("%lu compares\n", s_comps);

  // iterate through array elements (for print length)
  for (uint32_t i = 0; i < print_len; i++) {
    // print the elements
    printf("%13" PRIu32, arr[i]);
    // print in columns of 7
    if (i % 7 == 6) {
      printf("\n");
    }
  }
}

void swaps(uint32_t arr[], uint32_t j, uint32_t gap) {

  uint32_t temp = arr[j]; // temp to hold the intermediate step of swap
  arr[j] = arr[j + gap];  // swap
  arr[j + gap] = temp;    // swap

  s_moves += 3; // increment moves (3 per swap)
}

bool comps(uint32_t arr[], int32_t j, int32_t gap) {

  // if array to the right of gap is < element
  if (arr[j + gap] < arr[j]) {
    s_comps++;
    return 1; // return T
  }
  s_comps++; // in either case, increment the comparisons
  return 0;  // otherwise return F
}

// This implementation appears in:
// page 62 of "the C Programming Language"
// by Brian W. Kernighan and Dennis M. Ritchie
void shell_sort(uint32_t arr[], uint32_t length, uint32_t print_len) {

  int32_t gap = 0; // gap to create "subarrays"

  // outer loop iterates through all the gaps
  for (gap = length / 2; gap > 0; gap /= 2) {
    s_comps *= 2;
    // middle loop steps through elements
    for (uint32_t i = gap; i < length; i++) {
      // inner loop compares the elements adjacent to gap
      for (int j = i - gap; j >= 0 && comps(arr, j, gap); j -= gap) {
        s_comps++;
        // arr[j] <-> arr[gap]
        swaps(arr, j, gap);
      }
    }
  }
  // print the array when it is finished
  prints(arr, length, print_len);
}
