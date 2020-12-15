#include "io.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>

#define BLOCK 4096

//extern stats
uint64_t uncompressed_bits; //decoded
uint64_t compressed_bits;   //encoded

//read_sym
static uint8_t sym_buff[BLOCK]; //buffer to store symbols
static uint16_t sym_index;      //index of sym bit

//buffer_pair and read_pair
static uint8_t bitbuff[BLOCK];  //buffer stores bits
static uint16_t bitindex;       //index of buff bit

//buffer_word
static uint8_t wordbuffer[BLOCK];
static uint16_t word_index;


//read from infile
int read_bytes(int infile, uint8_t *buff, int to_read) {

	int read_bytes = 0; //number of bytes read
	int total = 0;			//number of bytes to read

	do {
		read_bytes = read(infile, (buff + total), (to_read - total));
		total += read_bytes;
	}
	while ((read_bytes > 0) && (total != to_read));
	return total;
}


//write to outfile
int write_bytes(int outfile, uint8_t *buff, int to_write) {

	int write_bytes = 0;//number of bytes wrote
	int total = 0;		//number of bytes to write

	do {
		write_bytes = write(outfile, (buff + total), (to_write - total));
		total += write_bytes;
	}
	while (write_bytes > 0 && total != to_write);

	return total;
}

//decode
void read_header(int infile, FileHeader *header) {

	compressed_bits += (8 * sizeof(FileHeader));
	read_bytes (infile, (uint8_t*)header, sizeof(FileHeader));
}

//encode
void write_header(int outfile, FileHeader *header) {

	compressed_bits += (8 * sizeof(FileHeader));
	write_bytes (outfile, (uint8_t*)header, sizeof(FileHeader));
}

//encode
bool read_sym(int infile, uint8_t *sym) {

	//track the bytes which have been read
	static int remaining_symbols = 0;

	if (remaining_symbols == 0) {
		remaining_symbols = read_bytes(infile, sym_buff, BLOCK);
		if ( !remaining_symbols )
		{
			// nothing left, return
			return false;
		}
	}

	//load symbol as the current index of buffer and increment
	*sym = sym_buff[sym_index];
	sym_index = (sym_index + 1) % BLOCK;
	remaining_symbols--;
	uncompressed_bits += 8;

	return true;
}

//encode
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bit_len) {

	// printf("code: %d, symbol: 0x%.2X\n", code, sym);

	for (int i = 0; i < bit_len; ++i, bitindex++)
	{
		if ( BLOCK == (bitindex / 8) ) // optimize: bitindex >> 3
		{
			flush_pairs(outfile);
		}

		uint16_t byte_idx = bitindex / 8;
		uint8_t normalized_bit_idx = bitindex % 8;

		uint8_t extracted_bit = code & 1;
		code = code >> 1;

		bitbuff[byte_idx] |= (extracted_bit << normalized_bit_idx);
	}

	for (int i = 0; i < 8; ++i, bitindex++)
	{
		if ( BLOCK == (bitindex / 8) ) // optimize: bitindex >> 3
		{
			flush_pairs(outfile);
		}

		uint16_t byte_idx = bitindex / 8;
		uint8_t normalized_bit_idx = bitindex % 8;

		uint8_t extracted_bit = sym & 1;
		sym = sym >> 1;

		bitbuff[byte_idx] |= (extracted_bit << normalized_bit_idx);
	}
}

//encode
void flush_pairs(int outfile) {

	int total = 0;

	if (bitindex != 0) {
		total = write_bytes(outfile, bitbuff, to_bytes(bitindex));
		bitindex = 0;

		memset(bitbuff, 0, sizeof(bitbuff));
	}

	compressed_bits += (total * 8);
}

//decode
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bit_len) {

	*code = 0;
	*sym = 0;

	if (bitindex == 0) {
		int blen = read_bytes(infile, bitbuff, BLOCK);
		compressed_bits += (blen * 8);
	}

	uint16_t tcode = 0;
	for (int i = 0; i < bit_len; ++i, bitindex++)
	{
		if ( BLOCK == (bitindex / 8) ) // optimize: bitindex >> 3
		{
			int blen = read_bytes(infile, bitbuff, BLOCK);
			bitindex = 0;
			compressed_bits += (blen * 8);
		}

		uint16_t byte_idx = bitindex / 8;
		uint8_t normalized_bit_idx = bitindex % 8;
		uint8_t extracted_bit = (bitbuff[byte_idx] >> normalized_bit_idx) & 1;
		tcode |= (extracted_bit << i);
	}
	*code = tcode;

	if( *code == STOP_CODE )
	{
		return false;
	}

	uint16_t tsym = 0;
	for (int i = 0; i < 8; ++i, bitindex++)
	{
		if ( BLOCK == (bitindex / 8) ) // optimize: bitindex >> 3
		{
			int blen = read_bytes(infile, bitbuff, BLOCK);
			bitindex = 0;
			compressed_bits += (blen * 8);
		}

		uint16_t byte_idx = bitindex / 8;
		uint8_t normalized_bit_idx = bitindex % 8;
		uint8_t extracted_bit = (bitbuff[byte_idx] >> normalized_bit_idx) & 1;
		tsym |= (extracted_bit << i);
	}
	*sym = tsym;

	return true;
}

//decode
void buffer_word(int outfile, Word *w) {

	for (uint32_t i = 0; i < w->len; i++) {
		wordbuffer[word_index] = w->syms[i];
		word_index++;
		//if buffer fills up write the bytes to the outfile
		if (word_index == BLOCK) {
			flush_words(outfile);
		}
	}
}

//decode
void flush_words(int outfile) {

	int total = 0;

	if (word_index != 0) {
		total = write_bytes (outfile, wordbuffer, word_index);
		word_index = 0;
	}

	uncompressed_bits += (total * 8);
}

int to_bytes ( int bits ) {

	if ((bits % 8) == 0) {
		return bits/8;
	}
	return bits/8 + 1;
}
