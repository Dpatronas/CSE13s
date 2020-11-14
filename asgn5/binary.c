#include "binary.h"

void printi(uint32_t arr[], uint32_t length) {
  //print the elements, moves, and comps
	printf("Binary Insertion Sort\n");
	printf("%d elements, ",length);
	printf("%lu moves, ", i_moves);
	printf("%lu compares\n", i_comps);

  //iterate through array elements -1
  for (uint32_t i = 0; i < length; i++) {
    //print the elements
    printf("%13" PRIu32, arr[i]);
    //print in columns of 7
    if (i % 7 == 6) {
      printf("\n");
    }
  }
}

//swap = 3 moves
void swapi( uint32_t arr[], uint32_t i) {
	//temp to hold the intermediate step of swap
	uint32_t temp = arr[i];
	arr[i] = arr[i-1];		//swap
	arr[i-1] = temp;		//swap

	//increment moves
	i_moves+=3;
}

bool compi( uint32_t val1, uint32_t val2) {
  if (val1 >= val2) {
    return 1;
    i_comps++;
  }	
  //in either case, increment the comparisons
  i_comps++;
  return 0;
}

void binary_insertion(uint32_t arr[], uint32_t length) {

  for (uint32_t i = 1; i < length; i++) {
    uint32_t value = arr[i];
    uint32_t left = 0;
    uint32_t right = i;
    
    while (left < right) {
      uint32_t mid = left + ((right - left)/2);
      //value >= arr[mid]
      if (compi(value,arr[mid])) {
        left = mid + 1;
      }
      else {
        right = mid;
      }
    }
    for (uint32_t j = i; j > left; j--) {
      swapi(arr, j);
    }
  }
  printi(arr, length);
}
