#include "io.h"
#include "word.h"
#include "trie.h"
#include <math.h>

int bit_length (int num) {
	return (log2(num) + 1);
}

int main (int argc, char ** argv) {

	int c = 0;
	//default in / out file
	int infile = STDIN_FILENO;
	int outfile = STDOUT_FILENO;

	while ((c=getopt(argc, argv, OPTIONS)) != -1) {
		switch (c) {

			//display compression statistics
			case 'v':
				break;

			//specify input other than stdin
			case 'i':
				int infile = open(optarg, O_RDONLY);
				break;

			//specify output other than stout
			case 'o':
				int outfile = open(optarg, O_WTONLY);
				break;
		}
	}

	//make a fileheader struct contains the protection bits and magic num
	FileHeader hd = {0,0};;
	read_header(infile, &hd);
	hd.magic = MAGIC;

	if (hd.magic != 0x8badbeef) {
		exit(1);
	}

	//file protection
	struct stat header_protection;
	fstat(infile, &header_protection);
	hd.protection = header_protection.st_mode;
	//outfile emulates infile protection
	fchmod(outfile, hd.protection);
	write_header(outfile, &hd);

	//decoding based on provided pseudocode in asgn7 lab
	WordTable * table = wt_create();
	uint8_t curr_sym = 0;
	uint16_t curr_code = 0;
	uint16_t next_code = START_CODE;
	
	while ( read_pair(infile, &curr_code, &curr_sym, bit_length(next_code)) ) {
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
  close(infile);
  close(outfile);

  return 0;
}
