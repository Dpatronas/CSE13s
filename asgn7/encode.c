#include "io.h"
#include "word.h"
#include "trie.h"
#include <math.h>
#include <getopt.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPTIONS "vi:o:"

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
				infile = open(optarg, O_RDONLY);
				break;

			//specify output other than stout
			case 'o':
				outfile = open(optarg, O_WRONLY);
				break;
		}
	}

	//make a fileheader struct contains the protection bits and magic num
	FileHeader hd = {0,0};
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

	//encoding based on provided pseudocode in asgn7 lab
	TrieNode *root = trie_create();
	TrieNode *curr_node = root;
	TrieNode *prev_node = NULL;
	uint8_t curr_sym = 0;
	uint8_t prev_sym = 0;
	uint16_t next_code = START_CODE;	// START_CODE = 2

	while (read_sym(infile, &curr_sym)) {
		
		TrieNode * next_node = trie_step(curr_node, curr_sym);
		
		if (next_node) {
			prev_node = curr_node;
			curr_node = next_node;
		}
		else {
			buffer_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
			curr_node->children[curr_sym] = trie_node_create(next_code);
			curr_node = root;
			next_code ++;

			if (next_code == MAX_CODE) {
				trie_reset(root);
				curr_node = root;
				next_code = START_CODE;
			}
			prev_sym = curr_sym;
		}
		if (curr_node != root) {
			buffer_pair(outfile, STOP_CODE, 0, bit_length(next_code));
			next_code = (next_code+1) % MAX_CODE;
		}
		buffer_pair(outfile, STOP_CODE, 0, bit_length(next_code));
		flush_pairs(outfile);
	}

	trie_delete(root);
	close(infile);
	close(outfile);

	return 0;
}
