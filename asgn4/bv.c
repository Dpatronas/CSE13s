// bv.h - Contains the function declarations for the BitVector ADT.

#include "bv.h"
#include <inttypes.h>
#include <stdlib.h>

// to prevent include math.h library
// this ceiling function will disregard the negative number case since bit
// length is unsigned
int Ceil(float n) {
  // truncates the n and adds 1
  if ((int)n < n) {
    return (int)n + 1;
  } else
    return (int)n;
}

// Creates a new BitVector of specified length.
// bit_len : The unsigned length in bits of the BitVector.
// returns an 8 bit vector pointer
BitVector *bv_create(uint32_t bit_len) {

  // Allocate the BitVector on the heap (32 bits)
  BitVector *res = (BitVector *)malloc(sizeof(BitVector));
  if (!res) {
    return NULL;
  }
  res->length = bit_len;
  // Allocate the vector array of bitvector on heap (8 bits)
  res->vector = (uint8_t *)malloc((Ceil(res->length / 8)) * sizeof(uint8_t));
  if (!res) {
    return NULL;
  }
  return res;
}

// Frees memory allocated for a BitVector.
void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
}

// Returns the length in bits of the BitVector.
uint32_t bv_get_len(BitVector *v) { return v->length; }

// Sets the bit at index in the BitVector. from 0 -> 1
// i : Index of the bit to set.
void bv_set_bit(BitVector *v, uint32_t i) {
  int Byte_i = (int)i / 8; // normalized to access the byte element of vector
  int bit_i = (int)i % 8;  // normalized to access the bit within the vector

  // ex: 1010
  //   |0100  <- 0001 << 3 (index bit)
  //    1110     index bit is set to 1
  v->vector[Byte_i] |= (0x1 << (bit_i));
}

// Clears the bit at index in the BitVector
// i : Index of the bit to clear.
void bv_clr_bit(BitVector *v, uint32_t i) {
  int Byte_i = (int)i / 8; // normalized to access the byte element of vector
  int bit_i = (int)i % 8;  // normalized to access the bit within the vector

  // ex   1100
  //   & 1011  <- the inverse of ( 0001) << 3 (index)
  //   = 1000  the index bit is cleared
  v->vector[Byte_i] &= ~(0x1 << (bit_i));
}

// Gets a bit from a BitVector.
// i : Index of the bit to get.
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  int Byte_i = (int)i / 8; // normalized to access the byte element of vector
  int bit_i = (int)i % 8;  // normalized to access the bit within the vector

  // ex: 0001 <- 0100 >> 3 (the index bit)
  //  & 0001
  //  = 0001 (this would be 0 if we started with 1000)
  return ((v->vector[Byte_i] >> (bit_i)) & 0x1);
}

// Sets all bits in a BitVector.
// v : The BitVector.
void bv_set_all_bits(BitVector *v) {
  // loops through all the bits and sets them using the defined function
  for (int i = 0; i < bv_get_len(v); i++) {
    bv_set_bit(v, i);
  }
}
