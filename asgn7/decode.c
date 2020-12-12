#include "io.h"
#include "trie.h"
#include "word.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// extern stats
uint64_t uncompressed_bits;
uint64_t compressed_bits;

#define OPTIONS "vi:o:"

int bit_length(int num) { return (log2(num) + 1); }

int main(int argc, char **argv) {

  int c = 0;
  bool stats = false;
  // default in / out file
  int infile = STDIN_FILENO;
  int outfile = STDOUT_FILENO;

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {

    // display compression statistics
    case 'v':
      stats = true;
      break;

    // specify input other than stdin
    case 'i':
      infile = open(optarg, O_RDONLY);
      break;

    // specify output other than stout
    case 'o':
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      break;
    }
  }

  // make a fileheader struct contains the protection bits and magic num
  FileHeader hd = {0, 0};
  ;
  read_header(infile, &hd);
  hd.magic = MAGIC;

  if (hd.magic != 0x8badbeef) {
    exit(1);
  }

  // file protection
  struct stat permissions;
  fstat(infile, &permissions);
  hd.protection = permissions.st_mode;
  // outfile emulates infile protection
  fchmod(outfile, hd.protection);
  write_header(outfile, &hd);

  // decoding based on provided pseudocode in asgn7 lab
  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;

  while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) {
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    next_code++;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
    flush_words(outfile);
  }

  wt_delete(table);
  close(infile);
  close(outfile);

  if (stats) {
    printf("Compressed file size: %lu bytes", compressed_bits);
    printf("Uncompressed file size: %lu bytes", uncompressed_bits);
    printf("Compression ratio: %lu%%",
           (100 * (1 - (compressed_bits / uncompressed_bits))));
  }

  return 0;
}
