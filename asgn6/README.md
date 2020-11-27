README.md

hatterspeak.c

#This program is designed create dictionary of words from 2 user input txt files

	1) hatterspeak.txt 	(words which have translatable counterparts next to them)
	2) oldspeak.txt 	(forbidden words)


#Storing and accessing data for dictionary:

	bv files, speck files, bf files:

		oldspeak words from both files will be hashed with speck using (3) 128 bit salts to reduce false positives.
		Into a Bloom filter (with underlying ADT bit vector)

	hash files, ll files, hattspeak files

		Generate a linked list for words in the dictionary and whether they are translatable or not.
		Generate a hash table of linked list (hashed using (1) 128 bit salt)
			*Note this program checks for duplicates, discards the old data and replaces it with the new data

#I/O
	This program supports user input via stdin
		This input is filtered through REGEX (loosely) to take in appropriate language syntax
		This input will continuously take in user input until EOF or Null termination of stdin stream

		Display "letter" message based on the user input
			Compares user input words to dictionary and determines if they are 1)forbidden and/or 2)translatable

#Stats

	This program will determine various stats about the performance of the bloomfilter, linked list, and hashtable
		based on various factors:

		1) linked list insertions mode: //Move_to_front
		2) Seeks: 						# Seeks performed
		3) Average Seek length: 		# nodes traversed / Seeks
		4) Average Linked List Length: 	Sum Linked Lists / Hash Table length
		5) Hash Table Load:				# heads indexed / Hash Table length
		6) Bloom Load:					# Set Vec Bits / Bloomfilter length


#*How to Make and compile hatterspeak.c and supporting files
	*with the provided Makefile, .c, and .h files in current directory
	*in the bash terminal make and create the executable for hatterspeak.c
		*$make hatterspeak.c
		*$./hatterspeak

#Whats included in the makefile

	•CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c99 -g (for debugging with lldb)
	•CC = clang specified

	•make clean 	removes all files that compiler generated.
	•make valgrind 	will generate a valgrind report of memory usage
	•make infer 	generates a report of memory usage and errors
	•make 			builds the program
	•make all 		builds the program

Program supports the following command line options

	$./hatterspeak -s 	supress letter, print stats
	$./hatterspeak -h 	specify Hash Table size 	default size: 10000
	$./hatterspeak -f 	specify Bloom Filter size 	default size: 2^20
	$./hatterspeak -m 	Toggle Move_to_Front
	$./hatterspeak -b 	this is the default mode
					
	( -m || -b )

