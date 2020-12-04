//Eugene Chou code from piazza

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BYTE    8     // 8 bits per byte.
#define BLOCK   4096  // 4KB per block.

typedef struct BitVector {
  uint8_t *vector;
  uint32_t length;
} BitVector;

static uint32_t bytes(uint32_t bits) {
  return bits % 8 || !bits ? bits / 8 + 1 : bits / 8;
}

BitVector *bv_create(uint32_t length) {
  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  v->vector = (uint8_t *)calloc(bytes(length), sizeof(uint8_t));
  v->length = length;
  return v;
}

void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  return (v->vector[i >> 3] >> (i & 7)) & 1;
}

void bv_read(BitVector *v, int infile) {
  read(infile, v->vector, bytes(v->length));
}

void bv_print(BitVector *v) {
  printf("[");
  for (uint32_t i = 0; i < v->length; i += 1) {
    printf("%" PRIu8, bv_get_bit(v, i));
  }
  printf("]\n");
}
