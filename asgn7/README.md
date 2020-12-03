README.md

encode.c
decode.c

#Program using Lempel-Ziv Compression LZ78:

	COMPRESSION:

	Open infile with open () 				default infile = stdin (may change with user input) getopt optarg)
	outfile header file with magic number:	1) 0xbadbeef
											2) filesize
											3) protected bitmask (using fstat())


#


#I/O
	This program supports user input via stdin


#Stats printout
	For encode.c:
		Compressed file size: 		X Bytes
		Uncompressed file size:		X Bytes
		Comrpression rate:			float decimal percentage

	For decode.c:
		Decompressed file size: 	X Bytes
		Undecompressed file size:	X Bytes
		Decompression rate:			float decimal percentage

#Whats included in the makefile?

	•CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c99 -g (for debugging with lldb)
	•CC = clang specified

	•make clean 	removes all files that compiler generated.
	•make valgrind 	will generate a valgrind report of memory usage
	•make all 		builds the program

	•make infer 	generates a report of memory usage and errors
	•make 			builds the program
	•make all 		builds the program

Program supports the following command line options

	$./encode -v 			print stats for compression
	$./encode -i <input>	specify input to compress (stdin by default)
	$./encode -o <output>	specify output of compression (stdout by default)


	$./decode -v 			print stats for decompression
	$./decode -i <input>	specify input to decompress (stdin by default)
	$./decode -o <output>	specify output of decompression (stdout by default)
