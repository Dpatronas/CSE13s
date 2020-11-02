README.md

	tower.c

This program is designed to test two implementations for solution to towers of hanoi game as a way to test the differences in ease of codability and performance of both iterations

	1) Stack solution		//solution inspired (refer to the DESIGN.pdf
	2) Recursive solution	//for the credits and sources)

	In both cases, user may input number of disks (optional)
	

how to make and compile 'tower.c' program and stack object and source files

With the provided Makefile and supporting files in current directory
In the bash terminal make and create executable :

	$ make tower.c
	$./tower

		•CFLAGS=-Wall -Wextra -Werror -Wpedantic
		•CC = clang must be specified
		•make clean removes all files that are compiler generated.
		•make infer creates the infer-out and running infer reports no issues found but there is a backtrace error. 
		•make should build your program, as should make all

Program supports the following command-line options 

		$./tower -n x	//sets the number of disks to x (OTHERWISE x = 5)
		$./tower -s		//compile the stack implementation with x disks
		$./tower -r		//compile the recursive implementation with x disks

Memory (no leaks):
	the stack implementation uses heap allocated memory for:
		-creation of defined stack
		-int array variable within struct stack

	Valgrind reports a total of 252 Bytes to be allocated
	while running the executable tower.
	At runtime all allocated Bytes are freed

