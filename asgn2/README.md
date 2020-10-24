README.md

	Math.c

This program tests various homemade math function approximations with the folling parameters:

	functions		ranges			steps			Approx / formula	Order/threshold		Helper Fxns
	sin(x)		 [-2pi, 2pi)	w/ steps of pi/16		Horners				14th				Power
	cos(x)		 [-2pi, 2pi)	w/ steps of pi/16		Horners				14th				Power
	tan(x)		 [-pi/3, pi/3)	w/ steps of pi/16	 trig identity			14th			sin(x)/cos(x)
	e^x			 [0,9] 			w/ steps of 0.1		Maclaurin series		10^-9		Power  / Factorial

The functions above are tested against <math.h> math function standard libraries provided in C
The difference is calculated and reflected along the following ranges.

	No user input is required during runtime
	Observe the results by doing the following:

With the provided Makefile

In the bash terminal:

1) $ make and compile 'math.c' program
	•CFLAGS=-Wall -Wextra -Werror -Wpedantic
	•CC=clangmust be specified.•make cleanmust remove all files that are compiler generated.
	•make infer was not able to work for me. May depend on command line setup. Wasn't able to troubleshoot
	•make should build your program, as should make all

	Program supports the following command-line options 
		$./math -s			//compile executable to ouput SIN results
		$./math -c			//compile executable to ouput COS results
		$./math -t			//compile executable to ouput TAN results
		$./math -e			//compile executable to ouput E^X results
		$./math -a			//compile executable to ouput ALL results
