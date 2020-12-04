#include "io.h"

//stats
uint64_t total_syms;
uint64_t total_bits;

int read_bytes(int infile, uint8_t *buf, int to_read) {

}

int write_bytes(int outfile, uint8_t *buf, int to_write) {

}

void read_header(int infile, FileHeader *header) {

}

void write_header(int outfile, FileHeader *header) {

}

bool read_sym(int infile, uint8_t *byte) {

}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bit_len) {

}

void flush_pairs(int outfile) {

}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bit_len) {

}

void buffer_word(int outfile, Word *w) {

}

void flush_words(int outfile) {

}

#endif
