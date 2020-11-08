README.md

sequence.c

This program is designed to print primes, and special primes:

	1) Mersenne Prime
	2) Lucas Prime
	3) Fibonacci Prime

This program will also print palindromic primes in the following bases:

	1) Base 2
	2) Base 9
	3) Base 10
	4) Base 26

User may input the length of numbers to test for primality (optional)

How to make and compile program and header files
With the provided Makefile and supporting files in current directory
In the bash terminal make and create executable :
	
	$ make sequence.c
	$./sequence

	•CFLAGS=-Wall -Wextra -Werror -Wpedantic
	•CC = clang must be specified
	•make clean removes all files that are compiler generated.
	•make infer creates the infer-out
	•make should build your program, as should make all

Program supports the following command-line options
	
	$./sequence -n x	//sets the length to test primality to x (OTHERWISE x = 1000)
	$./sequence -s		//compile the sequence for special primes with x disks
	$./sequence -p		//compile the sequence for palindromes in different bases 
						// Bases:(2) (9) (10) (26)
