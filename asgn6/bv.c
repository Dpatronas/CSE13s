// bv.h - Contains the function declarations for the BitVector ADT.

#include "bv.h"
#include <inttypes.h>
#include <stdlib.h>

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
  int Byte_i = (int)i / 8;
  int bit_i = (int)i % 8;
  v->vector[Byte_i] |= (0x1 << (bit_i));
}

// Gets a bit from a BitVector.
// i : Index of the bit to get.
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  int Byte_i = (int)i / 8;
  int bit_i = (int)i % 8;
  return ((v->vector[Byte_i] >> (bit_i)) & 0x1);
}
