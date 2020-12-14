#include "io.h"
#include "word.h"
#include "trie.h"
#include <math.h>
#include <getopt.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//extern stats
uint64_t uncompressed_bits;
uint64_t compressed_bits;

#define OPTIONS "vi:o:"

int bit_length (int num) {
	return (log2(num) + 1);
}

int main (int argc, char* argv[]) {

	int c = 0;
	bool stats = false;

	//default in / out file
	int infile = STDIN_FILENO;
	int outfile = STDOUT_FILENO;

	while ((c=getopt(argc, argv, OPTIONS)) != -1) {
		switch (c) {

			//display compression statistics
			case 'v':
				stats = true;
				break;

			//specify input other than stdin
			case 'i':
				infile = open(optarg, O_RDONLY);
				break;

			//specify output other than stout
			case 'o':
				outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				break;
		}
	}

	//make a fileheader struct contains the protection bits and magic num
	FileHeader hd = {0,0};;
	read_header(infile, &hd);

	if (hd.magic != 0x8badbeef) {
		exit(1);
	}

	//outfile emulates infile protection
	fchmod(outfile, hd.protection);

	//decoding based on provided pseudocode in asgn7 lab
	WordTable * table = wt_create();
	uint8_t curr_sym = 0;
	uint16_t curr_code = 0;
	uint16_t next_code = START_CODE;

	while ( true ) {

		// printf("code: %x, symbol: %x, bit len: %x\n", curr_code, curr_sym, bit_length(next_code));

		bool res = read_pair(infile, &curr_code, &curr_sym, bit_length(next_code));
		if (res == false)
		{
			break;
		}

		// printf("code: %d, symbol: 0x%.2X\n", curr_code, curr_sym);

		table[next_code] = word_append_sym(table[curr_code], curr_sym);
		buffer_word(outfile, table[next_code]);

		next_code ++;
		if (next_code == MAX_CODE) {
			wt_reset(table);
			next_code = START_CODE;
		}

		flush_words(outfile);
	}

	wt_delete(table);

	if (stats) {
		printf("Compressed file size: %lu bits\n", compressed_bits);
		printf("Uncompressed file size: %lu bits\n", uncompressed_bits);

		long long ratio = 0;
		ratio = (long long)(100 * (double)uncompressed_bits/compressed_bits);

		printf("Compression ratio: %lld%%\n", ratio);
	}

	close(infile);
	close(outfile);

	return 0;
}
