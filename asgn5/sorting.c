#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include "binary.h"

#include <getopt.h>

#define OPTIONS "Absqip:r:n:"

//bitmask : 1073741823
#define BITMASK 0x3FFFFFFF

//function to reinitialize the array for reuse
void reset_array(uint32_t arr[], uint32_t length) {
	for (uint32_t i = 0; i < length; i++) {
		//initialize elements to 0
		arr[i]=0;
	}
}
//fill the array with values form rand 
void fill_array(uint32_t arr[], uint32_t length, uint32_t seed) {
    //plant the random seed each call
    srand(seed);
	for (uint32_t i = 0; i < length; i++) {
		//creates the values within capped range
		arr[i] = rand() & BITMASK;	
	}
}

int main ( int argc, char ** argv) {
	//variables and initializations
	int c = 0;
	uint32_t length = 100;	//default length of array
	uint32_t seed = 8222022;	//default seed

	//options to be set by switch case getopt
	bool all, bubble, shell, quick, ibinary;
	all = bubble = shell = quick = ibinary = 0;

	//optarg user inputs
	char *get_len = NULL;
	char *get_seed = NULL;

	//getopt while
	while ( (c = getopt(argc, argv, OPTIONS)) != -1) {
		switch (c) {
			//ALL the sorts
			case 'A':
				all = bubble = shell = quick = ibinary = 1;
				break;

			//bubble sort
			case 'b':
				bubble = 1;
				break;

			//shell sort
			case 's':
				shell = 1;
				break;

			//quick sort
			case 'q':
				quick = 1;
				break;

			//binary insert search
			case 'i':
				ibinary = 1;
				break;

			//print the first n elements of the array (get n)
			case 'p':
				get_len = optarg;
				//make sure theres at least 1 element in the array
				if ( atoi(get_len) > 0) {
					length = atoi (get_len);
				}
				break;

			//set seed
			case 'r':
				get_seed = optarg;
				seed = atoi(get_seed);
				break;
		}
	}
	//error check the getopt
	if (argc == 1) {
		return -1;
	}

	//initialize the array
	uint32_t *arr = calloc(length, sizeof(uint32_t));

	//initially fill the array with rand seed
	fill_array(arr, length, seed);

	//if getopts are triggered start the sorting
	//if all is triggered all will run in sequence
    
    if (ibinary) {
        if ( all ) {
            printf("\n");
        }
        binary_insertion(arr, length);
        //reset and refill with same rand seed if all was triggered
        reset_array(arr, length);
        fill_array(arr, length, seed);
    }
    
    if (quick) {
        //perform quick sort
        if ( all ) {
            printf("\n");
        }
        quick_sort(arr, 0, length-1);
        printq( arr, length);
        //reset and refill with same rand seed if all was triggered
        reset_array(arr, length);
        fill_array(arr, length, seed);
    }
    
	if (shell) {
        if ( all ) {
            printf("\n");
        }
		shell_sort(arr, length);
		//reset and refill with same rand seed if all was triggered
		reset_array(arr, length);
		fill_array(arr, length, seed);
	}

    if (bubble) {
        if ( all ) {
            printf("\n");
        }
        bubble_sort(arr, length);
        //reset and refill with same rand seed if all was triggered
        reset_array(arr, length);
        fill_array(arr, length, seed);
    }

	return 0;
}
