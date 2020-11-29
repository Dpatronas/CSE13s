#include "bf.h"
#include "speck.h" //hash()
#include <stdio.h>
#include <stdlib.h>

int set_bits;

// create a bloom filter with the sized 64 bit for total of 128 bit (not native)
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    // Three salt values to hash each sized
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    // create vector bloomfilter
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}

void bf_delete(BloomFilter *bf) {
  bv_delete(bf->filter);
  free(bf);
}

// inserts a new key into the bloomfilter (key = word)
// indices to set bit given by hash funtion
// key to insert into bloomfilter
void bf_insert(BloomFilter *bf, char *key) {

  // the length used for index MOD length_BF
  uint32_t len = bv_get_len(bf->filter);

  // set indexes as the hash for each salt with same key
  // mod the index by BF length
  uint32_t index1 = hash(bf->primary, key) % len;
  uint32_t index2 = hash(bf->secondary, key) % len;
  uint32_t index3 = hash(bf->tertiary, key) % len;

  // bit to set = Index MOD Size of Bloom filter (default is 2^20 bits)
  // set the bit as the index MOD bv_get_len(b->filter)
  // call set bit with bf->filter BV using index
  bv_set_bit(bf->filter, index1);
  bv_set_bit(bf->filter, index2);
  bv_set_bit(bf->filter, index3);

  // increment the set bits in bf
  set_bits++;
}

// probe BloomFilter to check if a key has been inserted
// key to check membership
bool bf_probe(BloomFilter *bf, char *key) {

  // the length used for index MOD length_BF
  uint32_t len = bv_get_len(bf->filter);

  // this is the index to check
  uint32_t index1 = hash(bf->primary, key) % len;
  uint32_t index2 = hash(bf->secondary, key) % len;
  uint32_t index3 = hash(bf->tertiary, key) % len;

  // booleans to check if the indexes have been set
  bool first = bv_get_bit(bf->filter, index1);
  bool second = bv_get_bit(bf->filter, index2);
  bool third = bv_get_bit(bf->filter, index3);

  // if all three indexes are set (PROBABLY) in the BloomFilter set
  if (first && second && third) {
    return true;
  }

  // if not definitely NOT in the set
  else
    return false;
}
