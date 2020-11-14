#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"

#include <getopt.h>

#define OPTIONS "Absqip:r:n:"

// bitmask : 1073741823
#define BITMASK 0x3FFFFFFF

// function to reinitialize the array of n length for reuse
void reset_array(uint32_t arr[], uint32_t length) {
  for (uint32_t i = 0; i < length; i++) {
    // initialize elements to 0
    arr[i] = 0;
  }
}
// fill the array with values form rand
void fill_array(uint32_t arr[], uint32_t length, uint32_t seed) {
  // plant the random seed each call
  srand(seed);
  for (uint32_t i = 0; i < length; i++) {
    // creates the values within capped range
    arr[i] = rand() & BITMASK;
  }
}

int main(int argc, char **argv) {
  // variables and initializations
  int c = 0;
  // these are the defaults for optional getopt defined inputs
  uint32_t print_len = 100;
  uint32_t length = 100;
  uint32_t seed = 8222022;

  // options to be set by switch case getopt
  bool all, bubble, shell, quick, ibinary;
  all = bubble = shell = quick = ibinary = 0;

  // optarg user inputs
  char *get_len = NULL;
  char *get_seed = NULL;
  char *get_p_len = NULL;

  // getopt while
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    // ALL the sorts = T
    case 'A':
      all = bubble = shell = quick = ibinary = 1;
      break;

    // bubble sort = T
    case 'b':
      bubble = 1;
      break;

    // shell sort = T
    case 's':
      shell = 1;
      break;

    // quick sort = T
    case 'q':
      quick = 1;
      break;

    // binary insert search = T
    case 'i':
      ibinary = 1;
      break;

    // set the print length which will print the first n elements of the array
    case 'p':
      get_p_len = optarg;
      print_len = atoi(get_p_len);
      break;

    // get seed form user and set seed
    case 'r':
      get_seed = optarg;
      seed = atoi(get_seed);
      break;

    // get the length of elements for the array
    case 'n':
      get_len = optarg;
      // make sure theres at least 1 element in the array
      if (atoi(get_len) > 0) {
        length = atoi(get_len);
      }
      break;
    }
  }
  // error check the getopt
  if (argc == 1) {
    return -1;
  }

  // initialize the array
  uint32_t *arr = calloc(length, sizeof(uint32_t));

  // initially fill the array with rand seed
  fill_array(arr, length, seed);

  // if getopts are triggered start the sorting
  // if all is triggered all will run in sequence

  if (ibinary) {
    if (all) {
      printf("\n");
    }
    binary_insertion(arr, length, print_len);
    // reset and refill with same rand seed if all was triggered
    reset_array(arr, length);
    fill_array(arr, length, seed);
  }

  if (quick) {
    // perform quick sort
    if (all) {
      printf("\n");
    }
    quick_sort(arr, 0, length - 1);
    printq(arr, length, print_len);
    // reset and refill with same rand seed if all was triggered
    reset_array(arr, length);
    fill_array(arr, length, seed);
  }

  if (shell) {
    if (all) {
      printf("\n");
    }
    shell_sort(arr, length, print_len);
    // reset and refill with same rand seed if all was triggered
    reset_array(arr, length);
    fill_array(arr, length, seed);
  }

  if (bubble) {
    if (all) {
      printf("\n");
    }
    bubble_sort(arr, length, print_len);
    // reset and refill with same rand seed if all was triggered
    reset_array(arr, length);
    fill_array(arr, length, seed);
  }

  return 0;
}
