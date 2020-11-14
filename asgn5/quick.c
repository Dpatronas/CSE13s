#include "quick.h"

void printq(uint32_t arr[], uint32_t length, uint32_t print_len) {
  //print the elements, moves, and comps
  printf("Quick Sort\n");
  printf("%d elements, ",length);
  printf("%lu moves, ", q_moves);
  printf("%lu compares\n", q_comps);

  //iterate through array elements -1
  for (uint32_t i = 0; i < print_len; i++) {
    //print the elements
    printf("%13" PRIu32, arr[i]);
    //print in columns of 7
    if (i % 7 == 6) {
      printf("\n");
    }
  }
}

void swapq(uint32_t arr[], uint32_t low, uint32_t hi) {
	//temp to hold the intermediate step of swap
	uint32_t temp = arr[low];
	arr[low] = arr[hi];	//swap
	arr[hi] = temp;		//swap

	//increment moves
	q_moves+=3;
}

bool compq(uint32_t val1, uint32_t val2) {
  //if arr[index] > arr[index+1] return T
  if (val1 <= val2) {
    return 1;
    q_comps++;
  }	
  //in either case, increment the comparisons
  q_comps++;
  return 0;
}

int partition(uint32_t arr[], int32_t left, int32_t right) {
  //pivot is the first element
  uint32_t pivot = arr[left];
  //low is the second element
  uint32_t low = left + 1;
  //right is the least element
  uint32_t hi = right;
  
  //continue loop until the 
  while (1) {

    //low <= hi doesnt count as a comp
    //(low <= hi) && (arr[hi-1] >= pivot)
    while( (low <= hi) && compq(pivot,arr[hi]) ) {
      hi -= 1;
    }

    //(low <= hi) && (app[low] <= pivot)
    while( (low <= hi) && compq(arr[low], pivot) ) {
      low += 1;
    }
    //(arr[low] <= arr[hi])
    if ( compq(low,hi) ) {
      swapq(arr, low, hi);
    }
    //otherwise arr[low] > arr[hi]
    else {
      break;
    }
  }
  //(arr[left] <-> arr[hi])
  swapq(arr, left, hi);
  return hi;
}

void quick_sort(uint32_t arr[], int32_t left, int32_t right, uint32_t length, uint32_t print_len) {
  // left < right no comps here
	if ( left < right ) {
    //set index = hi
    uint32_t index = partition(arr, left, right);
    //sort based on new right = index -1
    quick_sort(arr, left, index - 1, length, print_len);
    //sort based on new left = hi+1
    quick_sort(arr, index + 1, right, length, print_len);
  }
  else {
  //print the array when it is finished
  printq(arr, length, print_len);
  }
}
