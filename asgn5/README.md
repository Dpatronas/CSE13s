README.md

sorting.c

#This program is designed to sort a (seed defined 'randomly' populated) int array of n size using the following sorting algorithms:

	1) Bubble sort
	2) Shell sort
	3) Quick sort
	4) Binary Insertion sort

#In addition to sorting the array of n sized integer elements, the program will:

	count the n sized array		[WILL DEFAULT TO 100]
	count logical comparisons 	(<=, <, >=, >, ==)
	count swaps 				( arr[index1] <-> arr[index2] )

*note: a move is considered the swapping of two elements values in an array. In C a swap uses a temporary variable to preserve the value in the intermediate step, therefore a swap is considered 3 moves.


**The goal here is to compare the efficiency of each test side by side**

#*How to Make and compile sorting.c and supporting files
	*with the provided Makefile, .c, and .h files in current directory
	*in the bath terminal make and create the executable for sorting.c
		*$make sorting.c
		*$./sorting

#Whats included in the makefile

	•CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c99
	•CC = clang specified

	•make clean 	removes all files that compiler generated.
	•make valgrind 	will generate a valgrind report of memory usage
			(based on: valgrind ./sorting -A)

	•make infer 	**Make infer has an issue with NULL DEREFERENCE pointer**
			 of calloced array being called in function as parameter
			 (note: valgrind reports no memory leaks)

	•make 			builds the program
	•make all 		builds the program

Program supports the following command line options

	$./sorting -A 	run all sorting programs
	$./sorting -b 	runs bubble sort
	$./sorting -s 	runs shell sort
	$./sorting -q 	runs quick sort
	$./sorting -i 	runs binary insertion sort
	$./sorting -p 	prints n elements of the array.   (default print n = 100)
	$./sorting -r 	set the random seed to s	  (default s = 8222022)
	$./sorting -n 	sets the n elements of the array. (default n = 100)

Valgrind Report: 400 Bytes allocated.
		 Total Heap Usage: 1 alloc made, 1 alloc freed. NO MEMORY LEAKS
