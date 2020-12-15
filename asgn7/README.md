README.md

		***NOTE encoding files: last couple bits my encode cleans up the dirty bits at the end, while the testing testing files do not.

encode.c
decode.c

#Program using Lempel-Ziv Compression/ Decompression LZ78:

	Open infile and outfile with default stdin
	header file protections: 
		magic number:	1) 0xbadbeef
		fchmod and fstat to set and grab header protections



#I/O
	This program supports user input/output via stdin in getopts


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
	•make all 		builds the program

	•make infer 	generates a report of memory usage and errors
	•make 			builds the program
	•make all 		builds the program

Program supports the following command line options

	$./encode -v 			print stats for compression
	$./encode -i <input>	specify input to compress to (stdin by default)
	$./encode -o <output>	specify output of compression (stdout by default)


	$./decode -v 			print stats for decompression
	$./decode -i <input>	specify input to decompress to (stdin by default)
	$./decode -o <output>	specify output of decompression (stdout by default)

Thank you TA's <3
