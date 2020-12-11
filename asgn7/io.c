#include "io.h"

#define BLOCK 4096

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
	int total = 0;			//number of bytes to write

	do {
		write_bytes = read(outfile, (buff + total), (to_write - total));
		total += write_bytes;
	}
	while (write_bytes > 0 && total != to_write);
	return total;
}


void read_header(int infile, FileHeader *header) {
  //read from either STDIN_FILENO or specified infile
  read_bytes (infile, (uint8_t*)header, sizeof(FileHeader));
}


void write_header(int outfile, FileHeader *header) {
	//write from either STDOUT_FILENO or specified outfile
  write_bytes (outfile, (uint8_t*)header, sizeof(FileHeader));
}


//read symbols from an infile
bool read_sym(int infile, uint8_t *sym) {
  
  //track the bytes which have been read
  static int end = 0;

  if (sym_index == 0) {
    //store the bytes read
  	end = read_bytes(infile, sym_buff, BLOCK);
  }
  //load symbol as the current index of buffer and increment
  *sym = sym_buff[sym_index++];

  //after loading the symbol check the buffer
  //if buffer is EOF
  if (sym_index == BLOCK) {
  	sym_index = 0;
  }
  //potential bytes left to read
  else if (end == BLOCK) {
  	return true;
  }
  //can no longer read a block
  else {
    //check if the index is past the end
  	if (sym_index == end + 1) {
  		return false;
  	}
  	else  {
      // if it is not there is still bytes to read
  		return true;
  	}
  }
}

//encode
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bit_len) {

  //code buffer
  for ( int i = 0; i < bit_len; i++) {
    //getbit (LSB) for code
    if ((code & 1) == 1) {
      //set bit(bitbuff, bitindex)
      bitbuff[bitindex >> 3] |= ( 1 << (bitindex % 8));
    }
    else {
      //clr bit(bitbuff, bitindex)
      bitbuff[bitindex >> 3] &= ~(( 1 << (bitindex % 8)));
    }
    bitindex ++;  //increment the buffer
    code >>= 1;   //take the next code

    //check if end of buffer
    if (bitindex == BLOCK * 8) {
      //write out the buffer and restart
      flush_pairs(outfile);
    }
  }

  //symbol buffer
  for ( int i = 0; i < 8; i++) {
    //getbit (LSB) for symbol
    if ((sym & 1) == 1) {
      //set bit(symbuff, bitindex)
      sym_buff[bitindex >> 3] |= ( 1 << (bitindex % 8));
    }
    else {
      //clr bit(symbuff, bitindex)
      sym_buff[bitindex >> 3] &= ~(( 1 << (bitindex % 8)));
    }
    sym_index ++;
    sym >>= 1;

    //check if end of buffer
    if (bitindex == BLOCK * 8) {
      //write out the buffer and restart
      write_bytes(outfile, sym_buff, BLOCK);
      bitindex = 0;
    }
  }
}

//encode
void flush_pairs(int outfile) {

	if (bitindex != 0) {
		write_bytes(outfile, bitbuff, to_bytes(bitindex));
    bitindex = 0;
	}
} 

//opposite of buffer pair, decode
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bit_len) {
	
  *code = 0;
  //load code: current block
	for (int i = 0; i < bit_len; i++) {

    if (bitindex == 0) {
      read_bytes(infile, bitbuff, BLOCK);
    }
    if ( (bitbuff[bitindex] & 1) == 1 ) {
      //set_bit(*code, i);
      *code |= ( 1 << (i % 8));
    }
    else {
      //clr_bit(*code, i);
      *code &= ~(( 1 << (i % 8)));
    }

    bitindex++;
    if ( bitindex == BLOCK * 8) {
      bitindex = 0;
    }
  }
  return *code != STOP_CODE;

  //load symbol: current block
  for (int i = 0; i < 8; i++) {

    if (bitindex == 0) {
      read_bytes(infile, bitbuff, BLOCK);
    }
    if ( (bitindex & 1 ) == 1 ) {
      //set_bit(code, i);
      *sym |= ( 1 << (i % 8));
    }
    else {
      //clr_bit(code, i);
      *sym &= ~(( 1 << (i % 8)));
    }

    bitindex++;
    if ( bitindex == BLOCK * 8) {
      bitindex = 0;
    }
  }
}


void buffer_word(int outfile, Word *w) {

  for (int i = 0; i < w->len; i++) {
    wordbuffer[word_index] = w->syms[i];
    word_index++;
    //if buffer fills up write the bytes to the outfile
    if (word_index == BLOCK) {
      flush_words(outfile);
    }
  }
}



void flush_words(int outfile) {

  if (word_index != 0) {
    write_bytes (outfile, wordbuffer, word_index);
    word_index = 0;
  }
}


int to_bytes ( int bits ) {
  int bytes = 0;

  if ((bits % 8) == 0) {
    bytes = bits/8;
    return bytes;
  }
  return bytes = bits/8 + 1;
}
